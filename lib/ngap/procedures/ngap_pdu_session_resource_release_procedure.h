// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ngap/procedures/ngap_pdu_session_resource_release_procedure.h  (38 lines)
//
// LIBRARY: lib/ngap
// NG Application Protocol (NGAP, TS 38.413): the N2 control-plane between the gNB and the 5G Core AMF. Handles UE registration, PDU session setup, handover, paging, NAS message transport, and NG Setup. Implements full ASN.1 encode/decode + all NGAP elementary procedures.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_context/ngap_ue_context.h"
#include "ocudu/ngap/ngap.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {


class ngap_pdu_session_resource_release_procedure
{
public:
  ngap_pdu_session_resource_release_procedure(const ngap_pdu_session_resource_release_command& command_,
                                              const ngap_ue_ids&                               ue_ids_,
                                              ngap_cu_cp_notifier&                             cu_cp_notifier_,
                                              ngap_message_notifier&                           amf_notifier_,
                                              ngap_ue_logger&                                  logger_);


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "PDU Session Resource Release Procedure"; }


private:
  // Result senders.
  // Result senders.
  bool validate_and_send_response();


  ngap_pdu_session_resource_release_command  command;
  const ngap_ue_ids                          ue_ids;
  ngap_pdu_session_resource_release_response response;
  ngap_cu_cp_notifier&                       cu_cp_notifier;
  ngap_message_notifier&                     amf_notifier;
  ngap_ue_logger&                            logger;
};


} // namespace ocudu::ocucp
