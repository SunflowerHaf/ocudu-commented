// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar rate matcher interface.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/polar/polar_rate_matcher.h  (30 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar rate matcher interface.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/phy/upper/channel_coding/polar/polar_code.h"
#include <cstdint>


namespace ocudu {

/// Polar rate matcher interface.

/// Polar rate matcher interface.
class polar_rate_matcher
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~polar_rate_matcher() = default;

  /// \brief Carries out the actual rate-matching.
  /// \param[out] output  The rate-matched codeword resulting from the rate-matching operation.
  /// \param[in]  input   The codeword obtained from the polar encoder.
  /// \param[in]  code    The polar code description.

  /// \brief Carries out the actual rate-matching.
  /// \param[out] output  The rate-matched codeword resulting from the rate-matching operation.
  /// \param[in]  input   The codeword obtained from the polar encoder.
  /// \param[in]  code    The polar code description.
  virtual void rate_match(span<uint8_t> output, span<const uint8_t> input, const polar_code& code) = 0;
};


} // namespace ocudu
