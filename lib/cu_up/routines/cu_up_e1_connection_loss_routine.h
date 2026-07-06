// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_up/routines/cu_up_e1_connection_loss_routine.h  (45 lines)
//
// LIBRARY: lib/cu_up
// O-RAN Central Unit User Plane core: the PDCP layer (ciphering, integrity, header compression), SDAP (QoS flow to DRB mapping), F1-U endpoint management, N3 GTP-U endpoint, and the O-CU-UP factory. One CU-UP instance handles all UEs' user-plane data.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_manager.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/async/async_task.h"
#include <string>
#include <vector>


namespace ocudu::ocuup {


class cu_up_e1_connection_loss_routine
{
public:
  cu_up_e1_connection_loss_routine(gnb_cu_up_id_t           cu_up_id_,
                                   std::string              cu_up_name_,
                                   std::vector<std::string> plmns_,
                                   std::atomic<bool>&       stop_command,
                                   e1ap_interface&          e1ap_,
                                   ue_manager&              ue_mng_,
                                   timer_manager&           timers,
                                   task_executor&           ctrl_exec);


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "CU-UP E1 connection loss routine"; }


private:
  gnb_cu_up_id_t           cu_up_id;
  std::string              cu_up_name;
  std::vector<std::string> plmns;
  std::atomic<bool>&       stop_command;


  unique_timer            retry_timer;
  e1ap_interface&         e1ap;
  ue_manager&             ue_mng;
  ocudulog::basic_logger& logger;


  bool reconnected;
};


} // namespace ocudu::ocuup
