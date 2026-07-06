// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// FILE: helpers/logger/logger_appconfig_cli11_schema.h
// Declares the CLI11 schema entry point for the root [log] YAML block.
#pragma once

#include "CLI/CLI11.hpp"

namespace ocudu {

struct logger_appconfig;

/// Configures the given CLI11 application with the logger application configuration schema.
void configure_cli11_with_logger_appconfig_schema(CLI::App& app, logger_appconfig& config);

} // namespace ocudu
