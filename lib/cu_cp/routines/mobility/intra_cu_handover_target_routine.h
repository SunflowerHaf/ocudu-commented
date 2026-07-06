// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/mobility/intra_cu_handover_target_routine.h  (73 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../../cu_cp_impl_interface.h"
#include "../../mobility_manager/mobility_manager_impl.h"
#include "../../ue_manager/ue_manager_impl.h"
#include "ocudu/e1ap/cu_cp/e1ap_cu_cp.h"
#include "ocudu/f1ap/cu_cp/f1ap_cu.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// \brief Handles the handover of a UE between two different cells managed by the same CU.

/// \brief Handles the handover of a UE between two different cells managed by the same CU.
class intra_cu_handover_target_routine
{
public:
  intra_cu_handover_target_routine(const cu_cp_intra_cu_handover_target_request& request_,
                                   e1ap_bearer_context_manager&                  e1ap_bearer_ctxt_mng_,
                                   f1ap_ue_context_manager&                      target_du_f1ap_ue_ctxt_mng_,
                                   cu_cp_ue_context_release_handler&             ue_context_release_handler_,
                                   cu_cp_ue_removal_handler&                     ue_removal_handler_,
                                   cu_cp_ue_context_manipulation_handler&        cu_cp_handler_,
                                   cu_cp_location_manager_handler&               loc_mng_handler_,
                                   ue_manager&                                   ue_mng_,
                                   mobility_manager&                             mobility_mng_,
                                   ocudulog::basic_logger&                       logger_);


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "Intra CU Handover Target Routine"; }


private:
  up_config_update get_next_config_from_radio_bearer_cfg();


  bool add_security_context_to_bearer_context_modification(const ocudu::security::sec_as_config& security_cfg);

  /// Schedule the source UE release onto the source UE's own task scheduler. Kept out of the coroutine body because
  /// CORO_BEGIN cannot be nested (macro-local name collision).

  /// Schedule the source UE release onto the source UE's own task scheduler. Kept out of the coroutine body because
  /// CORO_BEGIN cannot be nested (macro-local name collision).
  void schedule_source_release_on_source_task_sched(cu_cp_ue_index_t source_ue_index);


  const cu_cp_intra_cu_handover_target_request request;

  // Pointer to UE in the source DU.

  // Pointer to UE in the source DU.
  cu_cp_ue* source_ue = nullptr;
  // Pointer to UE in the target DU.
  // Pointer to UE in the target DU.
  cu_cp_ue* target_ue = nullptr;


  e1ap_bearer_context_manager&           e1ap_bearer_ctxt_mng;
  f1ap_ue_context_manager&               target_du_f1ap_ue_ctxt_mng;
  cu_cp_ue_context_release_handler&      ue_context_release_handler;
  cu_cp_ue_removal_handler&              ue_removal_handler;
  cu_cp_ue_context_manipulation_handler& cu_cp_handler;
  cu_cp_location_manager_handler&        loc_mng_handler;
  ue_manager&                            ue_mng;
  mobility_manager&                      mobility_mng;


  ocudulog::basic_logger& logger;

  // (Sub-)routine requests.

  // (Sub-)routine requests.
  rrc_reconfiguration_procedure_request    rrc_reconfig_args;
  e1ap_bearer_context_modification_request bearer_context_modification_request;
  f1ap_ue_context_modification_request     target_ue_context_modification_request;
  cu_cp_ue_context_release_command         ue_context_release_command;

  // (Sub-)routine results.

  // (Sub-)routine results.
  bool                                      reconf_result = false;
  e1ap_bearer_context_modification_response bearer_context_modification_response;
};


} // namespace ocudu::ocucp
