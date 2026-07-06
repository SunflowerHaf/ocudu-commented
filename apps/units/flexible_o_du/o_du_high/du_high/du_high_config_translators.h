// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_high_config_translators.h
//
// Purpose (plain English):
//   Declares three translator functions that bridge the user-facing DU High
//   unit config into the internal representations used by the core DU High
//   library and the worker manager.
//
//     generate_du_cell_config — produces the low-level per-cell configuration
//       objects (SSB position, PDCCH, PUCCH, PRACH, scheduler params, QoS, etc.)
//       from the user's high-level cell entries. Used by announce_du_high_cells()
//       to show the user what was derived, and by generate_du_high_config().
//
//     generate_du_high_config — populates the full odu::du_high_configuration
//       (fed directly into the core DU High factory). Calls
//       generate_du_cell_config() internally.
//
//     fill_du_high_worker_manager_config — tells the worker manager which
//       thread-pool executors the DU High needs (MAC scheduler, RLC, F1AP,
//       PDCP, UE management, etc.) and their properties.
// =============================================================================

#pragma once


#include "du_high_config.h"
#include "ocudu/du/du_cell_config.h"


namespace ocudu {


namespace odu {
struct du_high_configuration;
} // namespace odu


struct du_high_unit_config;
struct worker_manager_config;

/// Converts and returns the given gNB application configuration to a DU cell configuration.

/// \brief Derives the low-level per-cell configs from the user's cell settings.
///
/// Resolves ARFCNs to SSB offsets, fills PDCCH coreset tables, selects
/// PUCCH resource grids, etc. Returns one du_cell_config per configured cell.
std::vector<odu::du_cell_config> generate_du_cell_config(const du_high_unit_config& config);

/// Generates and fills the given DU high configuration from the given DU high unit configuration.

/// \brief Populates the internal DU High configuration from the unit config.
///
/// Calls generate_du_cell_config() plus fills QoS, SRB, timing, identity
/// fields, and everything else the core DU High factory expects.
void generate_du_high_config(odu::du_high_configuration& du_hi_cfg, const du_high_unit_config& du_high_unit_cfg);

/// Fills the DU high worker manager parameters of the given worker manager configuration.

/// \brief Declares the DU High's executor requirements to the worker manager.
///
/// \param config                   Worker manager config being built.
/// \param unit_cfg                 The parsed DU High unit config.
/// \param is_blocking_mode_enabled True in single-thread/debug builds.
void fill_du_high_worker_manager_config(worker_manager_config&     config,
                                        const du_high_unit_config& unit_cfg,
                                        bool                       is_blocking_mode_enabled = false);


} // namespace ocudu
