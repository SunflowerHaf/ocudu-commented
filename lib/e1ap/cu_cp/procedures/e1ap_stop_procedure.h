// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/cu_cp/procedures/e1ap_stop_procedure.h  (31 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace ocucp {


class e1ap_cu_cp_notifier;
class e1ap_ue_context_list;

/// Procedure called during the shutdown of the E1AP to clear up existing transactions.

/// Procedure called during the shutdown of the E1AP to clear up existing transactions.
class e1ap_stop_procedure
{
public:
  e1ap_stop_procedure(e1ap_cu_cp_notifier& cu_cp_notifier_, e1ap_ue_context_list& ue_ctxt_list_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  async_task<void> handle_transaction_info_loss();


  e1ap_cu_cp_notifier&  cu_cp_notifier;
  e1ap_ue_context_list& ue_ctxt_list;
};


} // namespace ocucp
} // namespace ocudu
