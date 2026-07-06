// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/cu_cp/ue_context/f1ap_cu_ue_context.cpp  (40 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "f1ap_cu_ue_context.h"
#include "ocudu/asn1/f1ap/common.h"
#include "ocudu/f1ap/f1ap_message.h"


using namespace ocudu;
using namespace ocucp;


void f1ap_ue_context::handle_dl_rrc_message(const f1ap_dl_rrc_message& msg, f1ap_message_notifier& msg_notifier)
{
  ocudu_sanity_check(ue_ids.du_ue_f1ap_id && ue_ids.du_ue_f1ap_id != gnb_du_ue_f1ap_id_t::invalid,
                     "Invalid gNB-DU-UE-F1AP-Id");


  asn1::f1ap::dl_rrc_msg_transfer_s dl_rrc_msg = {};
  dl_rrc_msg->gnb_cu_ue_f1ap_id                = gnb_cu_ue_f1ap_id_to_uint(ue_ids.cu_ue_f1ap_id);
  dl_rrc_msg->gnb_du_ue_f1ap_id                = gnb_du_ue_f1ap_id_to_uint(*ue_ids.du_ue_f1ap_id);
  dl_rrc_msg->srb_id                           = static_cast<uint8_t>(srb_id_to_uint(msg.srb_id));
  dl_rrc_msg->rrc_container                    = msg.rrc_container.copy();


  if (pending_old_ue_id.has_value()) {
    // If the UE requests to reestablish RRC connection in the last serving gNB-DU, the DL RRC MESSAGE TRANSFER message
    // shall include old gNB-DU UE F1AP ID, see TS 38.401 section 8.7.
    // If the UE requests to reestablish RRC connection in the last serving gNB-DU, the DL RRC MESSAGE TRANSFER message
    // shall include old gNB-DU UE F1AP ID, see TS 38.401 section 8.7.
    dl_rrc_msg->old_gnb_du_ue_f1ap_id_present = true;
    dl_rrc_msg->old_gnb_du_ue_f1ap_id         = gnb_du_ue_f1ap_id_to_uint(pending_old_ue_id.value());


    pending_old_ue_id.reset();
  }

  // Pack message into PDU.

  // Pack message into PDU.
  f1ap_message f1ap_dl_rrc_msg;
  f1ap_dl_rrc_msg.pdu.set_init_msg();
  f1ap_dl_rrc_msg.pdu.init_msg().load_info_obj(ASN1_F1AP_ID_DL_RRC_MSG_TRANSFER);
  f1ap_dl_rrc_msg.pdu.init_msg().value.dl_rrc_msg_transfer() = std::move(dl_rrc_msg);

  // Send DL RRC message.

  // Send DL RRC message.
  msg_notifier.on_new_message(f1ap_dl_rrc_msg);
}
