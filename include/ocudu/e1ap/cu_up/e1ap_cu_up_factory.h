// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/cu_up/e1ap_cu_up_factory.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e1ap/cu_up/e1ap_configuration.h"
#include "ocudu/e1ap/cu_up/e1ap_cu_up.h"
#include "ocudu/e1ap/gateways/e1_connection_client.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/timers.h"
#include <memory>


namespace ocudu {
namespace ocuup {

/// Creates an instance of an E1AP interface, notifying outgoing packets on the specified listener object.

/// Creates an instance of an E1AP interface, notifying outgoing packets on the specified listener object.
std::unique_ptr<e1ap_interface> create_e1ap(cu_up_e1_index_t             e1_index,
                                            const e1ap_configuration&    e1ap_cfg_,
                                            e1_connection_client&        e1_client_handler_,
                                            e1ap_cu_up_manager_notifier& cu_up_notifier_,
                                            timer_manager&               timers_,
                                            task_executor&               cu_up_exec_);


} // namespace ocuup
} // namespace ocudu
