// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: du_high_config_cli11_schema.h
//
// Purpose (plain English):
//   Declares the two public entry points that hook the DU High configuration
//   into the CLI11 command-line / YAML parser:
//
//     configure_cli11_with_du_high_config_schema — registers every DU High
//       field (cells, MAC, RLC, scheduler, PDCP, PCAP, logging, metrics, etc.)
//       with the CLI11 App object so the parser knows how to read the YAML.
//
//     autoderive_du_high_parameters_after_parsing — fills in fields whose
//       values depend on other parsed values (e.g. SSB positions derived from
//       ARFCNs, PDSCH/PUSCH configs derived from bandwidth, default TDD
//       patterns filled in from the band).
// =============================================================================

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct du_high_parsed_config;
struct du_high_unit_config;

/// Configures the given CLI11 application with the DU high configuration schema.

/// \brief Registers the full DU High configuration schema with the CLI11 parser.
/// \param app        The CLI11 application/subcommand for the DU High block.
/// \param parsed_cfg The struct that will receive all parsed values.
void configure_cli11_with_du_high_config_schema(CLI::App& app, du_high_parsed_config& parsed_cfg);

/// Auto derive DU high parameters after the parsing.

/// \brief Fills in DU High parameters that are derived from other parsed values.
/// \param app      The same CLI11 application (used to check which options were set).
/// \param unit_cfg The fully-parsed unit config to post-process.
void autoderive_du_high_parameters_after_parsing(CLI::App& app, du_high_unit_config& unit_cfg);


} // namespace ocudu
