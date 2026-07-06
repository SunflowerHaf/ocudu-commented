// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/config/serving_cell_config_builder.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pucch/pucch_configuration.h"
#include "ocudu/scheduler/config/cell_bwp_res_config.h"
#include "ocudu/scheduler/config/ran_cell_config.h"
#include "ocudu/scheduler/config/ue_bwp_config.h"


namespace ocudu::config_helpers {

/// Build the PUCCH-Config for a given UE.

/// Build the PUCCH-Config for a given UE.
pucch_config build_pucch_config(const ran_cell_config&        cell_cfg,
                                const cell_ul_bwp_res_config& cell_ul_bwp_res,
                                const ue_bwp_config&          ue_bwp_cfg);

/// Build the CSI-MeasConfig for a given UE.

/// Build the CSI-MeasConfig for a given UE.
std::optional<csi_meas_config> build_csi_meas_config(const ran_cell_config&        cell_cfg,
                                                     const cell_ul_bwp_res_config& cell_ul_bwp_res,
                                                     const ue_bwp_config&          ue_bwp_cfg);


} // namespace ocudu::config_helpers
