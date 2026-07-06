// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: metrics/du_high_rlc_metrics_producer.h
//
// Purpose (plain English):
//   The "source" end of the RLC metrics pipeline.
//
//   The core RLC library calls report_metrics() whenever a measurement period
//   ends (typically every second). This class wraps that raw data into an
//   rlc_metrics_impl snapshot and hands it to the metrics_notifier, which
//   fans it out to any registered consumers (log, JSON, E2).
//
//   Dual-inherits:
//     * rlc_metrics_notifier — so the RLC layer can call report_metrics().
//     * app_services::metrics_producer — so the framework knows this object
//       is a producer and can manage its lifecycle.
// =============================================================================

#pragma once


#include "apps/services/metrics/metrics_notifier.h"
#include "apps/services/metrics/metrics_producer.h"
#include "ocudu/rlc/rlc_metrics.h"


namespace ocudu {

/// RLC metrics producer implementation.

/// RLC metrics producer: receives raw RLC stats, wraps, forwards to consumers.
class rlc_metrics_producer_impl : public rlc_metrics_notifier, public app_services::metrics_producer
{
public:
  explicit rlc_metrics_producer_impl(app_services::metrics_notifier& notifier_) : notifier(notifier_) {}

  // See interface for documentation.

  /// Called by the RLC core when a measurement period ends.
  void report_metrics(const rlc_metrics& metrics) override;

  // See interface for documentation.

  /// Called by the framework to start a new reporting period. No-op here
  /// because RLC resets its own counters independently.
  void on_new_report_period() override {}


private:
  app_services::metrics_notifier& notifier; ///< Fan-out to all registered consumers.
};


} // namespace ocudu
