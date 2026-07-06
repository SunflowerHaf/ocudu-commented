// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/cu_cp/procedures/f1ap_stop_procedure.h  (31 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace ocucp {


class f1ap_du_processor_notifier;
class f1ap_ue_context_list;

/// Procedure called during the shutdown of the F1AP to clear up existing transactions.

/// Procedure called during the shutdown of the F1AP to clear up existing transactions.
class f1ap_stop_procedure
{
public:
  f1ap_stop_procedure(f1ap_du_processor_notifier& cu_cp_notifier_, f1ap_ue_context_list& ue_ctxt_list_);


  void operator()(coro_context<async_task<void>>& ctx);


private:
  async_task<void> handle_transaction_info_loss();


  f1ap_du_processor_notifier& cu_cp_notifier;
  f1ap_ue_context_list&       ue_ctxt_list;
};


} // namespace ocucp
} // namespace ocudu
