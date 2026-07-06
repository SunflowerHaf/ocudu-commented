// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_validators.cpp
 * @brief Implementation of gNB application configuration validation functions.
 *
 * These functions are called by main() after the YAML config file has been
 * parsed but before any system objects are constructed. They act as a sanity
 * check gate — catching misconfiguration early and providing clear error
 * messages rather than mysterious failures later at runtime.
 */

#include "gnb_appconfig_validators.h"
#include "apps/helpers/logger/logger_appconfig_validator.h" ///< validate_logger_appconfig()
#include "apps/services/worker_manager/worker_manager_appconfig_validator.h" ///< validate_expert_execution_appconfig()
#include "apps/units/flexible_o_du/o_du_high/du_high/du_high_config.h" ///< du_high_unit_config definition
#include "apps/units/o_cu_cp/cu_cp/cu_cp_unit_config.h" ///< cu_cp_unit_config definition


using namespace ocudu;


/**
 * @brief Validates the HAL (Hardware Abstraction Layer) configuration.
 *
 * The HAL config is only relevant when DPDK (Data Plane Development Kit) is
 * compiled in. DPDK provides kernel-bypass networking for very low latency.
 * If DPDK is present and the user has provided a hal_config block, it must
 * include EAL (Environment Abstraction Layer) arguments — DPDK requires these
 * to initialise correctly (e.g. specifying which CPU cores and NICs DPDK can use).
 *
 * @param config  Optional HAL config. Empty means DPDK is either not compiled
 *                in or not being used.
 * @return true if the HAL config is valid or not present; false if DPDK is
 *         compiled in and hal_config is present but has no EAL arguments.
 */
static bool validate_hal_config(const std::optional<hal_appconfig>& config)
{
#ifdef DPDK_FOUND
  // DPDK is compiled in. If the user provided a hal_config block, make sure
  // the mandatory EAL arguments string is not empty.
  if (config && config->eal_args.empty()) {
    fmt::print("It is mandatory to fill the EAL configuration arguments to initialize DPDK correctly\n");
    return false;
  }
#endif
  // Either DPDK is not compiled in, or no hal_config was provided, or EAL args are present.
  return true;
}


/**
 * @brief Validates the complete top-level gNB application configuration.
 *
 * Runs each sub-validator in sequence. Returns false as soon as any check
 * fails so that only the first error is reported (keeping error output clean).
 *
 * @param config  The fully parsed gnb_appconfig to validate.
 * @return true if all validation checks pass; false on the first failure.
 */
bool ocudu::validate_appconfig(const gnb_appconfig& config)
{
  // Check log levels are valid strings and the log file path is writable.
  if (!validate_logger_appconfig(config.log_cfg)) {
    return false;
  }


  // Check thread pool sizes, CPU affinity masks, and task queue sizes are
  // within acceptable ranges for the current hardware.
  if (!validate_expert_execution_appconfig(config.expert_execution_cfg)) {
    return false;
  }


  // If DPDK is configured, check that EAL arguments are present.
  if (!validate_hal_config(config.hal_config)) {
    return false;
  }


  return true;
}


/**
 * @brief Validates that DU cell PLMNs and TACs are present in the CU-CP config.
 *
 * Every cell the DU hosts must be served by the CU-CP. The CU-CP declares
 * which Tracking Areas (identified by TAC) and PLMNs it supports by listing
 * them in its AMF configuration. This function cross-checks the DU cell list
 * against that list.
 *
 * Example: if the DU has a cell with PLMN "00101" and TAC 7, there must be
 * an entry in the CU-CP's supported_tas with TAC 7 that includes PLMN "00101".
 *
 * @param du_hi_cfg  DU High config containing the list of cells.
 * @param cu_cp_cfg  CU-CP config containing the AMF and supported tracking areas.
 * @return true if all DU cells are covered; false if any cell is missing from
 *         the CU-CP's supported areas.
 */
bool ocudu::validate_plmn_and_tacs(const du_high_unit_config& du_hi_cfg, const cu_cp_unit_config& cu_cp_cfg)
{
  // If running without a real core network (no_core mode, used in test setups),
  // the AMF supported TAs are not meaningful — skip this check.
  if (cu_cp_cfg.amf_config.no_core) {
    return true;
  }


  // Build a flat list of all supported tracking area items across the primary
  // AMF and any additional AMFs configured for redundancy.
  std::vector<cu_cp_unit_supported_ta_item> supported_tas;


  supported_tas.reserve(cu_cp_cfg.amf_config.amf.supported_tas.size());
  for (const auto& supported_ta : cu_cp_cfg.amf_config.amf.supported_tas) {
    supported_tas.push_back(supported_ta);
  }


  // Include supported TAs from any extra (secondary) AMFs as well.
  for (const auto& amf : cu_cp_cfg.extra_amfs) {
    for (const auto& supported_ta : amf.supported_tas) {
      supported_tas.push_back(supported_ta);
    }
  }


  // For each DU cell, search for a matching TAC+PLMN combination in the
  // flattened supported_tas list.
  for (const auto& cell : du_hi_cfg.cells_cfg) {
    bool found = false;

    for (const auto& supported_ta : supported_tas) {
      for (const auto& plmn_item : supported_ta.plmn_list) {
        // A match requires both the PLMN and the TAC to agree.
        if (plmn_item.plmn_id == cell.cell.plmn && supported_ta.tac == cell.cell.tac) {
          found = true;
          break;
        }
      }
    }


    // If no matching entry was found for this cell, report exactly which
    // PLMN and TAC are missing so the user knows what to fix in the config.
    if (!found) {
      fmt::print("Could not find cell PLMN '{}' and cell TAC '{}' in the CU-CP supported tracking areas list\n",
                 cell.cell.plmn,
                 cell.cell.tac);
      return false;
    }
  }


  return true;
}
