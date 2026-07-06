// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/config/sched_cell_config_helpers.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct pucch_resource_builder_params;
struct bwp_downlink_dedicated;
struct serving_cell_config;
struct dl_config_common;
struct pdcch_config;


namespace config_helpers {


unsigned compute_tot_nof_monitored_pdcch_candidates_per_slot(const serving_cell_config& ue_cell_cfg,
                                                             const dl_config_common&    dl_cfg_common);
unsigned compute_tot_nof_monitored_pdcch_candidates_per_slot(const pdcch_config&     ue_pdcch_cfg,
                                                             const dl_config_common& dl_cfg_common);
} // namespace config_helpers
} // namespace ocudu
