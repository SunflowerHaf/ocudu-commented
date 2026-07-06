// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_cli11_schema.h
 * @brief Declarations for registering the gNB-level config fields with the CLI11/YAML parser.
 *
 * This file declares three functions used during startup (see gnb.cpp's main()):
 *
 *   configure_cli11_with_gnb_appconfig_schema(): registers every gnb_appconfig
 *   field (logging, tracing, buffer pool, threading, metrics, HAL, remote
 *   control) with the CLI11 parser so the YAML config file's top-level
 *   options get parsed directly into the gnb_appconfig struct.
 *
 *   autoderive_gnb_parameters_after_parsing(): runs once after parsing, to
 *   fill in any gNB-level values that depend on what else was parsed (e.g.
 *   disabling the HAL config if DPDK is compiled in but the user didn't
 *   provide a [hal] section).
 *
 *   autoderive_supported_tas_for_amf_from_du_cells(): a cross-cutting helper
 *   that derives the CU-CP's list of supported Tracking Areas from the DU's
 *   cell definitions, used by main() when the user hasn't explicitly
 *   configured supported_tas themselves.
 */

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct gnb_appconfig;
struct cu_cp_unit_config;
struct du_high_unit_config;

/// Configures the given CLI11 application with the gNB application configuration schema.

/**
 * @brief Registers every gnb_appconfig field with the CLI11/YAML parser.
 *
 * @param app             The CLI11 application object to register fields on.
 * @param gnb_parsed_cfg  The gnb_appconfig struct that will be populated when parsing runs.
 */
void configure_cli11_with_gnb_appconfig_schema(CLI::App& app, gnb_appconfig& gnb_parsed_cfg);

/// Auto derive gNB parameters after the parsing.

/**
 * @brief Auto-derives gNB-level parameters after parsing has completed.
 *
 * @param app     The CLI11 app object (provides access to which fields were explicitly set).
 * @param config  The config struct to update in place.
 */
void autoderive_gnb_parameters_after_parsing(CLI::App& app, gnb_appconfig& parsed_cfg);

/// Auto derive the supported TAs for the CU-CP AMF config from the DU cells config.

/**
 * @brief Derives the CU-CP's supported Tracking Area list from the DU's cell definitions.
 *
 * Called by main() when the CU-CP's AMF config has no explicit supported_tas
 * list (or is running in no_core mode being reconfigured) — fills in the
 * CU-CP's TAC/PLMN list to match exactly what the DU cells are using, so the
 * user doesn't have to specify this information in two places.
 *
 * @param du_hi_cfg  The DU High config containing cell PLMN/TAC definitions.
 * @param cu_cp_cfg  The CU-CP config to update with derived supported TAs.
 */
void autoderive_supported_tas_for_amf_from_du_cells(const du_high_unit_config& du_hi_cfg, cu_cp_unit_config& cu_cp_cfg);


} // namespace ocudu
