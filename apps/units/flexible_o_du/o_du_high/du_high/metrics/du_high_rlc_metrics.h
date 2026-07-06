// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: metrics/du_high_rlc_metrics.h
//
// Purpose (plain English):
//   Defines the "wrapper" types that the metrics-framework pipeline uses
//   for RLC (Radio Link Control) metrics.
//
//   The metrics framework works with three abstractions:
//     * metrics_properties — gives each metric type a human-readable name.
//     * metrics_set        — wraps a snapshot of the actual data.
//     * callback           — a function that takes a completed snapshot,
//                           dispatches it to the executor that runs consumers.
//
//   This file provides the RLC-specific implementations of the first two,
//   plus the dispatch callback. The underlying data is rlc_metrics (defined
//   in the core RLC library) containing per-RB TX and RX counters.
// =============================================================================

#pragma once


#include "apps/services/metrics/metrics_consumer.h"
#include "apps/services/metrics/metrics_properties.h"
#include "apps/services/metrics/metrics_set.h"
#include "ocudu/adt/span.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/rlc/rlc_metrics.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {

/// RLC metrics properties implementation.

/// Provides the name "RLC metrics" to the framework's stats reporting.
class rlc_metrics_properties_impl : public app_services::metrics_properties
{
public:
  std::string_view name() const override { return "RLC metrics"; }
};


/// \brief A single snapshot of RLC metrics wrapped in the metrics_set interface.
///
/// Holds one rlc_metrics sample (covering one measurement period for one
/// Radio Bearer) and exposes it to consumers via get_metrics().
class rlc_metrics_impl : public app_services::metrics_set
{
  rlc_metrics_properties_impl properties;
  rlc_metrics                 metrics; ///< The actual per-RB counters.


public:
  explicit rlc_metrics_impl(const rlc_metrics& metrics_) : metrics(metrics_) {}

  // See interface for documentation.

  const app_services::metrics_properties& get_properties() const override { return properties; }

  const rlc_metrics& get_metrics() const { return metrics; }
};

/// Callback for the RLC metrics.

/// \brief Dispatch callback for RLC metrics.
///
/// When a new RLC snapshot is ready, the framework calls this lambda. It
/// defers the actual consumer calls onto the metrics executor, so consumers
/// (log writer, JSON serialiser, E2 notifier) run off the real-time path.
/// A stop_event_token is captured so the deferred task can be cancelled
/// cleanly during shutdown.
inline auto rlc_metrics_callback = [](const app_services::metrics_set&      report,
                                      span<app_services::metrics_consumer*> consumers,
                                      task_executor&                        executor,
                                      ocudulog::basic_logger&               logger,
                                      stop_event_token                      token) {
  const auto& metric = static_cast<const rlc_metrics_impl&>(report);


  if (!executor.defer([metric, consumers, stop_token = std::move(token)]() {
        for (auto& consumer : consumers) {
          consumer->handle_metric(metric);
        }
      })) {
    logger.error("Failed to dispatch the metric '{}'", metric.get_properties().name());
  }
};


} // namespace ocudu
