// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/ue_amf_context_release_request_routine.cpp  (42 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ue_amf_context_release_request_routine.h"
#include "ue_context_release_routine.h"


using namespace ocudu;
using namespace ocucp;


ue_amf_context_release_request_routine::ue_amf_context_release_request_routine(
    const cu_cp_ue_context_release_request& request_,
    ngap_control_message_handler*           ng_release_handler_,
    cu_cp_ue_context_release_handler&       cu_cp_ue_ctxt_release_handler_,
    ocudulog::basic_logger&                 logger_) :
  request(request_),
  ng_release_handler(ng_release_handler_),
  cu_cp_ue_ctxt_release_handler(cu_cp_ue_ctxt_release_handler_),
  logger(logger_)
{
}


void ue_amf_context_release_request_routine::operator()(coro_context<async_task<void>>& ctx)
{
  CORO_BEGIN(ctx);


  if (ng_release_handler) {
    // Notify NGAP to request a release from the AMF.
    // Notify NGAP to request a release from the AMF.
    CORO_AWAIT_VALUE(amf_ue_release_requested, ng_release_handler->handle_ue_context_release_request(request));
  }


  if (not ng_release_handler or not amf_ue_release_requested) {
    logger.debug("ue={}: Skipping NG UE Context Release Request. Cause: {}",
                 request.ue_index,
                 ng_release_handler ? "UE does not have an NG UE context" : "NGAP for UE not found");

    // If NGAP release request was not sent to AMF, release UE from DU processor, RRC and F1AP.

    // If NGAP release request was not sent to AMF, release UE from DU processor, RRC and F1AP.
    CORO_AWAIT(cu_cp_ue_ctxt_release_handler.handle_ue_context_release_command({request.ue_index, request.cause}));
  }


  CORO_RETURN();
}
