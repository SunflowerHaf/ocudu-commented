// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_validators.h
 * @brief Declarations for functions that validate the gNB application configuration.
 *
 * After the YAML config file has been parsed into a gnb_appconfig struct, these
 * functions are called to check that the values make sense before the system
 * starts. If any check fails, the application prints an error and exits rather
 * than starting with a broken configuration.
 *
 * Validation is separate from parsing so that each concern (reading, checking,
 * translating) is handled in its own file.
 */

#pragma once


#include "gnb_appconfig.h"


namespace ocudu {


// Forward declarations — avoids needing to include the full headers here,
// keeping compile times short.
struct cu_cp_unit_config;
struct du_high_unit_config;

/// Validates the given GNB application configuration. Returns true on success, false otherwise.

/**
 * @brief Validates the top-level gNB application configuration.
 *
 * Checks the logging config, expert execution (thread) config, and HAL
 * (hardware abstraction) config for obvious errors such as invalid values
 * or missing required fields.
 *
 * @param config  The fully parsed gNB configuration to validate.
 * @return true if all checks pass; false if any error is found (error message
 *         is printed to stdout before returning false).
 */
bool validate_appconfig(const gnb_appconfig& config);

/// Validates that the DU PLMNs and TACs are present in the CU-CP config.

/**
 * @brief Validates that every DU cell's PLMN and TAC appear in the CU-CP's supported tracking areas.
 *
 * A PLMN (Public Land Mobile Network) identifies the mobile operator (e.g. a specific
 * country/carrier combination). A TAC (Tracking Area Code) is a geographic grouping
 * of cells. The CU-CP must be configured to serve all PLMNs and TACs that the DU cells
 * advertise — this function verifies that is the case.
 *
 * This check is skipped if no_core mode is active (i.e. running without a real AMF).
 *
 * @param du_hi_cfg  The DU High configuration containing cell definitions.
 * @param cu_cp_cfg  The CU-CP configuration containing the list of supported tracking areas.
 * @return true if every DU cell's PLMN+TAC combination is found in the CU-CP config;
 *         false otherwise (with a descriptive error printed to stdout).
 */
bool validate_plmn_and_tacs(const du_high_unit_config& du_hi_cfg, const cu_cp_unit_config& cu_cp_cfg);


} // namespace ocudu
