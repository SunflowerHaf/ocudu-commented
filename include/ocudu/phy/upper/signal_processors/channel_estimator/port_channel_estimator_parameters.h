// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/channel_estimator/port_channel_estimator_parameters.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

/// Port channel estimator frequency domain smoothing strategy.

/// Port channel estimator frequency domain smoothing strategy.
enum class port_channel_estimator_fd_smoothing_strategy {
  /// No smoothing strategy.
  /// No smoothing strategy.
  none = 0,
  /// Averages all frequency domain estimates.
  /// Averages all frequency domain estimates.
  mean,
  /// Filters in the frequency domain with a low pass filter.
  /// Filters in the frequency domain with a low pass filter.
  filter,
};

/// Port channel estimator time domain interpolation strategy.

/// Port channel estimator time domain interpolation strategy.
enum class port_channel_estimator_td_interpolation_strategy {
  /// Performs linear interpolation between the symbols containing DM-RS.
  /// Performs linear interpolation between the symbols containing DM-RS.
  interpolate = 0,
  /// Averages all time domain estimates.
  /// Averages all time domain estimates.
  average
};


} // namespace ocudu
