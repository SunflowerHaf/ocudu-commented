// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/amf_connection_setup_routine.h  (45 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ngap_repository.h"
#include "ocudu/cu_cp/cu_cp_ng_setup_notifier.h"
#include "ocudu/ngap/ngap.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {


async_task<bool> start_amf_connection_setup(ngap_repository&                                          ngap_db,
                                            std::unordered_map<cu_cp_amf_index_t, std::atomic<bool>>& amfs_connected,
                                            cu_cp_ng_setup_complete_notifier* ng_setup_notifier = nullptr);

/// \brief Handles the setup of the connection between the CU-CP and AMF, handling in particular the NG Setup procedure.

/// \brief Handles the setup of the connection between the CU-CP and AMF, handling in particular the NG Setup procedure.
class amf_connection_setup_routine
{
public:
  amf_connection_setup_routine(ngap_repository&                                          ngap_db_,
                               std::unordered_map<cu_cp_amf_index_t, std::atomic<bool>>& amfs_connected_,
                               cu_cp_ng_setup_complete_notifier*                         ng_setup_notifier_ = nullptr);


  void operator()(coro_context<async_task<bool>>& ctx);


private:
  void handle_connection_setup_result();


  ngap_repository&                                          ngap_db;
  std::unordered_map<cu_cp_amf_index_t, std::atomic<bool>>& amfs_connected;
  cu_cp_ng_setup_complete_notifier*                         ng_setup_notifier;
  std::map<cu_cp_amf_index_t, ngap_interface*>              ngaps;
  ocudulog::basic_logger&                                   logger;


  std::map<cu_cp_amf_index_t, ngap_interface*>::iterator ngap_it;
  cu_cp_amf_index_t                                      amf_index = cu_cp_amf_index_t::invalid;
  ngap_interface*                                        ngap      = nullptr;


  ngap_ng_setup_result result_msg = {};
  bool                 success    = false;
};


} // namespace ocudu::ocucp
