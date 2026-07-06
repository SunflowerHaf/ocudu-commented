// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: ntn/du_high_ntn_config_yaml_writer.h
//
// Purpose (plain English):
//   Declares the entry point for serialising the per-cell NTN configuration
//   back to a YAML node (used by the "print effective config" feature).
// =============================================================================

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct du_high_unit_cell_ntn_config;

/// Fills the given node with the NTN configuration values.

/// Writes the NTN config fields into the given YAML node.
void fill_ntn_config_in_yaml_schema(YAML::Node& node, const du_high_unit_cell_ntn_config& config);


} // namespace ocudu
