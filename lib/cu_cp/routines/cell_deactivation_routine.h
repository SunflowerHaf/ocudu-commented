// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/routines/cell_deactivation_routine.h  (66 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../du_processor/du_processor.h"
#include "../ue_manager/ue_manager_impl.h"
#include "ocudu/adt/expected.h"
#include "ocudu/f1ap/cu_cp/f1ap_cu_configuration_update.h"
#include "ocudu/support/async/eager_async_task.h"
#include <unordered_set>


namespace ocudu::ocucp {

/// \brief Handles the release of the connected UEs and the deactivation of the cell.

/// \brief Handles the release of the connected UEs and the deactivation of the cell.
class cell_deactivation_routine
{
public:
  cell_deactivation_routine(const cu_cp_configuration&        cu_cp_cfg_,
                            const std::vector<plmn_identity>& plmns_,
                            du_processor_repository&          du_db_,
                            cu_cp_ue_context_release_handler& ue_release_handler_,
                            ue_manager&                       ue_mng_,
                            ocudulog::basic_logger&           logger_);
  ~cell_deactivation_routine() = default;


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "Cell Deactivation Routine"; }


  void trigger_context_release_for_all_ues();


  void get_remaining_plmns(const du_cell_configuration& cell_cfg);


  bool generate_gnb_cu_configuration_update();


private:
  const cu_cp_configuration&        cu_cp_cfg;
  const std::vector<plmn_identity>  plmns;
  du_processor_repository&          du_db;
  cu_cp_ue_context_release_handler& ue_release_handler;
  ue_manager&                       ue_mng;
  ocudulog::basic_logger&           logger;

  // (Sub-)Routine requests.

  // (Sub-)Routine requests.
  f1ap_gnb_cu_configuration_update f1ap_cu_cfg_update;

  // (Sub-)Routine results.

  // (Sub-)Routine results.
  f1ap_gnb_cu_configuration_update_response f1ap_cu_cfg_update_response;
  bool                                      routine_success = true;


  using ue_release_task_t = eager_async_task<expected<cu_cp_ue_context_release_complete>>;
  std::vector<ue_release_task_t>           ue_release_tasks;
  std::vector<ue_release_task_t>::iterator ue_release_task_it;


  std::unordered_set<plmn_identity>       remaining_plmns;
  std::vector<cu_cp_du_index_t>           du_indexes;
  std::vector<cu_cp_du_index_t>::iterator du_idx_it;
  du_processor*                           du_proc = nullptr;


  std::chrono::steady_clock::time_point proc_start_tp;
  std::chrono::steady_clock::time_point ue_release_finish_tp;
};


} // namespace ocudu::ocucp
