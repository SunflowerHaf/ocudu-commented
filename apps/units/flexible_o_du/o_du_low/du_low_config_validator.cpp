// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_config_validator.cpp
//
// Purpose (plain English):
//   Sanity-checks the parsed DU-Low config *before* it's used to build the
//   upper PHY. Catches user errors up front instead of crashing deep inside
//   the RAN code. Four groups of checks:
//     1. Executor thread concurrency values are within the CPU's capability.
//     2. Expert PHY choices (SINR method, decoder iterations) make sense.
//     3. Log options (Rx port to dump) refer to a real antenna port.
//     4. Per-cell PRACH configurations satisfy the PHY's PRACH detector
//        constraints (format/SCS/ZCZ/ports combination is supported).
// =============================================================================

#include "du_low_config_validator.h"
#include "ocudu/adt/interval.h"
#include "ocudu/phy/upper/channel_processors/prach/prach_detector_phy_validator.h"


using namespace ocudu;


// -----------------------------------------------------------------------------
// validate_upper_phy_threads_appconfig()
//   Concurrency values must fit in [0, hardware_concurrency()]. 0 = "no limit".
//   Also checks that the pdsch_processor_type string is one of the known values.
// -----------------------------------------------------------------------------
static bool validate_upper_phy_threads_appconfig(const du_low_unit_expert_threads_config& config)
{
  // Closed interval: [0, hardware_concurrency()]. std::thread::hardware_concurrency()
  // returns the number of logical cores available.
  static const interval<unsigned, true> max_concurrency_range(0, std::thread::hardware_concurrency());


  bool valid = true;


  if (!max_concurrency_range.contains(config.max_pucch_concurrency)) {
    fmt::print("Maximum PUCCH concurrency (i.e., {}) must be in range {}.\n",
               config.max_pucch_concurrency,
               max_concurrency_range);
    valid = false;
  }


  if (!max_concurrency_range.contains(config.max_pusch_and_srs_concurrency)) {
    fmt::print("Maximum joint PUSCH and SRS concurrency (i.e., {}) must be in range {}.\n",
               config.max_pusch_and_srs_concurrency,
               max_concurrency_range);
    valid = false;
  }


  // PDSCH processor type is a free string in YAML; reject anything unknown.
  if ((config.pdsch_processor_type != "auto") && (config.pdsch_processor_type != "flexible") &&
      (config.pdsch_processor_type != "generic")) {
    fmt::print("Invalid PDSCH processor type. Valid types are: auto, generic and flexible.\n");
    valid = false;
  }


  if (!max_concurrency_range.contains(config.max_pdsch_concurrency)) {
    fmt::print("Maximum PDSCH concurrency (i.e., {}) must be in range {}.\n",
               config.max_pdsch_concurrency,
               max_concurrency_range);
    valid = false;
  }


  return valid;
}


/// Wrapper that just forwards to the threads check.
static bool validate_expert_execution_unit_config(const du_low_unit_config& config)
{
  return validate_upper_phy_threads_appconfig(config.expert_execution_cfg.threads);
}


// -----------------------------------------------------------------------------
// validate_phy_prach_configuration()
//   For every cell, checks that the requested PRACH parameters are actually
//   supported by the PRACH detector. Constraints are defined by TS38.211 and
//   the detector's own implementation (some (format, SCS, ZCZ) combos are
//   unsupported).
// -----------------------------------------------------------------------------
static bool validate_phy_prach_configuration(span<const du_low_prach_validation_config>& prach_cells_config)
{
  for (const auto& prach_cell_cfg : prach_cells_config) {
    error_type<std::string> valid_prach = validate_prach_detector_phy(prach_cell_cfg.format,
                                                                      prach_cell_cfg.prach_scs,
                                                                      prach_cell_cfg.zero_correlation_zone,
                                                                      prach_cell_cfg.nof_prach_ports);
    if (!valid_prach.has_value()) {
      // Detector returned an error string with the specific violation.
      fmt::print("Invalid configuration:\n    {}", valid_prach.error());
      return false;
    }
  }


  return true;
}

/// Validates expert physical layer configuration parameters.

// -----------------------------------------------------------------------------
// validate_expert_phy_unit_config()
//   Expert PHY string enum + non-zero decoder iterations.
// -----------------------------------------------------------------------------
static bool validate_expert_phy_unit_config(const du_low_unit_expert_upper_phy_config& config)
{
  bool valid = true;


  if ((config.pusch_sinr_calc_method != "channel_estimator") &&
      (config.pusch_sinr_calc_method != "post_equalization") && (config.pusch_sinr_calc_method != "evm")) {
    fmt::print(
        "Invalid PUSCH SINR calculation method. Valid types are: channel_estimator, post_equalization and evm.\n");
    valid = false;
  }


  if (config.pusch_decoder_max_iterations == 0) {
    fmt::print("Maximum PUSCH LDPC decoder iterations cannot be zero.\n");
    valid = false;
  }


  return valid;
}


// -----------------------------------------------------------------------------
// validate_log_options()
//   If the user wants to dump Rx IQ samples from a specific port, that port
//   must exist on the cell.
// -----------------------------------------------------------------------------
static bool validate_log_options(const du_low_unit_logger_config& config, const du_low_prach_validation_config& cell)
{
  if (!config.phy_rx_symbols_filename.empty() && config.phy_rx_symbols_port.has_value() &&
      (config.phy_rx_symbols_port.value() >= cell.nof_antennas_ul)) {
    fmt::print("Requested IQ dump from Rx port {}, valid Rx ports are 0-{}.\n",
               config.phy_rx_symbols_port.value(),
               cell.nof_antennas_ul - 1);
    return false;
  }


  return true;
}


// -----------------------------------------------------------------------------
// validate_du_low_config()
//   Top-level entry. Runs each check in turn; bails out on the first failure
//   so the user doesn't get a wall of stacked errors.
// -----------------------------------------------------------------------------
bool ocudu::validate_du_low_config(const du_low_unit_config&                  config,
                                   span<const du_low_prach_validation_config> prach_cells_config)
{
  // Log-options check uses cell[0]'s antenna count — assumes all cells have
  // the same UL antenna count, which is enforced elsewhere.
  if (!validate_log_options(config.loggers, prach_cells_config.front())) {
    return false;
  }


  if (!validate_expert_phy_unit_config(config.expert_phy_cfg)) {
    return false;
  }


  if (!validate_expert_execution_unit_config(config)) {
    return false;
  }


  if (!validate_phy_prach_configuration(prach_cells_config)) {
    return false;
  }


  return true;
}
