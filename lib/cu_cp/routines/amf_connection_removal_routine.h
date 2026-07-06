// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/amf_connection_removal_routine.h  (35 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ngap_repository.h"
#include "ocudu/ngap/ngap.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {


async_task<void> start_amf_connection_removal(ngap_repository&                                          ngap_db,
                                              std::unordered_map<cu_cp_amf_index_t, std::atomic<bool>>& amfs_connected);

/// \brief Handles the removal of the connection between the CU-CP and AMF.

/// \brief Handles the removal of the connection between the CU-CP and AMF.
class amf_connection_removal_routine
{
public:
  amf_connection_removal_routine(ngap_repository&                                          ngap_db_,
                                 std::unordered_map<cu_cp_amf_index_t, std::atomic<bool>>& amfs_connected_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  std::unordered_map<cu_cp_amf_index_t, std::atomic<bool>>& amfs_connected;
  std::map<cu_cp_amf_index_t, ngap_interface*>              ngaps;
  ocudulog::basic_logger&                                   logger;


  std::map<cu_cp_amf_index_t, ngap_interface*>::iterator ngap_it;
  cu_cp_amf_index_t                                      amf_index = cu_cp_amf_index_t::invalid;
  ngap_interface*                                        ngap      = nullptr;
};


} // namespace ocudu::ocucp
