// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/metrics/metrics_producer.h
//
// Purpose (plain English):
//   Abstract base class for metrics producers. on_new_report_period() is called by the metrics manager once per reporting interval; producers should flush accumulated counters here.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace app_services {


class metrics_properties;

/// \brief Metrics producer.
///
/// Produces metrics that will be consumed by the corresponding metrics consumers.

/// \brief Metrics producer.
///
/// Produces metrics that will be consumed by the corresponding metrics consumers.
class metrics_producer
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~metrics_producer() = default;

  /// This method can be called periodically to process accumulated metrics and produce the metrics to be consumed by
  /// the corresponding metrics consumers.

  /// This method can be called periodically to process accumulated metrics and produce the metrics to be consumed by
  /// the corresponding metrics consumers.
  virtual void on_new_report_period() = 0;
};


} // namespace app_services
} // namespace ocudu
