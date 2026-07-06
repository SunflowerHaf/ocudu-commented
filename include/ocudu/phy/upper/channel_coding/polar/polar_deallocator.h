// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar deallocator - Interface.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/polar/polar_deallocator.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar deallocator - Interface.

#pragma once


#include "ocudu/phy/upper/channel_coding/polar/polar_code.h"


namespace ocudu {

/// Polar deallocator interface.

/// Polar deallocator interface.
class polar_deallocator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~polar_deallocator() = default;

  /// \brief Extracts the information bits from the polar decoder output.
  ///
  /// \param[out] message         Information bits.
  /// \param[in]  output_decoder  Output bits of the polar decoder.
  /// \param[in]  code            Polar code description.

  /// \brief Extracts the information bits from the polar decoder output.
  ///
  /// \param[out] message         Information bits.
  /// \param[in]  output_decoder  Output bits of the polar decoder.
  /// \param[in]  code            Polar code description.
  virtual void deallocate(span<uint8_t> message, span<const uint8_t> output_decoder, const polar_code& code) = 0;
};


} // namespace ocudu
