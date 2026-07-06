// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar encoder interface.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/polar/polar_encoder.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar encoder interface.

#pragma once


#include "ocudu/adt/span.h"
#include <cstdint>


namespace ocudu {

/// Polar encoder interface.

/// Polar encoder interface.
class polar_encoder
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~polar_encoder() = default;

  /// \brief Encodes the input vector into a codeword with the specified polar encoder.
  /// \param[out] output       The encoder output vector.
  /// \param[in]  input        The encoder input vector.
  /// \param[in] code_size_log The \f$ log_2\f$ of the number of bits of the encoder input/output vector.
  ///     It cannot be larger than the maximum \c code_size_log specified in \c q.code_size_log of
  ///     the \c ocudu_polar_encoder_t structure.

  /// \brief Encodes the input vector into a codeword with the specified polar encoder.
  /// \param[out] output       The encoder output vector.
  /// \param[in]  input        The encoder input vector.
  /// \param[in] code_size_log The \f$ log_2\f$ of the number of bits of the encoder input/output vector.
  ///     It cannot be larger than the maximum \c code_size_log specified in \c q.code_size_log of
  ///     the \c ocudu_polar_encoder_t structure.
  virtual void encode(span<uint8_t> output, span<const uint8_t> input, unsigned code_size_log) = 0;
};


} // namespace ocudu
