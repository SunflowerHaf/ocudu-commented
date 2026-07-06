// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/cu_up/procedures/e1ap_cu_up_release_procedure.h  (42 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../e1ap_cu_up_connection_handler.h"
#include "common/e1ap_logger.h"
#include "e1ap_cu_up_event_manager.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace ocuup {

/// This coroutines handles the E1AP CU UP release procedure as per TS 37.483, 8.2.7.2.2.

/// This coroutines handles the E1AP CU UP release procedure as per TS 37.483, 8.2.7.2.2.
class e1ap_cu_up_release_procedure
{
public:
  e1ap_cu_up_release_procedure(e1ap_cu_up_connection_handler& cu_up_conn_handler_,
                               e1ap_message_notifier&         tx_pdu_notifier_,
                               e1ap_event_manager&            ev_mng_,
                               e1ap_logger&                   logger_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  const char* name() const { return "E1AP CU-UP Release Procedure"; }


  void send_e1ap_release_request();


  void handle_e1ap_release_response();


  e1ap_cu_up_connection_handler& cu_up_conn_handler;
  e1ap_message_notifier&         cu_notifier;
  e1ap_event_manager&            ev_mng;
  e1ap_logger&                   logger;


  e1ap_transaction transaction;
};


} // namespace ocuup
} // namespace ocudu
