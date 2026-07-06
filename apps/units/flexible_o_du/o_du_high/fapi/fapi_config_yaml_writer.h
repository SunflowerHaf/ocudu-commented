// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: fapi/fapi_config_yaml_writer.h
//
// Purpose (plain English):
//   Declares the entry point for serialising the FAPI config back to YAML
//   for the print-effective-config feature. Writes fapi_level under [fapi][log].
// =============================================================================

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct fapi_unit_config;

/// Fills the given node with the FAPI configuration values.

/// Writes the FAPI config (currently just the log level) into the given YAML node.
void fill_fapi_config_in_yaml_schema(YAML::Node& node, const fapi_unit_config& config);


} // namespace ocudu
