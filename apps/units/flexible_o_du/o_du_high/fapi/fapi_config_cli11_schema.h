// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: fapi/fapi_config_cli11_schema.h
//
// Purpose (plain English):
//   Declares the single entry point for registering the FAPI config with the
//   CLI11 parser. Currently the only FAPI option is the log level, registered
//   under [fapi][log][--fapi_level].
// =============================================================================

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct fapi_unit_config;

/// Configures the given CLI11 application with the FAPI configuration schema.

/// Registers FAPI config options (currently just the log level) with CLI11.
void configure_cli11_with_fapi_config_schema(CLI::App& app, fapi_unit_config& parsed_cfg);


} // namespace ocudu
