// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/metrics/metrics_helpers.h
//
// Purpose (plain English):
//   Declares three shared metric-infrastructure helpers:
//
//   fetch_logger_metrics_log_channel() — returns the named log channel used
//     by all "log metrics" consumers. A single shared channel avoids having
//     dozens of consumers create their own loggers.
//
//   fetch_json_metrics_log_channel() — same idea for JSON debug logging.
//
//   initialize_metrics_log_channels() — called once at startup to create
//     the two channels, set their levels based on the metrics config
//     (info if enabled, none if not), and set the hex-dump size limit.
// =============================================================================
#pragma once

namespace ocudulog {
class log_channel;
}

namespace ocudu {
namespace app_helpers {

struct metrics_config;

/// Returns the metrics log channel for the logger type.
ocudulog::log_channel& fetch_logger_metrics_log_channel();

/// Returns the metrics log channel for the JSON type.
ocudulog::log_channel& fetch_json_metrics_log_channel();

/// Initializes the metrics log channels using the given configuration.
void initialize_metrics_log_channels(const metrics_config& config, unsigned hex_dump_size);

} // namespace app_helpers
} // namespace ocudu
