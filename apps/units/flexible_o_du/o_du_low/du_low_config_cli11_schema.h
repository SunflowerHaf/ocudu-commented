// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_low_config_cli11_schema.h
//
// Purpose (plain English):
//   Declares the two entry points used by the top-level app-unit code to
//   plug the DU-Low config into the CLI11 command-line/YAML parser:
//
//     * configure_cli11_with_du_low_config_schema — registers every DU-Low
//       config field (name, type, default, description) with the CLI11
//       parser, so it knows how to interpret the [du_low] YAML block.
//
//     * autoderive_du_low_parameters_after_parsing — runs post-parse
//       derivations. Some DU-Low defaults depend on the cell's duplex mode
//       (FDD vs TDD) — for example the max processing delay differs — so
//       the duplex mode is passed in explicitly.
//
//   Both are declared in this header and implemented in the (large) CPP.
// =============================================================================

#pragma once


#include "ocudu/ran/duplex_mode.h"
#include "CLI/CLI11.hpp"


namespace ocudu {


struct du_low_unit_config;

/// Configures the given CLI11 application with the DU low configuration schema.

/// Registers every DU-Low config field with the CLI11 parser.
void configure_cli11_with_du_low_config_schema(CLI::App& app, du_low_unit_config& parsed_cfg);

/// Auto derive DU low parameters after the parsing.

/// Fills in DU-Low fields that depend on other parsed values.
/// \param mode  The cell's duplex mode (FDD or TDD) — some derivations differ.
void autoderive_du_low_parameters_after_parsing(CLI::App& app, du_low_unit_config& parsed_cfg, duplex_mode mode);


} // namespace ocudu
