// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/mobility/conditional_handover_cancellation_routine.h  (41 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../../ue_manager/ue_manager_impl.h"
#include "../../xnap_repository.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// \brief Cancels CHO if the UE never executes it after the execution timer fires.
///
/// Sends an RRCReconfiguration removing the conditional reconfig from the UE, cancels each candidate's RRC
/// reconfiguration transaction and clears the source CHO context.

/// \brief Cancels CHO if the UE never executes it after the execution timer fires.
///
/// Sends an RRCReconfiguration removing the conditional reconfig from the UE, cancels each candidate's RRC
/// reconfiguration transaction and clears the source CHO context.
class conditional_handover_cancellation_routine
{
public:
  conditional_handover_cancellation_routine(cu_cp_ue_index_t        source_ue_index,
                                            ue_manager&             ue_mng,
                                            xnap_repository*        xnap_db,
                                            ocudulog::basic_logger& logger);


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "CHO Cancellation Routine"; }


private:
  const cu_cp_ue_index_t  source_ue_index;
  ue_manager&             ue_mng;
  xnap_repository*        xnap_db;
  ocudulog::basic_logger& logger;


  cu_cp_ue*                             source_ue      = nullptr;
  bool                                  removal_result = false;
  rrc_reconfiguration_procedure_request removal_request;
};


} // namespace ocudu::ocucp
