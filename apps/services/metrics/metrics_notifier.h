// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/metrics/metrics_notifier.h
//
// Purpose (plain English):
//   Abstract base class for the metrics fan-out bus. Producers call on_new_metric() when a new snapshot is ready; the bus dispatches it to all registered consumers via their callback.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace app_services {


class metrics_set;

/// Notifies new metrics.

/// Notifies new metrics.
class metrics_notifier
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~metrics_notifier() = default;

  /// Notifies the given metrics.

  /// Notifies the given metrics.
  virtual void on_new_metric(const metrics_set& metric) = 0;
};


} // namespace app_services
} // namespace ocudu
