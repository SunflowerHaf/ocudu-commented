// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar interleaver interface.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/polar/polar_interleaver.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar interleaver interface.

#pragma once


#include "ocudu/adt/span.h"
#include <cstdint>


namespace ocudu {

/// Identifiers for Tx and Rx interleavers.

/// Identifiers for Tx and Rx interleavers.
enum class polar_interleaver_direction { tx, rx };

/// Polar interleaver interface.

/// Polar interleaver interface.
class polar_interleaver
{
public:
  virtual ~polar_interleaver() = default;

  /// \brief Implements Polar code interleaver as described in TS38.212 V15.9.0 Section 5.3.1.1
  ///
  /// \attention The input and output data cannot be the same.
  ///
  /// \param[out] out       Output data.
  /// \param[in]  in        Input data.
  /// \param[in]  direction Set to TX or RX for encoder or decoder, respectively.

  /// \brief Implements Polar code interleaver as described in TS38.212 V15.9.0 Section 5.3.1.1
  ///
  /// \attention The input and output data cannot be the same.
  ///
  /// \param[out] out       Output data.
  /// \param[in]  in        Input data.
  /// \param[in]  direction Set to TX or RX for encoder or decoder, respectively.
  virtual void interleave(span<uint8_t> out, span<const uint8_t> in, polar_interleaver_direction direction) = 0;
};


} // namespace ocudu
