// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_cp_controller/xnc_connection_manager.h  (71 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../xnap_repository.h"
#include "ocudu/support/async/async_task_scheduler.h"
#include "ocudu/xnap/cu_cp_xnc_handler.h"
#include "ocudu/xnap/gateways/xnc_connection_gateway.h"
#include "ocudu/xnap/xnap_configuration.h"
#include <condition_variable>
#include <mutex>


namespace ocudu::ocucp {


class cu_cp_routine_manager;
struct cu_cp_configuration;


class xnc_connection_manager : public cu_cp_xnc_handler
{
public:
  xnc_connection_manager(xnap_repository&                            xnaps_,
                         const std::vector<xnc_connection_gateway*>& xnc_gws_,
                         timer_manager&                              timers_,
                         task_executor&                              cu_cp_exec_,
                         async_task_scheduler&                       common_task_sched_);


  void start(const xnap_configuration& xnap_cfg);

  /// Register the XnAP gateway used for outbound connect/reconnect to the given peer.

  /// Register the XnAP gateway used for outbound connect/reconnect to the given peer.
  void register_peer_gateway(xnc_peer_index_t xnc_idx, xnc_connection_gateway* gateway);


  std::unique_ptr<xnap_message_notifier>
  handle_new_xnc_cu_cp_connection(std::unique_ptr<xnap_message_notifier> xnap_tx_pdu_notifier,
                                  const sctp_association_info&           assoc_info) override;


  void handle_xnc_gw_connection_closed(xnc_peer_index_t xnc_idx);


  void stop();


private:
  void reconnect_peer(xnc_peer_index_t                            xnc_idx,
                      const std::vector<transport_layer_address>& peer_addrs,
                      xnc_connection_gateway*                     xnc_gw);


  class shared_xnc_connection_context;
  class xnc_gw_to_cu_cp_pdu_adapter;


  xnap_repository&                     xnaps;
  std::vector<xnc_connection_gateway*> xnc_gws;
  timer_manager&                       timers;
  task_executor&                       cu_cp_exec;
  async_task_scheduler&                common_task_sched;
  ocudulog::basic_logger&              logger;

  /// XNAP configuration used to recreate XNAP instances after connection loss.

  /// XNAP configuration used to recreate XNAP instances after connection loss.
  xnap_configuration xnap_cfg;

  /// XNAP peer to Xn-C gateway mapping, used for outbound connect/reconnect to that peer.

  /// XNAP peer to Xn-C gateway mapping, used for outbound connect/reconnect to that peer.
  std::map<xnc_peer_index_t, xnc_connection_gateway*> xnc_gateways;


  std::map<xnc_peer_index_t, std::shared_ptr<shared_xnc_connection_context>> xnc_connections;


  std::atomic<bool>       stopped{false};
  std::mutex              stop_mutex;
  std::condition_variable stop_cvar;
  bool                    stop_completed = false;
};


} // namespace ocudu::ocucp
