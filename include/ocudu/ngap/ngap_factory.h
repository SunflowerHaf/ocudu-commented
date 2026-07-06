// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ngap/ngap_factory.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/ngap
// NGAP interface headers: n2_connection_client (manages the SCTP connection to the AMF), ngap_message_handler interfaces for all NGAP procedures, and the NGAP-to-RRC message passing interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ngap/ngap.h"
#include "ocudu/ngap/ngap_configuration.h"
#include "ocudu/support/executors/task_executor.h"
#include <memory>


namespace ocudu {


namespace ocucp {


class n2_connection_client;

/// Creates an instance of an NGAP interface, notifying outgoing packets on the specified listener object.

/// Creates an instance of an NGAP interface, notifying outgoing packets on the specified listener object.
std::unique_ptr<ngap_interface> create_ngap(const ngap_configuration& ngap_cfg_,
                                            ngap_cu_cp_notifier&      cu_cp_notifier_,
                                            n2_connection_client&     n2_gateway_handler_,
                                            timer_manager&            timers_,
                                            task_executor&            ctrl_exec_);


} // namespace ocucp


} // namespace ocudu
