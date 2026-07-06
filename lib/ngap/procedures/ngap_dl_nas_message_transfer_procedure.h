// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ngap/procedures/ngap_dl_nas_message_transfer_procedure.h  (39 lines)
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
#include "ocudu/ngap/ngap_nas.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace ocucp {


class ngap_dl_nas_message_transfer_procedure
{
public:
  ngap_dl_nas_message_transfer_procedure(const ngap_dl_nas_transport_message&         msg_,
                                         ngap_rrc_ue_notifier&                        rrc_ue_notifier_,
                                         ngap_ue_radio_capability_management_handler& ngap_handler_,
                                         ngap_ue_logger&                              logger_);


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "DL NAS Message Transfer Procedure"; }


private:
  // results senders
  // results senders
  void send_pdu_to_rrc_ue();
  void send_ue_radio_capability_info_indication();


  ngap_dl_nas_transport_message                msg;
  ngap_rrc_ue_notifier&                        rrc_ue_notifier;
  ngap_ue_radio_capability_management_handler& ngap_handler;
  ngap_ue_logger&                              logger;
};


} // namespace ocucp
} // namespace ocudu
