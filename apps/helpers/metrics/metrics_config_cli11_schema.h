// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// FILE: helpers/metrics/metrics_config_cli11_schema.h
// Registers the shared metrics output toggles (log, json, verbose) with CLI11.
#pragma once

#include "CLI/CLI11.hpp"

namespace ocudu {
namespace app_helpers {

struct metrics_config;

/// Configures the given CLI11 application with the metrics logger application configuration schema.
void configure_cli11_with_metrics_appconfig_schema(CLI::App& app, metrics_config& config);

} // namespace app_helpers
} // namespace ocudu
