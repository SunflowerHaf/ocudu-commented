// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ru/sdr/ru_sdr_ntn_doppler_compensation_handler_factory.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/ru
// Radio Unit (RU) interface headers: upper_ru_dl_rg_handler (receives DL resource grids from the upper PHY for transmission), upper_ru_ul_rx_symbol_handler (delivers received IQ symbols to the upper PHY), the RU configuration interface, and the RU controller (start/stop). The split-8 RU implementation is in lib/ru/sdr; these headers define the contract.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ntn/ntn_doppler_compensation_handler.h"
#include <memory>


namespace ocudu {


class ru_controller;

/// \brief Create RU SDR NTN Doppler Compensation handler.
///
/// \param ru_ctrl RU controller interface.
/// \return NTN Doppler compensation handler.

/// \brief Create RU SDR NTN Doppler Compensation handler.
///
/// \param ru_ctrl RU controller interface.
/// \return NTN Doppler compensation handler.
std::unique_ptr<ocudu_ntn::ntn_doppler_compensation_handler>
create_ru_sdr_ntn_doppler_compensation_handler(ru_controller& ru_ctrl);


} // namespace ocudu
