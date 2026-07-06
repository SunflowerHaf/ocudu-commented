// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/du_metrics_consumers.cpp
//
// Purpose (plain English):
//   Implements the four DU metric consumer handle_metric() methods.
//
//   stdout: checks the atomic enable flag; if set, passes the scheduler
//     report to sched_consumer which prints a row per connected UE.
//
//   json: generates two JSON strings — one for the full DU report and one
//     specifically for the scheduler table — and sends both to the gateway.
//
//   log: routes the three sub-sections to their dedicated log consumers:
//     DU-procedure stats (UE create latency), MAC DL latencies, scheduler
//     per-UE table.
//
//   e2: passes the scheduler report to the E2 agent notifier.
// =============================================================================

#include "du_metrics_consumers.h"
#include "apps/helpers/metrics/json_generators/du_high/scheduler.h"
#include "apps/helpers/metrics/json_generators/generator_helpers.h"
#include "apps/helpers/metrics/json_generators/o_du_high.h"
#include "apps/services/remote_control/remote_server_metrics_gateway.h"
#include "du_metrics.h"


using namespace ocudu;


void du_metrics_consumer_stdout::handle_metric(const app_services::metrics_set& metric)
{
  const odu::du_metrics_report& report = static_cast<const du_metrics_impl&>(metric).get_report();


  // Only print if the user hasn't toggled stdout off.
  if (!print_metrics.load(std::memory_order_relaxed)) {
    return;
  }

  // Nothing to show if the MAC hasn't produced a report yet.
  if (!report.mac) {
    return;
  }

  sched_consumer.handle_metric(report.mac->sched);
}


void du_metrics_consumer_json::handle_metric(const app_services::metrics_set& metric)
{
  const odu::du_metrics_report& report = static_cast<const du_metrics_impl&>(metric).get_report();


  if (!report.mac) {
    return;
  }

  // Emit the top-level DU report, then a dedicated scheduler JSON document.
  gateway.send(app_helpers::json_generators::generate_string(report, DEFAULT_JSON_INDENT));
  if (report.mac) {
    gateway.send(app_helpers::json_generators::generate_string(report.mac->sched, DEFAULT_JSON_INDENT));
  }
}


void du_metrics_consumer_log::handle_metric(const app_services::metrics_set& metric)
{
  const odu::du_metrics_report& report = static_cast<const du_metrics_impl&>(metric).get_report();


  // DU procedure metrics (UE creation latency, count).
  proc_consumer.handle_metric(report.du_proc);

  if (report.mac) {
    // MAC DL latency breakdown.
    mac_consumer.handle_metric(report.mac->dl);
    // Per-UE scheduler table.
    sched_consumer.handle_metric(report.mac->sched);
  }
}


void du_metrics_consumer_e2::handle_metric(const app_services::metrics_set& metric)
{
  const odu::du_metrics_report& report = static_cast<const du_metrics_impl&>(metric).get_report();


  if (!report.mac) {
    return;
  }

  sched_consumer.handle_metric(report.mac->sched);
}
