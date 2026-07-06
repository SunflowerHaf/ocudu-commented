// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/o_du_low/du_low_config_validator.h
//
// Purpose (plain English):
//   Declares validate_du_low_config() — the pre-startup sanity check for the
//   DU-Low configuration. Called once before the O-DU Low is constructed.
//
//   Also defines du_low_prach_validation_config — a small struct carrying the
//   per-cell parameters needed for PRACH detector validation (format, SCS,
//   zero-correlation zone, number of antennas) that are passed alongside the
//   main DU-Low config.
//
//   The validator checks:
//     * Rx symbol dump port is within the valid range for the cell's antenna count.
//     * Expert PHY string options (SINR method, equaliser) are valid.
//     * Thread concurrency values are within [0, hardware_concurrency()].
//     * Per-cell PRACH parameters are supported by the PRACH detector.
// =============================================================================

#pragma once

#include "du_low_config.h"

#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/prach/prach_subcarrier_spacing.h"


namespace ocudu {

/// DU low PRACH configuration for validation.


/// \brief Per-cell PRACH parameters needed for the pre-startup validator.
///
/// These are extracted from the full cell config and passed to the validator
/// so it can check that the PRACH format/SCS/ZCZ/port combination is
/// supported by the PRACH detector implementation.
struct du_low_prach_validation_config {
  /// PRACH format.
  prach_format_type format; ///< PRACH preamble format (e.g. format 0, A1, B4).
  /// PRACH subcarrier spacing.
  prach_subcarrier_spacing prach_scs;
  /// PRACH zero correlation zone.
  unsigned zero_correlation_zone; ///< ZCZ index (TS 38.211 Table 6.3.3.1-5).
  /// PRACH number of ports.
  unsigned nof_prach_ports; ///< Number of receive antenna ports for PRACH.
  /// Number of uplink antennas.
  unsigned nof_antennas_ul; ///< Total UL antennas (for Rx port range check).
};

/// Validates the given DU low configuration. Returns true on success, false otherwise.

/// \brief Validates the DU-Low configuration before construction.
///
/// \param config              The parsed DU-Low unit config.
/// \param prach_cells_config  Per-cell PRACH validation parameters (one per cell).
/// \return true if all checks pass; false (with error to stdout) on failure.
bool validate_du_low_config(const du_low_unit_config&                  config,
                            span<const du_low_prach_validation_config> prach_cells_config);


} // namespace ocudu
