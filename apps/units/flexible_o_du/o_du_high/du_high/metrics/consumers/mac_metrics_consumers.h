// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/consumers/mac_metrics_consumers.h
//
// Purpose (plain English):
//   Logger consumer for MAC downlink timing metrics. Writes per-cell latency
//   breakdown (wall-clock, scheduler, DL/UL TTI-req, slot-ind dequeue) to
//   the log once per metrics period, plus slot duration and context-switch
//   counts. Useful for diagnosing real-time overruns.
// =============================================================================

#pragma once


#include "ocudu/mac/mac_metrics.h"
#include "ocudu/ocudulog/log_channel.h"


namespace ocudu {

/// Logger consumer for the MAC metrics.

/// Logs MAC DL cell metrics (timing latencies + context-switch counts).
class mac_metrics_consumer_log
{
public:
  explicit mac_metrics_consumer_log(ocudulog::log_channel& log_chan_) : log_chan(log_chan_) {}

  /// Handle the given DU high MAC metrics.

  /// Handle the MAC DL metric report for all cells.
  void handle_metric(const mac_dl_metric_report& report);


private:
  ocudulog::log_channel& log_chan;
};


} // namespace ocudu
