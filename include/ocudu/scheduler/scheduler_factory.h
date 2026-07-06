// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/scheduler_factory.h  (15 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/scheduler/config/scheduler_config.h"
#include "ocudu/scheduler/mac_scheduler.h"


namespace ocudu {

/// Create L2 scheduler object.

/// Create L2 scheduler object.
std::unique_ptr<mac_scheduler> create_scheduler(const scheduler_config& sched_cfg);


} // namespace ocudu
