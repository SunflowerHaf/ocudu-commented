// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/metrics_config.h
//
// Purpose (plain English):
//   Defines the shared metrics_config struct used by every subsystem that
//   reports metrics. Three toggles:
//     enable_log_metrics  — write metric samples to the log file once per
//                           reporting period (default: 1 second).
//     enable_json_metrics — serialise metric samples as JSON and push them to
//                           the HTTP remote-server gateway for external tools.
//     enable_verbose      — include extra detail in the formatted output.
//   The enabled() helper is a convenience: it returns true if either output
//   channel is on. Metrics producers use it to decide whether to bother
//   computing samples at all.
// =============================================================================
#pragma once

#include <cstdint>
#include <string>


namespace ocudu {
namespace app_helpers {

/// Metrics configuration structure.

struct metrics_config {
  /// Enables the metrics in the log.
  bool enable_log_metrics = false; ///< Write metrics to the log channel.
  /// Enables the metrics in JSON format.
  bool enable_json_metrics = false; ///< Emit metrics as JSON over HTTP.
  /// Enable verbose metrics.
  bool enable_verbose = false; ///< Include additional detail in output.

  /// Returns true if the metrics are enabled, otherwise false.

  /// Returns true if any output channel is enabled.
  bool enabled() const { return enable_log_metrics || enable_json_metrics; }
};


} // namespace app_helpers
} // namespace ocudu
