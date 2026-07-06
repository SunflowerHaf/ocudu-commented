// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config_yaml_writer.h
//
// Purpose (plain English):
//   Declares the entry point for serialising the DU High E2 configuration
//   (connection settings, E2SM module flags, and PCAP toggle) back to a
//   YAML document node. Used by the "print effective config" feature at startup.
// =============================================================================

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct o_du_high_e2_config;

/// Fills the given node with the O-RAN DU high E2 configuration values.

/// Writes the DU High E2 config into the given YAML node (under [e2] and [pcap]).
void fill_o_du_high_e2_config_in_yaml_schema(YAML::Node& node, const o_du_high_e2_config& config);


} // namespace ocudu
