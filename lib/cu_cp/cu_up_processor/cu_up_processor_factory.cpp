// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_up_processor/cu_up_processor_factory.cpp  (23 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "cu_up_processor_factory.h"
#include "cu_up_processor_impl.h"
#include "ocudu/support/async/async_task_scheduler.h"

/// Notice this would be the only place were we include concrete class implementation files.


/// Notice this would be the only place were we include concrete class implementation files.

using namespace ocudu;
using namespace ocucp;


std::unique_ptr<cu_up_processor>
ocudu::ocucp::create_cu_up_processor(const cu_up_processor_config_t cu_up_processor_config_,
                                     e1ap_message_notifier&         e1ap_notifier_,
                                     e1ap_cu_cp_notifier&           cu_cp_notifier_,
                                     async_task_scheduler&          common_task_sched_)
{
  auto cu_up_processor = std::make_unique<cu_up_processor_impl>(
      cu_up_processor_config_, e1ap_notifier_, cu_cp_notifier_, common_task_sched_);
  return cu_up_processor;
}
