// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_cp/e2/o_cu_cp_e2_config_cli11_schema.h  (20 lines)
//
// Purpose (plain English):
//   CLI11 schema entry points for the CU-CP E2 config (E2AP PCAP + base E2 connection settings).
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include "CLI/CLI11.hpp"


namespace ocudu {


struct o_cu_cp_e2_config;

/// Configures the given CLI11 application with the O-RAN CU-CP E2 configuration schema.

/// Configures the given CLI11 application with the O-RAN CU-CP E2 configuration schema.
void configure_cli11_with_o_cu_cp_e2_config_schema(CLI::App& app, o_cu_cp_e2_config& unit_cfg);

/// Auto derive O-RAN CU-CP E2 parameters after the parsing.

/// Auto derive O-RAN CU-CP E2 parameters after the parsing.
void autoderive_o_cu_cp_e2_parameters_after_parsing(o_cu_cp_e2_config& unit_cfg);


} // namespace ocudu
