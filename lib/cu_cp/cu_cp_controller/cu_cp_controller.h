// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_cp_controller/cu_cp_controller.h  (73 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ngap_repository.h"
#include "amf_connection_manager.h"
#include "cu_cp_ue_admission_controller.h"
#include "cu_up_connection_manager.h"
#include "du_connection_manager.h"
#include "xnc_connection_manager.h"
#include "ocudu/cu_cp/cu_cp_configuration.h"
#include "ocudu/support/async/async_task_scheduler.h"


namespace ocudu::ocucp {


class cu_up_processor_repository;
class ue_manager;

/// \brief Entity responsible for managing the CU-CP connections to remote nodes and determining whether the CU-CP
/// is in a state to accept new connections.
///
/// In particular, this class is responsible for:
/// - triggering an AMF connection and tracking the status of the connection;
/// - determining whether a new DU setup request should be accepted based on the status of other remote node
/// connections;
/// - determining whether new UEs should be accepted depending on the status of the CU-CP remote connections.

/// \brief Entity responsible for managing the CU-CP connections to remote nodes and determining whether the CU-CP
/// is in a state to accept new connections.
///
/// In particular, this class is responsible for:
/// - triggering an AMF connection and tracking the status of the connection;
/// - determining whether a new DU setup request should be accepted based on the status of other remote node
/// connections;
/// - determining whether new UEs should be accepted depending on the status of the CU-CP remote connections.
class cu_cp_controller : public cu_cp_ue_admission_controller
{
public:
  cu_cp_controller(const cu_cp_configuration&      config_,
                   cu_cp_amf_reconnection_handler& cu_cp_notifier,
                   async_task_scheduler&           common_task_sched_,
                   ngap_repository&                ngaps_,
                   cu_up_processor_repository&     cu_ups_,
                   du_processor_repository&        dus_,
                   xnap_repository&                xncs_,
                   task_executor&                  ctrl_exec);


  void stop();


  amf_connection_manager& amf_connection_handler() { return amf_mng; }


  xnc_connection_manager& xnc_connection_handler() { return xnc_mng; }


  bool handle_du_setup_request(cu_cp_du_index_t du_idx, const std::set<plmn_identity>& plmn_ids);

  /// \brief Determines whether the CU-CP should accept new UE connections.

  /// \brief Determines whether the CU-CP should accept new UE connections.
  bool request_ue_setup() const override;

  /// \brief Determines whether the CU-CP should accept a new UE connection based on its PLMN.

  /// \brief Determines whether the CU-CP should accept a new UE connection based on its PLMN.
  bool is_supported_plmn(const plmn_identity& plmn) const;


  cu_cp_f1c_handler& get_f1c_handler() { return du_mng; }
  cu_cp_e1_handler&  get_e1_handler() { return cu_up_mng; }
  cu_cp_xnc_handler& get_xnc_handler() { return xnc_mng; }


private:
  const cu_cp_configuration& cfg;
  task_executor&             ctrl_exec;
  ocudulog::basic_logger&    logger;


  amf_connection_manager   amf_mng;
  du_connection_manager    du_mng;
  cu_up_connection_manager cu_up_mng;
  xnc_connection_manager   xnc_mng;


  std::mutex mutex;
  bool       running = true;
};


} // namespace ocudu::ocucp
