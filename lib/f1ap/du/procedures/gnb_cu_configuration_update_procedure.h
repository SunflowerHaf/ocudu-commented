// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/gnb_cu_configuration_update_procedure.h  (41 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/f1ap/f1ap_pdu_contents.h"
#include "ocudu/f1ap/du/f1ap_du.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {


class f1ap_message_notifier;


namespace odu {


class f1ap_du_configurator;


class gnb_cu_configuration_update_procedure
{
public:
  gnb_cu_configuration_update_procedure(const asn1::f1ap::gnb_cu_cfg_upd_s& msg_,
                                        f1ap_du_configurator&               du_mng_,
                                        f1ap_message_notifier&              cu_notif_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  gnbcu_config_update_request request_du_update();


  void send_response();


  const asn1::f1ap::gnb_cu_cfg_upd_s request;
  f1ap_du_configurator&              du_mng;
  f1ap_message_notifier&             cu_notif;


  gnbcu_config_update_response du_resp;
};


} // namespace odu
} // namespace ocudu
