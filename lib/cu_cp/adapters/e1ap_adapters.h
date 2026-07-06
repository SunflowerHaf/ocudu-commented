// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/adapters/e1ap_adapters.h  (64 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../cu_cp_impl_interface.h"
#include "ocudu/e1ap/cu_cp/e1ap_cu_cp.h"


namespace ocudu::ocucp {

/// Adapter between E1AP and CU-CP

/// Adapter between E1AP and CU-CP
class e1ap_cu_cp_adapter : public e1ap_cu_cp_notifier
{
public:
  void connect_cu_cp(cu_cp_e1ap_event_handler& cu_cp_handler_) { cu_cp_handler = &cu_cp_handler_; }


  bool schedule_async_task(cu_cp_ue_index_t ue_index, async_task<void> task) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    return cu_cp_handler->schedule_ue_task(ue_index, std::move(task));
  }


  void on_bearer_context_release_request_received(const cu_cp_bearer_context_release_request& msg) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    cu_cp_handler->handle_bearer_context_release_request(msg);
  }


  void on_bearer_context_inactivity_notification_received(const e1ap_inactivity_notification& msg) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    cu_cp_handler->handle_bearer_context_inactivity_notification(msg);
  }


  void on_dl_data_notification_received(cu_cp_ue_index_t ue_index) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    cu_cp_handler->handle_dl_data_notification(ue_index);
  }


  async_task<void> on_ue_release_required(const cu_cp_ue_context_release_request& request) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    return cu_cp_handler->handle_ue_context_release(request);
  }


  void on_e1_release_request_received(cu_cp_cu_up_index_t cu_up_index) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "E1AP handler must not be nullptr");
    cu_cp_handler->handle_e1_release_request(cu_up_index);
  }


  async_task<void> on_transaction_info_loss(const ue_transaction_info_loss_event& ev) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "E1AP handler must not be nullptr");
    return cu_cp_handler->handle_transaction_info_loss(ev);
  }


private:
  cu_cp_e1ap_event_handler* cu_cp_handler = nullptr;
};


} // namespace ocudu::ocucp
