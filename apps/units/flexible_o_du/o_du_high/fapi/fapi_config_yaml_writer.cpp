// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: fapi/fapi_config_yaml_writer.cpp
//
// Purpose (plain English):
//   Serialises the FAPI config to YAML. Currently just one field:
//   fapi_level, written under node["log"]["fapi_level"].
//
//   Note: the internal static function is named fill_du_low_log_section (a
//   naming artefact from when the FAPI config lived inside du_low) — its job
//   is simply to write the log level string.
// =============================================================================

#include "fapi_config_yaml_writer.h"
#include "fapi_config.h"


using namespace ocudu;


// Writes the fapi_level string into the [log] YAML node.
static void fill_du_low_log_section(YAML::Node node, ocudulog::basic_levels level)
{
  // basic_level_to_string converts the enum to a human-readable string
  // ("debug", "info", "warning", "error") that the YAML parser can round-trip.
  node["fapi_level"] = ocudulog::basic_level_to_string(level);
}


void ocudu::fill_fapi_config_in_yaml_schema(YAML::Node& node, const fapi_unit_config& config)
{
  fill_du_low_log_section(node["log"], config.fapi_level);
}
