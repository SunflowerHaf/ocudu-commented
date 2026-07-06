// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/flexible_o_du_metrics_aggregator.cpp  (48 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "flexible_o_du_metrics_aggregator.h"
#include "metrics/flexible_o_du_metrics.h"
#include "ocudu/ru/ru_metrics_collector.h"


using namespace ocudu;


namespace {

/// Fexible O-DU metrics notifier dummy implementation.

/// Fexible O-DU metrics notifier dummy implementation.
class flexible_o_du_metrics_notifier_dummy : public flexible_o_du_metrics_notifier
{
public:
  // See interface for documentation.
  // See interface for documentation.
  void on_new_metrics(const flexible_o_du_metrics& metric) override {}
};

/// Radio Unit metrics collector dummy implementation.

/// Radio Unit metrics collector dummy implementation.
class ru_metrics_collector_dummy : public ru_metrics_collector
{
public:
  // See interface for documentation.
  // See interface for documentation.
  void collect_metrics(ru_metrics& metrics) override {}
};


} // namespace

/// Dummy notifier and collector.

/// Dummy notifier and collector.
static flexible_o_du_metrics_notifier_dummy dummy_notifier;
static ru_metrics_collector_dummy           dummy_collector;


flexible_o_du_metrics_aggregator::flexible_o_du_metrics_aggregator(flexible_o_du_metrics_notifier* notifier_) :
  notifier(notifier_ ? *notifier_ : dummy_notifier), ru_collector(&dummy_collector)
{
}


void flexible_o_du_metrics_aggregator::on_new_metrics(const odu::o_du_metrics& odu_metrics)
{
  flexible_o_du_metrics metrics;

  // Caution, the copy may become expensive when the DU metrics grow.

  // Caution, the copy may become expensive when the DU metrics grow.
  metrics.du = odu_metrics;
  ru_collector->collect_metrics(metrics.ru);
  notifier.on_new_metrics(metrics);
}
