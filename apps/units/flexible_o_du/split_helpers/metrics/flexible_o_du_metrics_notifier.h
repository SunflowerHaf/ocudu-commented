// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_helpers/metrics/flexible_o_du_metrics_notifier.h  (21 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_helpers
// Shared helpers used by all flexible O-DU split variants. Contains: the O-DU High factory (builds the running DU High from config + dependencies), the flexible_o_du_impl (the top-level O-DU adapter that ties together DU High, DU Low, and RU), the worker manager config fill functions, PCAP factories, metrics pipeline, and the shared YAML/CLI11 schema entry points.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct flexible_o_du_metrics;

/// Flexible O-DU metrics notifier.

/// Flexible O-DU metrics notifier.
class flexible_o_du_metrics_notifier
{
public:
  virtual ~flexible_o_du_metrics_notifier() = default;

  /// Notifies a new flexible O-DU metric.

  /// Notifies a new flexible O-DU metric.
  virtual void on_new_metrics(const flexible_o_du_metrics& metric) = 0;
};


} // namespace ocudu
