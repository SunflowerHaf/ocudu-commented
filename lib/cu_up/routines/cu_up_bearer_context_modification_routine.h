// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_up/routines/cu_up_bearer_context_modification_routine.h  (34 lines)
//
// LIBRARY: lib/cu_up
// O-RAN Central Unit User Plane core: the PDCP layer (ciphering, integrity, header compression), SDAP (QoS flow to DRB mapping), F1-U endpoint management, N3 GTP-U endpoint, and the O-CU-UP factory. One CU-UP instance handles all UEs' user-plane data.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_context.h"
#include "ocudu/e1ap/cu_up/e1ap_cu_up_bearer_context_update.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace ocuup {


class cu_up_bearer_context_modification_routine
{
public:
  cu_up_bearer_context_modification_routine(ue_context& ue_ctxt, const e1ap_bearer_context_modification_request& msg);


  void operator()(coro_context<async_task<e1ap_bearer_context_modification_response>>& ctx);


  static const char* name() { return "CU-UP bearer context modification routine"; }


private:
  ue_context&                                     ue_ctxt;
  const e1ap_bearer_context_modification_request& msg;
  ocudulog::basic_logger&                         logger;

  // Helper variables

  // Helper variables
  e1ap_bearer_context_modification_response response = {};
  security::sec_as_config                   security_info;
};


} // namespace ocuup
} // namespace ocudu
