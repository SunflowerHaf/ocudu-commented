// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/metrics/metrics_set.h
//
// Purpose (plain English):
//   Base class for a single metrics snapshot: wraps a data object and its properties. Passed to consumers via handle_metric(). Concrete subclasses add the actual data accessor.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace app_services {


class metrics_properties;

/// General purpouse metrics set.

/// General purpouse metrics set.
class metrics_set
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~metrics_set() = default;

  /// Returns this metrics properties.

  /// Returns this metrics properties.
  virtual const metrics_properties& get_properties() const = 0;
};


} // namespace app_services
} // namespace ocudu
