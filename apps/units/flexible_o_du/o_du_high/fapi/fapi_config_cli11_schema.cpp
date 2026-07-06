// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: fapi/fapi_config_cli11_schema.cpp
//
// Purpose (plain English):
//   Registers the FAPI configuration with the CLI11 parser. Structured as:
//
//   [fapi]              ← parent sub-command (added by the caller)
//     [log]             ← log sub-command (added here)
//       --fapi_level    ← log level option (info/debug/warning/error)
//
//   The helper configure_cli11_log_args() is a small static function that
//   keeps the log registration logic grouped together, following the same
//   pattern used by every other unit in the codebase.
// =============================================================================

#include "fapi_config_cli11_schema.h"
#include "apps/helpers/logger/logger_appconfig_cli11_utils.h"
#include "fapi_config.h"
#include "ocudu/support/cli11_utils.h"


using namespace ocudu;


// Registers the --fapi_level option under the [log] sub-command.
static void configure_cli11_log_args(CLI::App& app, fapi_unit_config& log_params)
{
  app_helpers::add_log_option(app, log_params.fapi_level, "--fapi_level", "FAPI log level");
}


void ocudu::configure_cli11_with_fapi_config_schema(CLI::App& app, fapi_unit_config& parsed_cfg)
{
  // Loggers section.
  // Create the [log] sub-command under whatever FAPI parent section was passed in.
  CLI::App* log_subcmd = add_subcommand(app, "log", "Logging configuration")->configurable();
  configure_cli11_log_args(*log_subcmd, parsed_cfg);
}
