// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_ue_context_release_procedure.h  (45 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_context/f1ap_du_ue.h"
#include "../ue_context/f1ap_du_ue_manager.h"
#include "ocudu/asn1/f1ap/f1ap.h"


namespace ocudu {
namespace odu {


struct f1ap_du_context;


class f1ap_du_ue_context_release_procedure
{
public:
  f1ap_du_ue_context_release_procedure(const asn1::f1ap::ue_context_release_cmd_s& msg_,
                                       f1ap_du_ue_manager&                         ues,
                                       const f1ap_du_context&                      ctxt_,
                                       timer_factory                               timers_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  const char* name() const { return "UE Context Release"; }


  void send_ue_context_release_complete();


  async_task<bool> handle_rrc_container();


  const asn1::f1ap::ue_context_release_cmd_s msg;
  f1ap_du_ue&                                ue;
  ocudulog::basic_logger&                    logger = ocudulog::fetch_basic_logger("DU-F1");
  f1ap_message_notifier&                     cu_msg_notifier; // used after the UE context as been released.
  const f1ap_du_context&                     du_ctxt;
  timer_factory                              timers;


  std::chrono::milliseconds rem_timeout{0};
  bool                      success = false;
};


} // namespace odu
} // namespace ocudu
