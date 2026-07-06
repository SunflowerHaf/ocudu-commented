// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/cu_cp/f1ap_cu_factory.cpp  (22 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/f1ap/cu_cp/f1ap_cu_factory.h"
#include "f1ap_cu_impl.h"

/// Notice this would be the only place were we include concrete class implementation files.


/// Notice this would be the only place were we include concrete class implementation files.

using namespace ocudu;
using namespace ocucp;


std::unique_ptr<f1ap_cu> ocudu::ocucp::create_f1ap(const f1ap_configuration&   f1ap_cfg_,
                                                   f1ap_message_notifier&      f1ap_pdu_notifier_,
                                                   f1ap_du_processor_notifier& du_processor_notifier_,
                                                   timer_manager&              timers_,
                                                   task_executor&              ctrl_exec_)
{
  auto f1ap_cu =
      std::make_unique<f1ap_cu_impl>(f1ap_cfg_, f1ap_pdu_notifier_, du_processor_notifier_, timers_, ctrl_exec_);
  return f1ap_cu;
}
