// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/ldpc/ldpc_encoder_buffer.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include <stdint.h>


namespace ocudu {

/// \brief LDPC encoder output buffer interface.
///
/// This interface allows the LDPC encoder to provide the encoded bits to the rate matcher without using an intermediate
/// buffer.

/// \brief LDPC encoder output buffer interface.
///
/// This interface allows the LDPC encoder to provide the encoded bits to the rate matcher without using an intermediate
/// buffer.
class ldpc_encoder_buffer
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ldpc_encoder_buffer() = default;

  /// Gets the encoded codeblock length.

  /// Gets the encoded codeblock length.
  virtual unsigned get_codeblock_length() const = 0;

  /// \brief Reads the encoded codeblock data starting at bit index \c offset.
  ///
  /// The data size plus the offset shall not exceed the encoded codeblock length.
  ///
  /// \param[out] data   Read destination.
  /// \param[in]  offset Initial read position.

  /// \brief Reads the encoded codeblock data starting at bit index \c offset.
  ///
  /// The data size plus the offset shall not exceed the encoded codeblock length.
  ///
  /// \param[out] data   Read destination.
  /// \param[in]  offset Initial read position.
  virtual void write_codeblock(span<uint8_t> data, unsigned offset) const = 0;
};


} // namespace ocudu
