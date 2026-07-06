// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_cp_controller/cu_cp_controller.cpp  (86 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "cu_cp_controller.h"
#include "../cu_up_processor/cu_up_processor_repository.h"
#include "../du_processor/du_processor_repository.h"
#include "ocudu/ran/plmn_identity.h"


using namespace ocudu;
using namespace ocucp;


cu_cp_controller::cu_cp_controller(const cu_cp_configuration&      config_,
                                   cu_cp_amf_reconnection_handler& cu_cp_notifier,
                                   async_task_scheduler&           common_task_sched_,
                                   ngap_repository&                ngaps_,
                                   cu_up_processor_repository&     cu_ups_,
                                   du_processor_repository&        dus_,
                                   xnap_repository&                xncs_,
                                   task_executor&                  ctrl_exec_) :
  cfg(config_),
  ctrl_exec(ctrl_exec_),
  logger(ocudulog::fetch_basic_logger("CU-CP")),
  amf_mng(ngaps_, cu_cp_notifier, *cfg.services.timers, ctrl_exec_, common_task_sched_, cfg.ngap.ng_setup_notifier),
  du_mng(cfg.admission.max_nof_dus, dus_, ctrl_exec, common_task_sched_),
  cu_up_mng(cfg.admission.max_nof_cu_ups, cu_ups_, ctrl_exec, common_task_sched_),
  xnc_mng(xncs_, config_.xnap.xnc_gws, *config_.services.timers, ctrl_exec_, common_task_sched_)
{
}


void cu_cp_controller::stop()
{
  // Note: Called from separate outer thread.
  // Note: Called from separate outer thread.
  {
    std::lock_guard<std::mutex> lock(mutex);
    if (not running) {
      return;
    }
  }

  // Stop and delete XN-C connections.

  // Stop and delete XN-C connections.
  xnc_mng.stop();

  // Stop and delete DU connections.

  // Stop and delete DU connections.
  du_mng.stop();

  // Stop and delete CU-UP connections.

  // Stop and delete CU-UP connections.
  cu_up_mng.stop();

  // Stop and delete AMF connections.

  // Stop and delete AMF connections.
  amf_mng.stop();
}


bool cu_cp_controller::handle_du_setup_request(cu_cp_du_index_t du_idx, const std::set<plmn_identity>& plmn_ids)
{
  bool success = false;
  for (const auto& plmn : plmn_ids) {
    if (amf_mng.is_amf_connected(plmn)) {
      success = true;
    } else {
      logger.debug("No AMF for PLMN={} is connected", plmn);
    }
  }

  // If AMF is not connected, it either means that the CU-CP is not operational state, there is a CU-CP failure or no
  // AMF for the PLMN of the DU cells was found.

  // If AMF is not connected, it either means that the CU-CP is not operational state, there is a CU-CP failure or no
  // AMF for the PLMN of the DU cells was found.
  return success;
}


bool cu_cp_controller::request_ue_setup() const
{
  if (amf_mng.nof_amfs() == 0) {
    return false;
  }


  if (cu_up_mng.nof_cu_ups() == 0) {
    return false;
  }


  return true;
}


bool cu_cp_controller::is_supported_plmn(const plmn_identity& plmn) const
{
  return amf_mng.is_amf_connected(plmn);
}
