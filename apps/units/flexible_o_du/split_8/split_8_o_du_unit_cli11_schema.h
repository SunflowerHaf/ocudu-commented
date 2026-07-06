// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/split_8_o_du_unit_cli11_schema.h  (19 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct split_8_o_du_unit_config;

/// Configures the given CLI11 application with the split 8 O-RAN DU unit configuration schema.

/// Configures the given CLI11 application with the split 8 O-RAN DU unit configuration schema.
void configure_cli11_with_split_8_o_du_unit_config_schema(CLI::App& app, split_8_o_du_unit_config& parsed_cfg);

/// Auto derive split 8 O-RAN DU parameters after the parsing.

/// Auto derive split 8 O-RAN DU parameters after the parsing.
void autoderive_split_8_o_du_parameters_after_parsing(CLI::App& app, split_8_o_du_unit_config& parsed_cfg);


} // namespace ocudu
