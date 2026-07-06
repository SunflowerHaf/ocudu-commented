// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: o_du_high_unit_config_yaml_writer.h
//
// Purpose (plain English):
//   Serialises the parsed O-DU High config back out to a YAML document.
//   Used by the "print-effective-config" feature: when the gNB starts up,
//   it can dump the fully-populated config (including all defaulted and
//   derived values) to disk, so the user has a record of exactly what was
//   used for the run — useful for debugging, reproducibility, and academic
//   write-ups.
// =============================================================================

#pragma once


#include "du_high/du_high_config_yaml_writer.h"
#include "e2/o_du_high_e2_config_yaml_writer.h"
#include "fapi/fapi_config_yaml_writer.h"
#include "o_du_high_unit_config.h"
#include <yaml-cpp/yaml.h>


namespace ocudu {

/// Fills the given node with the O-DU high configuration values.

/// \brief Writes the DU High, FAPI, and E2 config sections into the given
///        YAML node.
/// \param node   The parent YAML node — sub-keys will be added under it.
/// \param config The config to serialise.
inline void fill_o_du_high_config_in_yaml_schema(YAML::Node& node, const o_du_high_unit_config& config)
{
  fill_du_high_config_in_yaml_schema(node, config.du_high_cfg);
  fill_fapi_config_in_yaml_schema(node, config.fapi_cfg);
  fill_o_du_high_e2_config_in_yaml_schema(node, config.e2_cfg);
}


} // namespace ocudu
