// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_config_translators.h
//
// Purpose (plain English):
//   Bridges the "unit config" (what the user wrote in YAML) into the
//   "worker manager config" (what the thread-pool subsystem needs to know
//   about which executors to create for this unit). The worker manager owns
//   all the CPU thread pools; every subsystem that needs to run code on a
//   particular pool has to declare its executor requirements here.
//
//   For the O-DU High, that means declaring executors for MAC control, MAC
//   downlink/uplink, RLC, F1AP, plus (if E2 is enabled) an E2 executor.
// =============================================================================

#pragma once


#include "du_high/du_high_config_translators.h"
#include "e2/o_du_high_e2_config_translators.h"
#include "o_du_high_unit_config.h"


namespace ocudu {

/// Fills the O-RAN DU high worker manager parameters of the given worker manager configuration.

/// \brief Populates the worker-manager configuration for the O-DU High.
///
/// This tells the worker manager: "here are the executors this O-DU High
/// instance needs, and this is what each of them should look like (queue
/// sizes, priorities, whether blocking is allowed, etc.)".
///
/// \param config                     The worker-manager config being built up
///                                   (may already contain entries from other
///                                   units, hence "fill" not "set").
/// \param unit_cfg                   The parsed O-DU High config.
/// \param is_blocking_mode_enabled   True in single-threaded/debug builds
///                                   where executors are allowed to block
///                                   their caller instead of dispatching.
inline void fill_o_du_high_worker_manager_config(worker_manager_config&       config,
                                                 const o_du_high_unit_config& unit_cfg,
                                                 bool                         is_blocking_mode_enabled = false)
{
  fill_du_high_worker_manager_config(config, unit_cfg.du_high_cfg.config, is_blocking_mode_enabled);
  fill_o_du_high_e2_worker_manager_config(config, unit_cfg.e2_cfg);
}


} // namespace ocudu
