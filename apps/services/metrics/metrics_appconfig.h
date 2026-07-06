// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/metrics/metrics_appconfig.h
//
// Purpose (plain English):
//   Top-level metrics service config: just the reporting period in ms (default 1000 = 1 second). Used by the metrics manager to schedule the periodic producer flush timer.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace app_services {

/// Metrics service application configuration.

/// Metrics service application configuration.
struct metrics_appconfig {
  /// Application usage report period in milliseconds.
  /// Application usage report period in milliseconds.
  unsigned app_usage_report_period = 1000;
};


} // namespace app_services
} // namespace ocudu
