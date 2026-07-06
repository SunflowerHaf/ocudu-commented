// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config_cli11_schema.cpp
//
// Purpose (plain English):
//   Implements the two CLI11 entry points for the DU High E2 config.
//
//   configure_cli11_pcap_args() registers the [pcap] sub-section options:
//     e2ap_du_filename — file path for the E2AP PCAP capture.
//     e2ap_enable      — boolean toggle for the E2AP capture.
//
//   configure_cli11_with_o_du_high_e2_config_schema():
//     1. Adds the [pcap] sub-command with the two options above.
//     2. Delegates the [e2] sub-section (enable toggle, near-RT RIC address,
//        port, E2SM module flags) to the shared configure_cli11_with_e2_config_schema()
//        helper, which is reused by every unit that has an E2 agent.
//
//   autoderive_o_du_high_e2_parameters_after_parsing():
//     Forces pcaps.enabled = false when the E2 agent is disabled, so the
//     user cannot accidentally create an empty PCAP file.
// =============================================================================

#include "o_du_high_e2_config_cli11_schema.h"
#include "apps/helpers/e2/e2_cli11_schema.h"
#include "o_du_high_e2_config.h"
#include "ocudu/support/cli11_utils.h"


using namespace ocudu;


// Registers the two E2AP PCAP options under the [pcap] sub-command.
static void configure_cli11_pcap_args(CLI::App& app, o_du_high_e2_pcap_config& pcap_params)
{
  add_option(app, "--e2ap_du_filename", pcap_params.filename, "E2AP PCAP file output path")->capture_default_str();
  add_option(app, "--e2ap_enable", pcap_params.enabled, "Enable E2AP packet capture")->always_capture_default();
}


void ocudu::configure_cli11_with_o_du_high_e2_config_schema(CLI::App& app, o_du_high_e2_config& config)
{
  // PCAP section.
  // Register the [pcap] sub-section.
  CLI::App* pcap_subcmd = add_subcommand(app, "pcap", "PCAP configuration")->configurable();
  configure_cli11_pcap_args(*pcap_subcmd, config.pcaps);

  // E2 section.

  // Delegate the shared E2 base config (RIC address, port, E2SM modules).
  // "--enable_du_e2" is the per-unit toggle flag; each unit type has its own
  // name so users can enable E2 on the DU but not the CU, or vice versa.
  configure_cli11_with_e2_config_schema(app, config.base_cfg, "--enable_du_e2", "Enable DU E2 agent");
}


void ocudu::autoderive_o_du_high_e2_parameters_after_parsing(o_du_high_e2_config& unit_cfg)
{
  // If O-DU E2 agent is disabled do not enable E2AP PCAP for it.
  // If the E2 agent is disabled, disable its PCAP too. A PCAP file with no
  // packets is confusing and wastes disk space.
  unit_cfg.pcaps.enabled = unit_cfg.base_cfg.enable_unit_e2 && unit_cfg.pcaps.enabled;
}
