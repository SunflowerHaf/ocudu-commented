// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/ue_amf_context_release_request_routine.h  (38 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_manager/ue_manager_impl.h"
#include "ocudu/support/async/async_task.h"
#include "ocudu/support/async/eager_async_task.h"


namespace ocudu {
namespace ocucp {

/// \brief Routine to handle the request to the AMF to remove the UE context from the CU-CP.
///
/// If the UE does not have an NG context, this procedure fallbacks to a removal of the UE context from the DU, CU-UP
/// and CU-CP without AMF involvement.

/// \brief Routine to handle the request to the AMF to remove the UE context from the CU-CP.
///
/// If the UE does not have an NG context, this procedure fallbacks to a removal of the UE context from the DU, CU-UP
/// and CU-CP without AMF involvement.
class ue_amf_context_release_request_routine
{
public:
  ue_amf_context_release_request_routine(const cu_cp_ue_context_release_request& request_,
                                         ngap_control_message_handler*           ng_release_handler_,
                                         cu_cp_ue_context_release_handler&       cu_cp_ue_ctxt_release_handler_,
                                         ocudulog::basic_logger&                 logger_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  const cu_cp_ue_context_release_request request;
  ngap_control_message_handler*          ng_release_handler = nullptr;
  cu_cp_ue_context_release_handler&      cu_cp_ue_ctxt_release_handler;
  ocudulog::basic_logger&                logger;


  bool amf_ue_release_requested = false;
};


} // namespace ocucp
} // namespace ocudu
