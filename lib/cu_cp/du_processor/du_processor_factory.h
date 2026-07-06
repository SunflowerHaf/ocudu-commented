// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/du_processor/du_processor_factory.h  (23 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../ue_manager/ue_manager_impl.h"
#include "du_processor.h"
#include "du_processor_config.h"
#include "ocudu/f1ap/f1ap_message_notifier.h"
#include "ocudu/support/async/async_task_scheduler.h"
#include <memory>


namespace ocudu::ocucp {

/// Creates an instance of an DU processor interface

/// Creates an instance of an DU processor interface
std::unique_ptr<du_processor> create_du_processor(du_processor_config_t        du_processor_config_,
                                                  du_processor_cu_cp_notifier& cu_cp_notifier_,
                                                  f1ap_message_notifier&       f1ap_pdu_notifier_,
                                                  async_task_scheduler&        common_task_sched_,
                                                  ue_manager&                  ue_mng_);


} // namespace ocudu::ocucp
