// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/metrics/metrics_consumer.h
//
// Purpose (plain English):
//   Abstract base class for every metrics consumer (log writer, JSON serialiser, E2 notifier). Each consumer implements handle_metric() to receive one snapshot per reporting period.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace app_services {


class metrics_set;
class metrics_properties;

/// \brief Metrics subscriber.
///
/// A subscriber will listen to a configured metric.

/// \brief Metrics subscriber.
///
/// A subscriber will listen to a configured metric.
class metrics_consumer
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~metrics_consumer() = default;

  /// Handles the given metrics.

  /// Handles the given metrics.
  virtual void handle_metric(const metrics_set& metric) = 0;
};


} // namespace app_services
} // namespace ocudu
