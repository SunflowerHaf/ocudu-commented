// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/procedures/f1c_disconnection_handling_procedure.h  (35 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "du_proc_context_view.h"
#include "procedure_logger.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace odu {


struct du_manager_params;
class du_cell_manager;
class du_ue_manager;
class du_manager_metrics_aggregator_impl;


class f1c_disconnection_handling_procedure
{
public:
  f1c_disconnection_handling_procedure(du_proc_context_view ctxt_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  const du_proc_context_view ctxt;
  du_procedure_logger        proc_logger;


  unsigned i = 0;
};


} // namespace odu
} // namespace ocudu
