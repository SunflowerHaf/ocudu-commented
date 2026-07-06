// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// FILE: helpers/logger/logger_appconfig_validator.h
// Validates the top-level logger config (file path is writable, levels are valid).
#pragma once

namespace ocudu {

struct logger_appconfig;

/// Validates the given logger application configuration. Returns true on success, false otherwise.
bool validate_logger_appconfig(const logger_appconfig& config);

} // namespace ocudu
