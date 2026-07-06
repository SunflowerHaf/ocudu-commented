// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_low/o_du_low_metrics_collector.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace odu {


struct o_du_low_metrics;

/// O-RAN DU low metrics collector used for collecting metrics from the O-DU low.

/// O-RAN DU low metrics collector used for collecting metrics from the O-DU low.
class o_du_low_metrics_collector
{
public:
  virtual ~o_du_low_metrics_collector() = default;

  /// Collects the metrics from the O-DU low and writes them into the given metrics argument.

  /// Collects the metrics from the O-DU low and writes them into the given metrics argument.
  virtual void collect_metrics(o_du_low_metrics& metrics) = 0;
};


} // namespace odu
} // namespace ocudu
