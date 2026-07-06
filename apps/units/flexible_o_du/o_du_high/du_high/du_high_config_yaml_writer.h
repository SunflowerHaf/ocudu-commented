// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_high_config_yaml_writer.h
//
// Purpose (plain English):
//   Declares the entry point for serialising the DU High config (including
//   all per-cell settings, MAC, RLC, scheduler, PCAP, log, metrics) back to
//   a YAML document node. Used by the "print effective config" feature at
//   startup, so the user has a full record of every value in effect.
// =============================================================================

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct du_high_parsed_config;

/// Fills the given node with the DU high configuration values.

/// \brief Writes the full DU High config into the given YAML node.
void fill_du_high_config_in_yaml_schema(YAML::Node& node, const du_high_parsed_config& parsed_cfg);


} // namespace ocudu
