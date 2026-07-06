// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_logger_registrator.h
//
// Purpose (plain English):
//   Registers every logger channel used by the O-DU High with the central
//   logger service, so they can be individually enabled/disabled and given
//   log levels through the YAML config. Loggers here include: MAC, RLC, F1AP,
//   scheduler, FAPI, and (conditionally) NTN. Each channel appears in the
//   YAML config's [log] block as its own entry (e.g. `mac_level: info`).
// =============================================================================

#pragma once


#include "du_high/du_high_logger_registrator.h"
#include "du_high/ntn/ntn_logger_registrator.h"
#include "fapi/fapi_logger_registrator.h"
#include "o_du_high_unit_config.h"


namespace ocudu {

/// Checks if NTN is enabled in any cell.

/// \brief Returns true if at least one configured cell has NTN (Non-Terrestrial
///        Network / satellite) parameters set. Used to decide whether to
///        register the NTN loggers.
static bool is_ntn_enabled(span<const du_high_unit_cell_config> cells_cfg)
{
  for (const auto& cell : cells_cfg) {
    // .ntn_cfg is a std::optional; has_value() means the user wrote an
    // [ntn] block for this cell in the YAML.
    if (cell.cell.ntn_cfg.has_value()) {
      return true;
    }
  }
  return false;
}

/// Registers the O-RAN DU high loggers in the logger service.

/// \brief Registers every DU-High-side logger channel with the logger service.
///
/// After this runs, the logging framework knows about all channels this unit
/// might write to, and can apply the log levels the user specified.
inline void register_o_du_high_loggers(const o_du_high_unit_config& unit_config)
{
  // Register the "always on" DU High channels (MAC, RLC, F1AP, scheduler, ...).
  register_du_high_loggers(unit_config.du_high_cfg.config.loggers);

  // Register NTN loggers only if at least one cell has NTN config

  // NTN loggers are only registered when at least one cell actually uses NTN.
  // This avoids cluttering log output with disabled channels.
  if (is_ntn_enabled(unit_config.du_high_cfg.config.cells_cfg)) {
    register_ntn_loggers(unit_config.du_high_cfg.config.loggers.ntn_level);
  }


  // Register the FAPI channels (MAC↔PHY message tracing).
  register_fapi_loggers(unit_config.fapi_cfg);
}


} // namespace ocudu
