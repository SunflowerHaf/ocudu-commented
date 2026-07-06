// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/e2/e2_cli11_schema.cpp
//
// Purpose (plain English):
//   Registers all E2 connection parameters with the CLI11 parser under an
//   [e2] sub-command. The function is called once per unit type (DU, CU-CP,
//   CU-UP), each passing its own unit-specific enable flag name.
//
//   Fields registered:
//     {option_name}     — the per-unit enable toggle (e.g. "--enable_du_e2").
//     --addrs / --addr  — RIC IP address(es); multi-homing supported.
//     --port            — RIC SCTP port (must be in [20000, 40000] range).
//     --bind_addrs      — local SCTP bind address(es).
//     SCTP socket args  — delegated to configure_cli11_sctp_socket_args().
//     --e2sm_kpm_enabled / --e2sm_rc_enabled / --e2sm_ccc_enabled — E2SM module flags.
// =============================================================================

#include "e2_cli11_schema.h"
#include "apps/helpers/e2/e2_appconfig.h"
#include "apps/helpers/network/sctp_cli11_schema.h"
#include "ocudu/support/cli11_utils.h"


using namespace ocudu;


static void configure_cli11_e2_args(CLI::App&          app,
                                    e2_config&         e2_params,
                                    const std::string& option_name,
                                    const std::string& option_description)
{
  // Per-unit enable toggle (name varies: "--enable_du_e2", "--enable_cu_e2", etc.).
  add_option(app, option_name, e2_params.enable_unit_e2, option_description)->capture_default_str();

  // RIC IP address(es). "--addrs" is the current name; "--addr" kept for backward
  // compatibility with config files written against older versions.
  add_option(app,
             "--addrs,--addr", // TODO: old name kept for backward compatibility, should be removed in the future
             e2_params.ip_addrs,
             "RIC addresses to be used for E2 interface. Multiple addresses can be specified for SCTP multi-homing")
      ->capture_default_str();

  // RIC SCTP port (3GPP/O-RAN: 36421 is the default; user can override within this range).
  add_option(app, "--port", e2_params.port, "RIC port")->check(CLI::Range(20000, 40000))->capture_default_str();

  // Local bind address(es). Same backward-compat alias as for --addrs.
  add_option(
      app,
      "--bind_addrs,--bind_addr", // TODO: old name kept for backward compatibility, should be removed in the future
      e2_params.bind_addrs,
      "Local bind addresses to be used for E2 interface. Multiple addresses can be specified for SCTP "
      "multi-homing. If left empty, implicit bind is performed")
      ->capture_default_str();

  // Delegate the SCTP socket fine-tuning options to the shared helper.
  configure_cli11_sctp_socket_args(app, e2_params.sctp);

  // E2SM module flags — each causes the corresponding module to be announced
  // in the E2 Setup Request.
  add_option(app, "--e2sm_kpm_enabled", e2_params.e2sm_kpm_enabled, "Enable KPM service module")->capture_default_str();
  add_option(app, "--e2sm_rc_enabled", e2_params.e2sm_rc_enabled, "Enable RC service module")->capture_default_str();
  add_option(app, "--e2sm_ccc_enabled", e2_params.e2sm_ccc_enabled, "Enable CCC service module")->capture_default_str();
}


void ocudu::configure_cli11_with_e2_config_schema(CLI::App&          app,
                                                  e2_config&         config,
                                                  const std::string& option_name,
                                                  const std::string& option_description)
{
  // Create the [e2] sub-command and populate it.
  CLI::App* e2_subcmd = add_subcommand(app, "e2", "E2 parameters")->configurable();
  configure_cli11_e2_args(*e2_subcmd, config, option_name, option_description);
}
