// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/procedures/du_proc_context_view.h  (31 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ocudulog/logger.h"


namespace ocudu {
namespace odu {


struct du_manager_params;
struct du_manager_context;
class du_cell_manager;
class du_ue_manager;
class du_ran_resource_manager;
class du_manager_metrics_aggregator_impl;


struct du_proc_context_view {
  /// Static parameters of the DU.
  /// Static parameters of the DU.
  du_manager_params&                  params;
  du_manager_context&                 ctxt;
  du_cell_manager&                    cell_mng;
  du_ue_manager&                      ue_mng;
  du_ran_resource_manager&            res_mng;
  du_manager_metrics_aggregator_impl& metrics;
  ocudulog::basic_logger&             logger;
};


} // namespace odu
} // namespace ocudu
