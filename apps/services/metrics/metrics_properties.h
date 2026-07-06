// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/metrics/metrics_properties.h
//
// Purpose (plain English):
//   Returns the human-readable name of a metric type (e.g. 'RLC metrics', 'DU metrics'). Used by the framework for logging and for routing metrics to the right consumer chain.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <string_view>


namespace ocudu {
namespace app_services {

/// Metrics properties.

/// Metrics properties.
class metrics_properties
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~metrics_properties() = default;

  /// Returns the metrics name.

  /// Returns the metrics name.
  virtual std::string_view name() const = 0;
};


} // namespace app_services
} // namespace ocudu
