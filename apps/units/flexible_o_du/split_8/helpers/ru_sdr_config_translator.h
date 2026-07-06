// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/helpers/ru_sdr_config_translator.h  (23 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "apps/units/flexible_o_du/split_helpers/flexible_o_du_configs.h"
#include "ocudu/ru/sdr/ru_sdr_configuration.h"


namespace ocudu {


struct ru_sdr_unit_config;
struct worker_manager_config;

/// Converts and returns the given RU SDR application unit configuration to a SDR RU configuration.

/// Converts and returns the given RU SDR application unit configuration to a SDR RU configuration.
ru_sdr_configuration generate_ru_sdr_config(const ru_sdr_unit_config&                        ru_cfg,
                                            span<const flexible_o_du_ru_config::cell_config> cells,
                                            unsigned max_processing_delay_slots);

/// Fills the SDR worker manager parameters of the given worker manager configuration.

/// Fills the SDR worker manager parameters of the given worker manager configuration.
void fill_sdr_worker_manager_config(worker_manager_config& config, const ru_sdr_unit_config& ru_cfg);


} // namespace ocudu
