// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_up/cu_up/cu_up_unit_config_cli11_schema.h  (16 lines)
//
// Purpose (plain English):
//   Declares CLI11 schema entry points for the CU-UP YAML block.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct cu_up_unit_config;

/// Configures the given CLI11 application with the CU-UP application unit configuration schema.

/// Configures the given CLI11 application with the CU-UP application unit configuration schema.
void configure_cli11_with_cu_up_unit_config_schema(CLI::App& app, cu_up_unit_config& unit_cfg);


} // namespace ocudu
