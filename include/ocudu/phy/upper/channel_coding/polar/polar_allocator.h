// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar allocator interface.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/polar/polar_allocator.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar allocator interface.

#pragma once


#include "ocudu/phy/upper/channel_coding/polar/polar_code.h"


namespace ocudu {

/// Polar allocator interface.

/// Polar allocator interface.
class polar_allocator
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~polar_allocator() = default;

  /// \brief Allocates the message bits into the encoder input.
  ///
  /// \param[out] input_encoder   Sequence of allocated bits to be fed to the polar encoder.
  /// \param[in]  message         Information bits to be allocated.
  /// \param[in]  code            Polar code description.

  /// \brief Allocates the message bits into the encoder input.
  ///
  /// \param[out] input_encoder   Sequence of allocated bits to be fed to the polar encoder.
  /// \param[in]  message         Information bits to be allocated.
  /// \param[in]  code            Polar code description.
  virtual void allocate(span<uint8_t> input_encoder, span<const uint8_t> message, const polar_code& code) = 0;
};


} // namespace ocudu
