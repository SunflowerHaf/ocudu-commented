// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/du_metrics_consumers.h
//
// Purpose (plain English):
//   Declares four "sink" objects for the combined DU (scheduler+MAC) metrics:
//
//     du_metrics_consumer_stdout — prints the per-UE scheduler table to the
//       terminal. Can be enabled/disabled at runtime via console command.
//       Also exposes print_header() so the cmdline command can request a
//       fresh header when it re-enables the output.
//
//     du_metrics_consumer_json — serialises the combined report to JSON and
//       sends it to the HTTP metrics gateway.
//
//     du_metrics_consumer_log — writes MAC timing latencies and scheduler
//       stats as formatted log lines using sub-consumer objects defined in
//       the consumers/ sub-folder.
//
//     du_metrics_consumer_e2 — forwards the scheduler per-UE data to the
//       E2 agent for RIC-based RRM decisions.
// =============================================================================

#pragma once


#include "apps/services/metrics/metrics_consumer.h"
#include "consumers/du_procedure_metrics_consumers.h"
#include "consumers/mac_metrics_consumers.h"
#include "consumers/scheduler_metrics_consumers.h"
#include "ocudu/ocudulog/log_channel.h"


namespace ocudu {


namespace app_services {
class remote_server_metrics_gateway;
} // namespace app_services

/// Consumer for the STDOUT DU metrics.

/// Prints the per-UE scheduler table to stdout. Thread-safe enable/disable.
class du_metrics_consumer_stdout : public app_services::metrics_consumer
{
public:
  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;

  /// This can be called from another execution context to turn on the actual plotting.

  /// Turn on stdout printing from any thread.
  void enable() { print_metrics.store(true, std::memory_order_relaxed); }

  /// This can be called from another execution context to turn off the actual plotting.
  /// Turn off stdout printing from any thread.
  void disable() { print_metrics.store(false, std::memory_order_relaxed); }
  /// Prints the header in the next metric handle.
  /// Request that the column header is printed on the next metric tick.
  void print_header() { sched_consumer.print_header(); }


private:
  scheduler_cell_metrics_consumer_stdout sched_consumer;
  std::atomic<bool>                      print_metrics = {false};
};

/// Consumer for the json DU metrics.

/// Serialises DU metrics to JSON over HTTP.
class du_metrics_consumer_json : public app_services::metrics_consumer
{
public:
  explicit du_metrics_consumer_json(app_services::remote_server_metrics_gateway& gateway_) : gateway(gateway_) {}

  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;


private:
  app_services::remote_server_metrics_gateway& gateway;
};

/// Consumer for the logger DU metrics.

/// Writes MAC timing + scheduler + DU-procedure metrics to the log file.
class du_metrics_consumer_log : public app_services::metrics_consumer
{
public:
  explicit du_metrics_consumer_log(ocudulog::log_channel& log_chan) :
    mac_consumer(log_chan), sched_consumer(log_chan), proc_consumer(log_chan)
  {
  }

  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;


private:
  mac_metrics_consumer_log            mac_consumer; ///< MAC DL timing latencies.
  scheduler_cell_metrics_consumer_log sched_consumer; ///< Per-UE scheduler stats.
  du_procedure_metrics_consumer_log   proc_consumer; ///< UE creation latency.
};

/// Consumer for the E2 DU metrics.

/// Forwards scheduler per-UE data to the E2 RIC agent.
class du_metrics_consumer_e2 : public app_services::metrics_consumer
{
public:
  explicit du_metrics_consumer_e2(scheduler_metrics_notifier& notifier) : sched_consumer(notifier) {}

  // See interface for documentation.
  void handle_metric(const app_services::metrics_set& metric) override;


private:
  scheduler_cell_metrics_consumer_e2 sched_consumer;
};


} // namespace ocudu
