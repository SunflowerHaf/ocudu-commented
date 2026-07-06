// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/task_schedulers/xnap_task_scheduler.h  (32 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/support/async/fifo_async_task_scheduler.h"
#include <map>


namespace ocudu::ocucp {

/// \brief Service provided by CU-CP to schedule async tasks for a given XN-C peer.

/// \brief Service provided by CU-CP to schedule async tasks for a given XN-C peer.
class xnap_task_scheduler
{
public:
  explicit xnap_task_scheduler(uint16_t max_nof_xnc_peers, ocudulog::basic_logger& logger_);
  ~xnap_task_scheduler() = default;


  void handle_xnc_async_task(xnc_peer_index_t xnc_index, async_task<void>&& task);


  void clear_pending_tasks(xnc_peer_index_t xnc_index);


private:
  ocudulog::basic_logger& logger;

  // task event loops indexed by xnc_peer_index

  // task event loops indexed by xnc_peer_index
  std::map<xnc_peer_index_t, fifo_async_task_scheduler> xnc_ctrl_loop;
};


} // namespace ocudu::ocucp
