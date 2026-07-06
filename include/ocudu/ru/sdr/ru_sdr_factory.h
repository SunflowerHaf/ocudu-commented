// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/sdr/ru_sdr_factory.h  (18 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ru/ru.h"
#include <memory>


namespace ocudu {


struct ru_sdr_configuration;
struct ru_sdr_dependencies;

/// Returns an SDR Radio Unit using the given configuration.

/// Returns an SDR Radio Unit using the given configuration.
std::unique_ptr<radio_unit> create_sdr_ru(const ru_sdr_configuration& config, const ru_sdr_dependencies& dependencies);


} // namespace ocudu
