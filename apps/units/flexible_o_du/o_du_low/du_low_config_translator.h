// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_config_translator.h
//
// Purpose (plain English):
//   Declares two "translator" functions that bridge the user-facing DU-Low
//   config into the internal representations expected by the core O-DU Low
//   and by the worker manager.
//
//     * generate_o_du_low_config — takes the user's DU-Low unit config plus
//       the per-cell PHY parameters (bandwidth, TDD pattern, PRACH index,
//       antenna counts, ...) and fills in the internal odu::o_du_low_config
//       struct: buffer sizes, algorithm choices, resource-grid dimensions,
//       PRACH detector parameters, etc.
//
//     * fill_du_low_worker_manager_config — tells the worker manager which
//       thread pools/executors the DU-Low needs (PDSCH pool, PUCCH pool,
//       PUSCH+SRS pool), including size hints derived from bandwidth and
//       antenna count.
// =============================================================================

#pragma once


#include "o_du_low_unit_factory_config.h"
#include "ocudu/adt/span.h"
#include "ocudu/du/du_low/o_du_low_config.h"


namespace ocudu {


namespace odu {
struct du_cell_config;
struct du_low_config;
} // namespace odu


struct du_low_unit_config;
struct worker_manager_config;

/// Generates O-DU low configuration from the given parameters.

/// \brief Fills in the internal O-DU Low config from the user-facing config
///        plus per-cell parameters. See the CPP for details.
void generate_o_du_low_config(odu::o_du_low_config&                           out_config,
                              const du_low_unit_config&                       du_low_unit_cfg,
                              span<const o_du_low_unit_config::du_low_config> cells);

/// Fills the DU low worker manager parameters of the given worker manager configuration.

/// \brief Declares the DU-Low's executor needs to the worker manager.
///
/// \param config                   Worker manager config being built up.
/// \param unit_cfg                 The DU-Low unit config.
/// \param is_blocking_mode_active  True in single-thread/debug builds.
/// \param nof_dl_antennas          Per-cell DL antenna counts (sizes DL pools).
/// \param nof_ul_antennas          Per-cell UL antenna counts (sizes UL pools).
void fill_du_low_worker_manager_config(worker_manager_config&    config,
                                       const du_low_unit_config& unit_cfg,
                                       unsigned                  is_blocking_mode_active,
                                       span<const unsigned>      nof_dl_antennas,
                                       span<const unsigned>      nof_ul_antennas);


} // namespace ocudu
