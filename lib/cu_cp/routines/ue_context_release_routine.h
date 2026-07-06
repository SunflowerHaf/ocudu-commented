// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/ue_context_release_routine.h  (48 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../du_processor/du_processor.h"
#include "../ue_manager/ue_manager_impl.h"
#include "ocudu/e1ap/cu_cp/e1ap_cu_cp.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// \brief Handles the release of UE context resources from the CU-CP.

/// \brief Handles the release of UE context resources from the CU-CP.
class ue_context_release_routine
{
public:
  ue_context_release_routine(const cu_cp_ue_context_release_command& command_,
                             e1ap_bearer_context_manager*            e1ap_bearer_ctxt_mng_,
                             du_processor&                           du_proc_,
                             cu_cp_ue_removal_handler&               ue_removal_handler_,
                             ue_manager&                             ue_mng_,
                             ocudulog::basic_logger&                 logger_);


  void operator()(coro_context<async_task<cu_cp_ue_context_release_complete>>& ctx);


  static const char* name() { return "UE Context Release Routine"; }


private:
  cu_cp_ue_context_release_command command;


  e1ap_bearer_context_manager* e1ap_bearer_ctxt_mng = nullptr; // to trigger bearer context setup at CU-UP
  du_processor&                du_proc;            // to get RRC Reject and to trigger UE context modification at DU
  cu_cp_ue_removal_handler&    ue_removal_handler; // to remove UE
  ue_manager&                  ue_mng;
  ocudulog::basic_logger&      logger;

  // (Sub-)routine requests.

  // (Sub-)routine requests.
  rrc_ue_release_context              release_context;
  f1ap_ue_context_release_command     f1ap_ue_context_release_cmd;
  e1ap_bearer_context_release_command bearer_context_release_command;

  // (Sub-)routine results.

  // (Sub-)routine results.
  cu_cp_ue_index_t                  f1ap_ue_context_release_result;
  cu_cp_ue_context_release_complete release_complete;
};


} // namespace ocudu::ocucp
