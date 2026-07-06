// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/consumers/scheduler_metrics_consumers.h
//
// Purpose (plain English):
//   Declares three consumers for the NR scheduler's per-UE metrics report.
//   The scheduler produces one sample per metrics period (default: 1 second)
//   containing per-UE DL/UL MCS, bitrate, HARQ success/failure, CQI, RI,
//   BSR, timing advance, and power headroom.
//
//     scheduler_cell_metrics_consumer_stdout — prints a formatted table to
//       the terminal. Reprints the header after every 10 UE rows so the
//       column labels stay visible during a long run. Thread-safe via the
//       print_header() method called from the cmdline command.
//
//     scheduler_cell_metrics_consumer_log — writes the same data to the log
//       file using the RLC log channel (shares the metrics log channel).
//
//     scheduler_cell_metrics_consumer_e2 — forwards each per-UE sample to
//       the E2 agent's scheduler_metrics_notifier so the RIC can observe UE
//       performance and send RRM-control messages.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/log_channel.h"
#include "ocudu/scheduler/scheduler_metrics.h"
#include <optional>


namespace ocudu {

/// STDOUT consumer for the scheduler cell metrics.

/// Prints per-UE scheduler stats to stdout. Reprints header every 10 rows.
class scheduler_cell_metrics_consumer_stdout
{
  /// Maximum number of metric lines in STDOUT without a header, ie, print header every
  /// MAX_NOF_STDOUT_METRIC_LINES_WITHOUT_HEADER lines.
  /// Reprint the column header if more than this many UE rows were printed.
  static constexpr unsigned MAX_NOF_STDOUT_METRIC_LINES_WITHOUT_HEADER = 10;


public:
  /// Handle scheduler metrics.
  void handle_metric(const std::optional<scheduler_metrics_report>& report);

  /// Prints the header in the next metric handle.
  void print_header() { nof_lines = MAX_NOF_STDOUT_METRIC_LINES_WITHOUT_HEADER; }


private:
  unsigned nof_lines = MAX_NOF_STDOUT_METRIC_LINES_WITHOUT_HEADER;
};

/// Logger consumer for the scheduler cell metrics.

/// Logs per-UE scheduler stats to the metrics log channel.
class scheduler_cell_metrics_consumer_log
{
public:
  explicit scheduler_cell_metrics_consumer_log(ocudulog::log_channel& log_chan_) : log_chan(log_chan_)
  {
    ocudu_assert(log_chan.enabled(), "Logger log channel is not enabled");
  }

  /// Handle scheduler metrics.
  void handle_metric(const std::optional<scheduler_metrics_report>& report);


private:
  ocudulog::log_channel& log_chan;
};

/// E2 consumer for the scheduler cell metrics.

/// Forwards per-UE scheduler data to the E2 RIC agent.
class scheduler_cell_metrics_consumer_e2
{
public:
  explicit scheduler_cell_metrics_consumer_e2(scheduler_metrics_notifier& notifier_) : notifier(notifier_) {}

  /// Handle scheduler metrics.
  void handle_metric(const std::optional<scheduler_metrics_report>& report);


private:
  scheduler_metrics_notifier& notifier;
};


} // namespace ocudu
