// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/equalization/channel_equalizer_algorithm_type.h  (29 lines)
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

/// Channel equalizer algorithm type enumeration.

/// Channel equalizer algorithm type enumeration.
enum class channel_equalizer_algorithm_type {
  /// Zero Forcing.
  /// Zero Forcing.
  zf = 0,
  /// Minimum Mean Square Error.
  /// Minimum Mean Square Error.
  mmse
};

/// Convert channel equalizer algorithm type to string.

/// Convert channel equalizer algorithm type to string.
inline const char* to_string(channel_equalizer_algorithm_type type)
{
  switch (type) {
    case channel_equalizer_algorithm_type::zf:
      return "ZF";
    case channel_equalizer_algorithm_type::mmse:
    default:
      return "MMSE";
  }
}


} // namespace ocudu
