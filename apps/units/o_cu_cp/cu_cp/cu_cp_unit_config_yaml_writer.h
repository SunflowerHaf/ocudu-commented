// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_cp/cu_cp/cu_cp_unit_config_yaml_writer.h  (16 lines)
//
// Purpose (plain English):
//   Declares fill_cu_cp_config_in_yaml_schema() for the print-effective-config feature.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <yaml-cpp/yaml.h>


namespace ocudu {


struct cu_cp_unit_config;

/// Fills the given node with the CU-CP configuration values.

/// Fills the given node with the CU-CP configuration values.
void fill_cu_cp_config_in_yaml_schema(YAML::Node& node, const cu_cp_unit_config& config);


} // namespace ocudu
