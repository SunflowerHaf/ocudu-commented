// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/helpers/ru_sdr_config_cli11_schema.h  (19 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct ru_sdr_unit_config;

/// Configures the given CLI11 application with the SDR RU configuration schema.

/// Configures the given CLI11 application with the SDR RU configuration schema.
void configure_cli11_with_ru_sdr_config_schema(CLI::App& app, ru_sdr_unit_config& parsed_cfg);

/// Auto derive SDR Radio Unit parameters after the parsing.

/// Auto derive SDR Radio Unit parameters after the parsing.
void autoderive_ru_sdr_parameters_after_parsing(CLI::App& app, ru_sdr_unit_config& parsed_cfg, unsigned nof_cells);


} // namespace ocudu
