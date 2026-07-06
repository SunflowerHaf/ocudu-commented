// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/ue_resume_routine.h  (83 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../cu_cp_impl_interface.h"
#include "../du_processor/du_processor.h"
#include "../ue_manager/ue_manager_impl.h"
#include "ocudu/e1ap/cu_cp/e1ap_cu_cp.h"
#include "ocudu/e1ap/cu_cp/e1ap_cu_cp_bearer_context_update.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// \brief Handles the UE Connection Resume.

/// \brief Handles the UE Connection Resume.
class ue_resume_routine
{
public:
  ue_resume_routine(const rrc_resume_request&              request_,
                    const ue_configuration&                ue_cfg_,
                    du_processor&                          du_proc_,
                    cu_cp_ue_context_manipulation_handler& ue_context_handler_,
                    e1ap_bearer_context_manager&           e1ap_bearer_ctxt_mng_,
                    ue_manager&                            ue_mng_,
                    cu_cp_location_manager_handler&        loc_mng_handler_,
                    ocudulog::basic_logger&                logger_);


  void operator()(coro_context<async_task<rrc_resume_request_response>>& ctx);


  static const char* name() { return "RRC Resume Routine"; }


private:
  f1ap_ue_context_release_command fill_du_ue_context_release_command();


  bool generate_ue_context_setup_request(f1ap_ue_context_setup_request&               setup_request,
                                         const static_vector<srb_id_t, MAX_NOF_SRBS>& srbs,
                                         const rrc_ue_transfer_context&               transfer_context,
                                         byte_buffer&                                 cell_group_config);


  bool handle_ue_context_setup_response();


  bool add_security_context_to_bearer_context_modification(const ocudu::security::sec_as_config& security_cfg);


  bool fill_rrc_resume_request_response(const std::vector<f1ap_srb_to_setup>& srbs_to_be_setup_mod_list,
                                        const std::map<pdu_session_id_t, up_pdu_session_context_update>& pdu_sessions,
                                        const std::vector<drb_id_t>&                                     drb_to_remove,
                                        const f1ap_du_to_cu_rrc_info&               du_to_cu_rrc_info,
                                        const std::optional<rrc_meas_cfg>&          rrc_meas_cfg,
                                        bool                                        reestablish_srbs,
                                        bool                                        reestablish_drbs,
                                        std::optional<security::sec_selected_algos> selected_algos);


  const rrc_resume_request request;


  cu_cp_ue* ue = nullptr; // Pointer to UE in the DU


  rrc_ue_transfer_context rrc_context;


  const ue_configuration&                ue_cfg;
  du_processor&                          du_proc;
  cu_cp_ue_context_manipulation_handler& ue_context_handler;
  e1ap_bearer_context_manager&           e1ap_bearer_ctxt_mng; // to trigger bearer context modification at CU-UP
  ue_manager&                            ue_mng;               // to remove UE context from source DU processor
  cu_cp_location_manager_handler&        loc_mng_handler;
  up_config_update                       next_config;
  ocudulog::basic_logger&                logger;

  // (sub-)routine requests

  // (sub-)routine requests
  std::optional<i_rntis_t>                 i_rntis;
  f1ap_ue_context_setup_request            ue_context_setup_request;
  e1ap_bearer_context_modification_request bearer_context_modification_request;
  f1ap_ue_context_release_command          ue_context_release_cmd; // If HO fails target UE context needs to be removed.
  cu_cp_ue_context_release_command ue_context_release_command;     // After succesfull HO source UE needs to be removed.

  // (sub-)routine results

  // (sub-)routine results
  rrc_resume_request_response               response_msg;
  cu_cp_ue_index_t                          released_ue_index;
  f1ap_ue_context_setup_response            ue_context_setup_response;
  e1ap_bearer_context_modification_response bearer_context_modification_response;
};


} // namespace ocudu::ocucp
