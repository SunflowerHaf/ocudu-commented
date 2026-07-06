// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/ue_context/f1ap_du_ue.h  (48 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "f1ap_ue_context.h"
#include "ue_bearer_manager.h"
#include "ocudu/adt/slotted_array.h"
#include "ocudu/asn1/f1ap/f1ap_pdu_contents_ue.h"
#include "ocudu/f1ap/du/f1ap_du.h"
#include "ocudu/f1ap/f1ap_ue_id_types.h"
#include "ocudu/ran/du_types.h"


namespace ocudu {
namespace odu {


struct f1ap_du_context;


class f1ap_du_ue
{
public:
  f1ap_du_ue(du_ue_index_t          ue_index_,
             gnb_du_ue_f1ap_id_t    gnb_f1ap_du_ue_id_,
             f1ap_du_configurator&  du_handler_,
             f1ap_message_notifier& f1ap_msg_notifier_,
             task_executor&         ctrl_exec,
             task_executor&         ue_exec,
             timer_manager&         timers) :
    context(ue_index_, gnb_f1ap_du_ue_id_),
    f1ap_msg_notifier(f1ap_msg_notifier_),
    du_handler(du_handler_),
    bearers(context, f1ap_msg_notifier, du_handler, ctrl_exec, ue_exec, timers)
  {
  }


  f1ap_ue_context        context;
  f1ap_message_notifier& f1ap_msg_notifier;
  f1ap_du_configurator&  du_handler;
  ue_bearer_manager      bearers;

  /// \brief Handles UE CONTEXT MODIFICATION REQUEST as per TS38.473, Section 8.3.2.

  /// \brief Handles UE CONTEXT MODIFICATION REQUEST as per TS38.473, Section 8.3.2.
  void handle_ue_context_modification_request(const asn1::f1ap::ue_context_mod_request_s& msg,
                                              const f1ap_du_context&                      ctxt_);
};


} // namespace odu
} // namespace ocudu
