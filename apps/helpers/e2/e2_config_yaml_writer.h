// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/e2/e2_config_yaml_writer.h
//   Declares fill_e2_config_in_yaml_schema() — the shared serialiser for the
//   E2 config block (RIC address, port, E2SM flags, SCTP params). Called by
//   each unit's own YAML writer after writing its unit-specific enable flag.
// =============================================================================
#pragma once

#include <yaml-cpp/yaml.h>

namespace ocudu {

struct e2_config;

/// Fills the E2 configuration in the given YAML node.
void fill_e2_config_in_yaml_schema(YAML::Node node, const e2_config& config);

} // namespace ocudu
