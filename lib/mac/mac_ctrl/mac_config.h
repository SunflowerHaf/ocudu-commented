// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/mac/mac_ctrl/mac_config.h  (33 lines)
//
// LIBRARY: lib/mac
// Medium Access Control (MAC, TS 38.321): scheduler interface adaptor, HARQ process management, multiplexing/demultiplexing of logical channels into transport blocks, random-access (RACH) handling, and timing-advance control. Interfaces: MAC SDU to/from RLC, MAC PDU to/from the lower PHY via FAPI.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/mac.h"
#include "ocudu/ocudulog/ocudulog.h"


namespace ocudu {


class task_executor;
class mac_metrics_notifier;
class timer_manager;
class mac_clock_controller;

/// Config for MAC controller.

/// Config for MAC controller.
struct mac_control_config {
  struct metrics_config {
    std::chrono::milliseconds period{1000};
    mac_metrics_notifier&     mac_notifier;
    unsigned                  max_nof_ue_events;
    bool                      sched_ue_enabled = true;
  };


  mac_ul_ccch_notifier&   event_notifier;
  task_executor&          ctrl_exec;
  mac_clock_controller&   time_source;
  metrics_config          metrics;
  ocudulog::basic_logger& logger = ocudulog::fetch_basic_logger("MAC", true);
};


} // namespace ocudu
