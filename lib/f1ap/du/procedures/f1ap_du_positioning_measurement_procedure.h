// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_positioning_measurement_procedure.h  (43 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/f1ap/f1ap.h"
#include "ocudu/asn1/f1ap/f1ap_pdu_contents.h"
#include "ocudu/f1ap/du/f1ap_du_positioning_handler.h"
#include "ocudu/f1ap/f1ap_message_notifier.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace odu {


class f1ap_du_configurator;
class f1ap_du_ue;


class f1ap_du_positioning_measurement_procedure
{
public:
  f1ap_du_positioning_measurement_procedure(const asn1::f1ap::positioning_meas_request_s& msg_,
                                            f1ap_du_positioning_handler&                  du_mng_,
                                            f1ap_message_notifier&                        cu_notifier_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  bool                                     validate_request() const;
  async_task<du_positioning_meas_response> request_positioning_measurement();
  void                                     send_response() const;
  void                                     send_failure() const;


  const asn1::f1ap::positioning_meas_request_s msg;
  f1ap_du_positioning_handler&                 du_mng;
  f1ap_message_notifier&                       cu_notifier;
  ocudulog::basic_logger&                      logger;


  du_positioning_meas_response du_result;
};


} // namespace odu
} // namespace ocudu
