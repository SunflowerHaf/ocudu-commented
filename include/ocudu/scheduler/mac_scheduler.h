// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/scheduler/mac_scheduler.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/scheduler
// Scheduler interface headers: the scheduler itself (takes slot_indication, returns DL/UL grants), the scheduler-to-MAC and MAC-to-scheduler interfaces (grant notifications, CRC/UCI/BSR/SR/HARQ ACK reporting back from MAC), the scheduler configuration type, and the scheduler_metrics_notifier/scheduler_metrics_report types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/scheduler/scheduler_configurator.h"
#include "ocudu/scheduler/scheduler_dl_buffer_state_indication_handler.h"
#include "ocudu/scheduler/scheduler_feedback_handler.h"
#include "ocudu/scheduler/scheduler_paging_handler.h"
#include "ocudu/scheduler/scheduler_positioning_handler.h"
#include "ocudu/scheduler/scheduler_rach_handler.h"
#include "ocudu/scheduler/scheduler_slot_handler.h"
#include "ocudu/scheduler/scheduler_sys_info_handler.h"


namespace ocudu {


class mac_scheduler : public scheduler_configurator,
                      public scheduler_ue_configurator,
                      public scheduler_rach_handler,
                      public scheduler_feedback_handler,
                      public scheduler_slot_handler,
                      public scheduler_dl_buffer_state_indication_handler,
                      public scheduler_paging_handler,
                      public scheduler_sys_info_handler,
                      public scheduler_positioning_handler
{
public:
  virtual ~mac_scheduler() = default;
};


} // namespace ocudu
