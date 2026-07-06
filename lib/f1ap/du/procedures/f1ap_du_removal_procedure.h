// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_removal_procedure.h  (44 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../f1ap_du_connection_handler.h"
#include "f1ap_du_event_manager.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace odu {


struct f1ap_du_context;

/// This coroutines handles the F1 removal procedure as per TS 38.473, 8.2.8.

/// This coroutines handles the F1 removal procedure as per TS 38.473, 8.2.8.
class f1ap_du_removal_procedure
{
public:
  f1ap_du_removal_procedure(f1ap_du_connection_handler& du_conn_handler,
                            f1ap_message_notifier&      tx_pdu_notifier,
                            f1ap_event_manager&         ev_mng,
                            f1ap_du_context&            du_ctxt);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  const char* name() const { return "F1 Removal"; }


  void send_f1_removal_request();


  void handle_f1_removal_response();


  f1ap_du_connection_handler& du_conn_handler;
  f1ap_message_notifier&      cu_notifier;
  f1ap_event_manager&         ev_mng;
  f1ap_du_context&            du_ctxt;
  ocudulog::basic_logger&     logger;


  f1ap_transaction transaction;
};


} // namespace odu
} // namespace ocudu
