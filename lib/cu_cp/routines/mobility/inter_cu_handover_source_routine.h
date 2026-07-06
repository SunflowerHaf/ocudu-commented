// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/mobility/inter_cu_handover_source_routine.h  (54 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../../cu_up_processor/cu_up_processor_repository.h"
#include "../../du_processor/du_processor_repository.h"
#include "../../ue_manager/ue_manager_impl.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {


class inter_cu_handover_source_routine
{
public:
  inter_cu_handover_source_routine(cu_cp_ue_index_t              ue_index_,
                                   byte_buffer                   command,
                                   ue_manager&                   ue_mng_,
                                   du_processor_repository&      du_db_,
                                   cu_up_processor_repository&   cu_up_db_,
                                   ngap_control_message_handler& ngap_,
                                   xnap_interface*               xnap_,
                                   ocudulog::basic_logger&       logger_);


  void operator()(coro_context<async_task<bool>>& ctx);


  static const char* name() { return "Inter CU Handover Source Routine"; }


private:
  void fill_e1ap_bearer_modification_request_pdcp_sn_query();
  bool fill_status_transfer();


  cu_cp_ue_index_t              ue_index;
  byte_buffer                   command;
  ue_manager&                   ue_mng;
  du_processor_repository&      du_db;
  cu_up_processor_repository&   cu_up_db;
  ngap_control_message_handler& ngap;
  xnap_interface*               xnap = nullptr;


  ocudulog::basic_logger& logger;


  byte_buffer                               ho_reconfig_pdu;
  e1ap_bearer_context_modification_request  bearer_mod_req          = {};
  e1ap_bearer_context_modification_response bearer_mod_resp         = {};
  f1ap_ue_context_modification_response     ue_context_mod_response = {};
  f1ap_ue_context_modification_request      ue_context_mod_request  = {};
  cu_cp_status_transfer                     status_transfer         = {};
};


} // namespace ocudu::ocucp
