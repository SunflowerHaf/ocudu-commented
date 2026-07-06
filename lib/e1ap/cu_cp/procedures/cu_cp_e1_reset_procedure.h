// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/cu_cp/procedures/cu_cp_e1_reset_procedure.h  (44 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "cu_cp/procedures/e1ap_transaction_manager.h"
#include "cu_cp/ue_context/e1ap_cu_cp_ue_context.h"
#include "ocudu/e1ap/common/e1ap_common.h"
#include "ocudu/e1ap/cu_cp/e1ap_configuration.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// \brief Handle the CU-CP initiated E1 Reset Procedure as per TS 37.483 section 8.2.1.

/// \brief Handle the CU-CP initiated E1 Reset Procedure as per TS 37.483 section 8.2.1.
class cu_cp_e1_reset_procedure
{
public:
  cu_cp_e1_reset_procedure(const e1ap_configuration& e1ap_cfg_,
                           const cu_cp_reset&        reset_,
                           e1ap_message_notifier&    pdu_notifier_,
                           e1ap_transaction_manager& ev_mng_,
                           e1ap_ue_context_list&     ue_ctxt_list_,
                           ocudulog::basic_logger&   logger_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  const char* name() const { return "E1 Reset Procedure"; }


  bool send_e1_reset();


  const e1ap_configuration  e1ap_cfg;
  const cu_cp_reset         reset;
  e1ap_message_notifier&    pdu_notifier;
  e1ap_transaction_manager& ev_mng;
  e1ap_ue_context_list&     ue_ctxt_list;
  ocudulog::basic_logger&   logger;


  e1ap_transaction transaction;
};


} // namespace ocudu::ocucp
