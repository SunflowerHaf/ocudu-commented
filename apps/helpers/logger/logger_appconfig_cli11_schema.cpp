// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// =============================================================================
// FILE: helpers/logger/logger_appconfig_cli11_schema.cpp
//
// Purpose (plain English):
//   Registers the root [log] YAML block with CLI11. Fields: filename, all_level,
//   lib_level, e2ap_level, config_level, hex_max_size.
//
//   Special behaviour: a post-parse callback propagates "all_level" to every
//   other *_level option that the user did NOT set explicitly. This lets the
//   user write just "all_level: debug" and have it apply everywhere, without
//   needing to enumerate every layer. Exceptions:
//     * lib_level is NOT auto-propagated (it affects only library internals).
//     * config_level is limited to none/info/debug (error/warning are rejected).
//   Options already explicitly set in the YAML are never overridden.
// =============================================================================
#include "logger_appconfig_cli11_schema.h"
#include "logger_appconfig.h"
#include "logger_appconfig_cli11_utils.h"
#include "ocudu/support/cli11_utils.h"

using namespace ocudu;


static void configure_cli11_log_args(CLI::App& app, logger_appconfig& log_params)
{
  // config_level accepts only none/info/debug (not warning/error).
  auto config_level_check = [](const std::string& value) -> std::string {
    if (auto level = ocudulog::str_to_basic_level(value); !level.has_value() ||
                                                          level.value() == ocudulog::basic_levels::error ||
                                                          level.value() == ocudulog::basic_levels::warning) {
      return "Log level value not supported. Accepted values [none,info,debug]";
    }

    return {};
  };


  app.add_option("--filename", log_params.filename, "Log file output path")->capture_default_str();

  app_helpers::add_log_option(
      app, log_params.all_level, "--all_level", "Default log level for PHY, MAC, RLC, PDCP, RRC, SDAP, NGAP and GTPU");
  app_helpers::add_log_option(app, log_params.lib_level, "--lib_level", "Generic log level ");
  app_helpers::add_log_option(app, log_params.e2ap_level, " --e2ap_level", "E2AP log level");

  add_option_function<std::string>(
      app, " --config_level", app_helpers::capture_log_level_function(log_params.config_level), "Config log level")
      ->default_str(ocudulog::basic_level_to_string(log_params.config_level))
      ->check(config_level_check);
  add_option(app,
             "--hex_max_size",
             log_params.hex_max_size,
             "Maximum number of bytes to print in hex (zero for no hex dumps, -1 for unlimited bytes)")
      ->capture_default_str()
      ->check(CLI::Range(-1, 1024));
  // Post-parsing callback. This allows us to set the log level to "all" level, if no level is provided.

  // Post-parse callback: propagate all_level to every *_level that the user
  // did not set explicitly. This is how "all_level: debug" in the YAML sets
  // every layer to debug in one line.
  app.callback([&]() {
    // Do nothing when all_level is not defined or it is defined as warning.
    if (app.count("--all_level") == 0 || log_params.all_level == ocudulog::basic_levels::warning) {
      return; // all_level not set, or it is the default — nothing to propagate.
    }

    const auto options = app.get_options();
    for (auto* option : options) {
      // Skip all_level option and unrelated options to log level.
      if (option->check_name("--all_level") || option->get_single_name().find("level") == std::string::npos) {
        continue; // Skip all_level itself and non-level options.
      }

      // Do nothing if option is present.
      if (option->count()) {
        continue; // User explicitly set this option — don't override it.
      }

      // Config logger have only subset of levels.
      if (option->check_name("--config_level")) {
        // config_level can't be error — map it to none in that case.
        if (log_params.all_level == ocudulog::basic_levels::error) {
          option->default_val<std::string>("none");
          continue;
        }
      }

      // Skip setting options that are not directly related to the stack.
      if (option->check_name("--lib_level")) {
        continue; // lib_level is intentionally not auto-propagated.
      }

      option->default_val<std::string>(ocudulog::basic_level_to_string(log_params.all_level));
    }
  });
}


void ocudu::configure_cli11_with_logger_appconfig_schema(CLI::App& app, logger_appconfig& config)
{
  // Logging section.
  CLI::App* log_subcmd = add_subcommand(app, "log", "Logging configuration")->configurable();
  configure_cli11_log_args(*log_subcmd, config);
}
