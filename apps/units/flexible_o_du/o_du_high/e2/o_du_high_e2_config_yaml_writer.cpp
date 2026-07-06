// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config_yaml_writer.cpp
//
// Purpose (plain English):
//   Serialises the DU High E2 config back to YAML for the "print effective
//   config" feature. Two sections are written:
//
//   [e2] — The enable flag (enable_du_e2) is written first, then the shared
//     E2 base config (RIC address, port, E2SM flags) is handled by the shared
//     fill_e2_config_in_yaml_schema() helper used by all unit types.
//
//   [pcap] — The E2AP PCAP filename and enable toggle.
// =============================================================================

#include "o_du_high_e2_config_yaml_writer.h"
#include "apps/helpers/e2/e2_config_yaml_writer.h"
#include "o_du_high_e2_config.h"


using namespace ocudu;


// Fills the [pcap] sub-node with E2AP PCAP settings.
static void fill_o_du_high_e2_pcap_section(YAML::Node node, const o_du_high_e2_pcap_config& config)
{
  node["e2ap_du_filename"] = config.filename;
  node["e2ap_enable"]      = config.enabled;
}


void ocudu::fill_o_du_high_e2_config_in_yaml_schema(YAML::Node& node, const o_du_high_e2_config& config)
{
  // Write the DU-specific E2 enable flag into the [e2] sub-node.
  YAML::Node e2_node      = node["e2"];
  e2_node["enable_du_e2"] = config.base_cfg.enable_unit_e2;

  // Delegate the shared E2 base config fields (RIC IP, port, E2SM flags)
  // to the shared YAML writer used by all units.
  fill_e2_config_in_yaml_schema(e2_node, config.base_cfg);

  // PCAPs.

  // Write the PCAP settings.
  fill_o_du_high_e2_pcap_section(node["pcap"], config.pcaps);
}
