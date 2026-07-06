// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_gnbdu_config_update_procedure.h  (41 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "f1ap_du_event_manager.h"
#include "ocudu/f1ap/du/f1ap_du_connection_manager.h"
#include "ocudu/f1ap/f1ap_message_notifier.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace odu {

/// DU config update procedure for the gNB-DU as per TS 38.473, 8.2.4.

/// DU config update procedure for the gNB-DU as per TS 38.473, 8.2.4.
class f1ap_du_gnbdu_config_update_procedure
{
public:
  f1ap_du_gnbdu_config_update_procedure(const gnbdu_config_update_request& request_,
                                        f1ap_message_notifier&             cu_notif_,
                                        f1ap_event_manager&                ev_mng_);


  void operator()(coro_context<async_task<gnbdu_config_update_response>>& ctx);


private:
  const char* name() const { return "gNB-DU Configuration Update"; }


  void send_gnbdu_cu_update_request();


  gnbdu_config_update_response generate_du_response() const;


  const gnbdu_config_update_request request;
  f1ap_message_notifier&            cu_notif;
  f1ap_event_manager&               ev_mng;
  ocudulog::basic_logger&           logger;


  f1ap_transaction transaction;
};


} // namespace odu
} // namespace ocudu
