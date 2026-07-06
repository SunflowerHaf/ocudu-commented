// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/flexible_o_du/split_8/helpers/ru_sdr_factories.h  (20 lines)
//
// DIRECTORY: apps/units/flexible_o_du/split_8
// Split-8 application unit wiring. Builds the flexible O-DU in split-8 mode: directly connects the O-DU High (MAC/scheduler) to the O-DU Low (upper PHY) which in turn drives the UHD/USRP radio. No Ethernet fronthaul — the DU High, DU Low, and Radio Unit run in the same process. Contains the split-8 factory, YAML config schema, CLI11 schema, validator, and the O-DU unit config struct.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ru_sdr_config.h"
#include "ocudu/ru/ru.h"
#include <memory>


namespace ocudu {
struct flexible_o_du_ru_dependencies;
struct flexible_o_du_ru_config;

/// Creates and returns a SDR RU with the given configuration and dependencies.

/// Creates and returns a SDR RU with the given configuration and dependencies.
std::unique_ptr<radio_unit> create_sdr_radio_unit(const ru_sdr_unit_config&            ru_sdr_cfg,
                                                  const flexible_o_du_ru_config&       du_ru_config,
                                                  const flexible_o_du_ru_dependencies& ru_dependencies);


} // namespace ocudu
