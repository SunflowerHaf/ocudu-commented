// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: metrics/du_metrics_producer.h
//
// Purpose (plain English):
//   The "source" end of the DU combined (scheduler+MAC) metrics pipeline.
//   The core DU High calls on_new_metric_report() when each reporting period
//   ends; this class wraps the data and pushes it into the framework.
// =============================================================================

#pragma once


#include "apps/services/metrics/metrics_notifier.h"
#include "apps/services/metrics/metrics_producer.h"
#include "ocudu/du/du_high/du_metrics_notifier.h"


namespace ocudu {

/// DU metrics producer implementation.

/// DU metrics producer: wraps odu::du_metrics_report and forwards to consumers.
class du_metrics_producer_impl : public odu::du_metrics_notifier, public app_services::metrics_producer
{
public:
  explicit du_metrics_producer_impl(app_services::metrics_notifier& notifier_) : notifier(notifier_) {}

  // See interface for documentation.

  /// Called by the core DU High each time a metrics period completes.
  void on_new_metric_report(const odu::du_metrics_report& metrics) override;

  // See interface for documentation.

  /// No-op: the DU High resets its counters on its own schedule.
  void on_new_report_period() override {}


private:
  app_services::metrics_notifier& notifier;
};


} // namespace ocudu
