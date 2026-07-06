// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: ntn/du_high_ntn_config_cli11_schema.h
//
// Purpose (plain English):
//   Declares three entry points for registering NTN config fields with the
//   CLI11 parser at different levels of granularity:
//
//     configure_cli11_ntn_config_args — shared base NTN config (K-offset,
//       ephemeris type, validation duration etc.). Called for the common
//       [ntn] section that applies to all cells.
//
//     configure_cli11_advanced_ntn_args — advanced/enterprise fields that
//       most users don't need (feeder link, gateway location, polarization,
//       moving reference location, etc.).
//
//     configure_cli11_cell_ntn_args — per-cell NTN override block. Lets
//       each cell in a multi-cell config have its own NTN parameters.
// =============================================================================

#pragma once


#include "CLI/CLI11.hpp"
#include <optional>


namespace ocudu {


struct ntn_config;
struct du_high_unit_cell_ntn_config;

/// Configures shared NTN config CLI11 options.
/// \param app The CLI11 application or subcommand to configure.
/// \param config NTN config to populate.

/// Registers shared NTN config CLI11 options.
void configure_cli11_ntn_config_args(CLI::App& app, ntn_config& config);

/// Configures advanced/enterprise NTN CLI11 options.
/// \param app The CLI11 application or subcommand to configure.
/// \param config The NTN configuration structure to populate with advanced NTN parameters.

/// Registers advanced/enterprise NTN CLI11 options.
void configure_cli11_advanced_ntn_args(CLI::App& app, du_high_unit_cell_ntn_config& config);

/// Configures per-cell NTN CLI11 options. Allows overriding NTN parameters on a per-cell basis.
/// \param app The CLI11 application or subcommand to configure.
/// \param cell_ntn_params Optional NTN configuration for the cell; will be populated if NTN options are specified.

/// Registers per-cell NTN CLI11 option overrides.
void configure_cli11_cell_ntn_args(CLI::App& app, std::optional<du_high_unit_cell_ntn_config>& cell_ntn_params);


} // namespace ocudu
