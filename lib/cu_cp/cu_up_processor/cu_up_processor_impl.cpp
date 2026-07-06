// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_up_processor/cu_up_processor_impl.cpp  (101 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "cu_up_processor_impl.h"
#include "ocudu/e1ap/cu_cp/e1ap_cu_cp_factory.h"
#include "ocudu/support/async/async_task_scheduler.h"


using namespace ocudu;
using namespace ocucp;

/// Adapter between E1AP and CU-UP processor

/// Adapter between E1AP and CU-UP processor
class cu_up_processor_impl::e1ap_cu_up_processor_adapter : public e1ap_cu_up_processor_notifier
{
public:
  e1ap_cu_up_processor_adapter(cu_up_processor_impl& parent_, async_task_scheduler& common_task_sched_) :
    parent(parent_), common_task_sched(&common_task_sched_)
  {
  }


  void on_cu_up_e1_setup_request_received(const cu_up_e1_setup_request& msg) override
  {
    parent.handle_cu_up_e1_setup_request(msg);
  }


  bool schedule_async_task(async_task<void> task) override { return common_task_sched->schedule(std::move(task)); }


private:
  cu_up_processor_impl& parent;
  async_task_scheduler* common_task_sched = nullptr;
};


cu_up_processor_impl::cu_up_processor_impl(const cu_up_processor_config_t cu_up_processor_config_,
                                           e1ap_message_notifier&         e1ap_notifier_,
                                           e1ap_cu_cp_notifier&           cu_cp_notifier_,
                                           async_task_scheduler&          common_task_sched_) :
  cfg(cu_up_processor_config_),
  e1ap_notifier(e1ap_notifier_),
  cu_cp_notifier(cu_cp_notifier_),
  e1ap_ev_notifier(std::make_unique<e1ap_cu_up_processor_adapter>(*this, common_task_sched_))
{
  context.cu_cp_name  = cfg.name;
  context.cu_up_index = cfg.cu_up_index;

  // create e1

  // create e1
  e1ap = create_e1ap(cfg.cu_cp_cfg.e1ap,
                     context.cu_up_index,
                     e1ap_notifier,
                     *e1ap_ev_notifier,
                     cu_cp_notifier,
                     *cfg.cu_cp_cfg.services.timers,
                     *cfg.cu_cp_cfg.services.cu_cp_executor,
                     cfg.cu_cp_cfg.admission.max_nof_ues);
}


void cu_up_processor_impl::stop(cu_cp_ue_index_t ue_idx)
{
  // Cancel E1AP running tasks.
  // Cancel E1AP running tasks.
  e1ap->cancel_ue_tasks(ue_idx);
}


void cu_up_processor_impl::handle_cu_up_e1_setup_request(const cu_up_e1_setup_request& msg)
{
  if (msg.gnb_cu_up_name.has_value()) {
    context.cu_up_name = msg.gnb_cu_up_name.value();
  }
  context.id = msg.gnb_cu_up_id;

  // TODO: handle response

  // send setup response

  // TODO: handle response

  // send setup response
  send_cu_up_e1_setup_response();
}

/// Sender for F1AP messages

/// Sender for F1AP messages
void cu_up_processor_impl::send_cu_up_e1_setup_response()
{
  cu_up_e1_setup_response response;
  response.success        = true;
  response.gnb_cu_cp_name = context.cu_cp_name;


  e1ap->handle_cu_up_e1_setup_response(response);
}


void cu_up_processor_impl::send_cu_up_e1_setup_failure(e1ap_cause_t cause)
{
  cu_up_e1_setup_response response;
  response.success = false;
  response.cause   = cause;
  e1ap->handle_cu_up_e1_setup_response(response);
}


async_task<void> cu_up_processor_impl::handle_cu_cp_e1_reset_message(const cu_cp_reset& reset)
{
  return e1ap->handle_cu_cp_e1_reset_message(reset);
}


void cu_up_processor_impl::update_ue_index(cu_cp_ue_index_t ue_index, cu_cp_ue_index_t old_ue_index)
{
  e1ap->update_ue_context(ue_index, old_ue_index);
}
