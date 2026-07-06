// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/flexible_o_du_metrics_aggregator.h  (30 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "metrics/flexible_o_du_metrics_notifier.h"
#include "ocudu/du/o_du_metrics_notifier.h"


namespace ocudu {


class ru_metrics_collector;

/// Flexible O-DU metrics aggregator. It aggregates O-DU metrics and RU metrics.

/// Flexible O-DU metrics aggregator. It aggregates O-DU metrics and RU metrics.
class flexible_o_du_metrics_aggregator : public odu::o_du_metrics_notifier
{
  flexible_o_du_metrics_notifier& notifier;
  ru_metrics_collector*           ru_collector = nullptr;


public:
  explicit flexible_o_du_metrics_aggregator(flexible_o_du_metrics_notifier* notifier_);

  // See interface for documentation.

  // See interface for documentation.
  void on_new_metrics(const odu::o_du_metrics& odu_metrics) override;

  /// Sets the RU metrics collector to the given one.

  /// Sets the RU metrics collector to the given one.
  void set_ru_metrics_collector(ru_metrics_collector& collector) { ru_collector = &collector; }
};


} // namespace ocudu
