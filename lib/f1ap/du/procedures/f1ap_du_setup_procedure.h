// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_setup_procedure.h  (58 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "f1ap_du_event_manager.h"
#include "ocudu/adt/byte_buffer.h"
#include "ocudu/f1ap/du/f1ap_du.h"
#include "ocudu/f1ap/f1ap_message_notifier.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace odu {


struct f1ap_du_context;

/// F1 Setup Procedure for the gNB-DU as per TS 38.473, 8.2.3.

/// F1 Setup Procedure for the gNB-DU as per TS 38.473, 8.2.3.
class f1ap_du_setup_procedure
{
public:
  f1ap_du_setup_procedure(const f1_setup_request_message& request_,
                          f1ap_message_notifier&          cu_notif_,
                          f1ap_event_manager&             ev_mng_,
                          timer_factory&                  timers,
                          f1ap_du_context&                du_ctxt_);


  void operator()(coro_context<async_task<f1_setup_result>>& ctx);


private:
  const char* name() const { return "F1 Setup"; }

  /// Send F1 SETUP REQUEST to CU.

  /// Send F1 SETUP REQUEST to CU.
  void send_f1_setup_request();

  /// Checks whether the DU should attempt again to connect to CU.

  /// Checks whether the DU should attempt again to connect to CU.
  bool retry_required();

  /// Creates procedure result to send back to procedure caller.

  /// Creates procedure result to send back to procedure caller.
  f1_setup_result create_f1_setup_result();


  const f1_setup_request_message request;
  f1ap_message_notifier&         cu_notifier;
  f1ap_event_manager&            ev_mng;
  ocudulog::basic_logger&        logger;
  f1ap_du_context&               du_ctxt;


  unique_timer f1_setup_wait_timer;


  f1ap_transaction     transaction;
  unsigned             f1_setup_retry_no = 0;
  std::chrono::seconds time_to_wait{0};
  /// Packed F1SetupRequest PDU bytes.
  /// Packed F1SetupRequest PDU bytes.
  byte_buffer captured_request;
};


} // namespace odu
} // namespace ocudu
