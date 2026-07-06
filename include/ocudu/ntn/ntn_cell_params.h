// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ntn/ntn_cell_params.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/ntn
// NTN interface headers: orbit_propagator (interface for computing satellite positions at future times), the propagator factory, and the ephemeris data types used by the NTN Doppler compensation subsystem.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/ntn.h"
#include <chrono>
#include <optional>
#include <variant>


namespace ocudu {

/// NTN cell-level configuration parameters.

/// NTN cell-level configuration parameters.
struct ntn_cell_params {
  /// NTN cell configuration.
  /// NTN cell configuration.
  ntn_config ntn_cfg;

  /// Whether UL HARQ Mode B is enabled for this NTN cell (if there is at least one UL HARQ process in mode B).

  /// Whether UL HARQ Mode B is enabled for this NTN cell (if there is at least one UL HARQ process in mode B).
  bool ul_harq_mode_b = false;

  /// Helper method to check if NTN is enabled.

  /// Helper method to check if NTN is enabled.
  bool is_enabled() const
  {
    return (ntn_cfg.cell_specific_koffset.has_value() and ntn_cfg.cell_specific_koffset.value().count() > 0);
  }
};


} // namespace ocudu
