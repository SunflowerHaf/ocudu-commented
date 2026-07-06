// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/logger/logger_appconfig_cli11_utils.h
//
// Purpose (plain English):
//   Utility functions used by *every* CLI11 log-level option in the codebase.
//   Rather than duplicating the "parse string → enum, validate, register"
//   boilerplate in each config section, every caller uses add_log_option().
//
//   capture_log_level_function — returns a lambda that converts a string
//     (e.g. "info") into the corresponding ocudulog::basic_levels enum value.
//     If the string is not recognised, the level is set to "none" (i.e.
//     silent). This is the callback registered with CLI11's option_function().
//
//   add_log_option — convenience wrapper that wires a CLI11 option directly
//     to a basic_levels variable, applying the capture lambda + a validator
//     that rejects unknown level strings with a helpful error message.
// =============================================================================
#pragma once

#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/cli11_utils.h"


namespace ocudu {
namespace app_helpers {

/// Function to capture the log level.

/// Returns a lambda that parses a log-level string into basic_levels.
inline auto capture_log_level_function = [](ocudulog::basic_levels& level) {
  return [&level](const std::string& value) {
    auto val = ocudulog::str_to_basic_level(value);
    level    = (val) ? val.value() : ocudulog::basic_levels::none;
  };
};

/// Helper function to add log options to CLI11.

/// Registers a log-level CLI11 option that writes into `level`.
/// Validates that the string is one of: none, info, debug, warning, error.
inline CLI::Option*
add_log_option(CLI::App& app, ocudulog::basic_levels& level, const std::string& name, const std::string& descriptrion)
{
  /// Function to check that the log level is correct.
  auto check_log_level = [](const std::string& value) -> std::string {
    if (ocudulog::str_to_basic_level(value).has_value()) {
      return {};
    }

    return fmt::format("Log level '{}' not supported. Accepted values [none,info,debug,warning,error]", value);
  };

  return add_option_function<std::string>(app, name, capture_log_level_function(level), descriptrion)

      ->default_str(ocudulog::basic_level_to_string(level))
      ->check(check_log_level);
}


} // namespace app_helpers
} // namespace ocudu
