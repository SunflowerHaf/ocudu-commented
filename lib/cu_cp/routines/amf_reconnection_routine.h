// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/amf_reconnection_routine.h  (42 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ngap_repository.h"
#include "ocudu/cu_cp/cu_cp_configuration.h"
#include "ocudu/ngap/ngap.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace ocucp {


async_task<bool>
start_amf_reconnection(ngap_interface& ngap, timer_factory timers, std::chrono::milliseconds reconnection_retry_time);

/// \brief Handles the reconnection between the CU-CP and AMF.

/// \brief Handles the reconnection between the CU-CP and AMF.
class amf_reconnection_routine
{
public:
  amf_reconnection_routine(ngap_interface&           ngap_,
                           timer_factory             timers,
                           std::chrono::milliseconds reconnection_retry_time_);


  static std::string name() { return "AMF Reconnection Routine"; }


  void operator()(coro_context<async_task<bool>>& ctx);


private:
  ngap_interface&         ngap;
  ocudulog::basic_logger& logger;


  unique_timer              amf_tnl_connection_retry_timer;
  std::chrono::milliseconds reconnection_retry_time;


  ngap_ng_setup_result result_msg = {};
  bool                 success    = false;
};


} // namespace ocucp
} // namespace ocudu
