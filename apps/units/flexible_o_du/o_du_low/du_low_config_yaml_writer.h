// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_config_yaml_writer.h
//
// Purpose (plain English):
//   Declares the single entry point for serialising the DU-Low config back
//   to a YAML node. Used by the "print effective config" feature at startup.
// =============================================================================

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct du_low_unit_config;

/// Fills the given node with the DU low configuration values.

/// \brief Writes every DU-Low config field into the given YAML node.
///
/// Sub-sections created: log, trace, expert_execution, expert_phy, and
/// (only when configured) hal. Metrics fields are added at the root level
/// via the shared metrics helper.
void fill_du_low_config_in_yaml_schema(YAML::Node& node, const du_low_unit_config& config);


} // namespace ocudu
