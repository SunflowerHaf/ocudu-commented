// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file gnb_appconfig_translators.h
 * @brief Declarations for functions that translate gNB app config into subsystem configs.
 *
 * "Translation" is the step after parsing and validation. The gnb_appconfig struct
 * holds values in a user-facing format (as they appear in the YAML file). Subsystems
 * like the worker_manager expect their own internal config structs. Translator
 * functions convert between the two representations.
 *
 * This keeps gnb_appconfig simple and user-focused while each subsystem defines
 * exactly the format it needs internally.
 */

#pragma once


namespace ocudu {


// Forward declarations to avoid including full headers in this interface file.
struct gnb_appconfig;
struct worker_manager_config;

/// Fills the gNB worker manager parameters of the given worker manager configuration.

/**
 * @brief Fills the gNB-level fields of a worker_manager_config from gnb_appconfig.
 *
 * The worker_manager_config controls how many CPU threads are created, which
 * CPU cores they are pinned to, and how large the task queues between them are.
 * This function copies the relevant values from the user-facing gnb_appconfig
 * into the internal worker_manager_config format.
 *
 * Note: each application unit (CU-CP, CU-UP, DU) also fills its own portion
 * of the worker_manager_config separately. This function only fills the
 * gNB-level (shared/main pool) portion.
 *
 * @param config    The worker_manager_config to be populated (modified in place).
 * @param unit_cfg  The source gnb_appconfig containing the user's thread settings.
 */
void fill_gnb_worker_manager_config(worker_manager_config& config, const gnb_appconfig& unit_cfg);


} // namespace ocudu
