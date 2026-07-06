// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pdcch/pdcch_encoder.h  (38 lines)
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
#include "ocudu/ran/pdcch/pdcch_constants.h"
#include <memory>


namespace ocudu {

/// Describes the PDCCH encoder interface.

/// Describes the PDCCH encoder interface.
class pdcch_encoder
{
public:
  /// Describes the necessary parameters to encode PDCCH message.
  /// Describes the necessary parameters to encode PDCCH message.
  struct config_t {
    /// Number of rate-matched bits.
    /// Number of rate-matched bits.
    unsigned E;
    /// RNTI used for CRC bits scrambling according to TS38.212 Section 7.3.2.
    /// RNTI used for CRC bits scrambling according to TS38.212 Section 7.3.2.
    unsigned rnti;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~pdcch_encoder() = default;

  /// \brief Encodes a PDCCH message.
  /// \param [in]  data    - unencoded message bits
  /// \param [out] encoded - encoded bits
  /// \param [in]  config  - encoder configuration
  ///
  /// \remark size of + 24 bits of CRC gives K parameter for the Polar encoder


  /// \brief Encodes a PDCCH message.
  /// \param [in]  data    - unencoded message bits
  /// \param [out] encoded - encoded bits
  /// \param [in]  config  - encoder configuration
  ///
  /// \remark size of + 24 bits of CRC gives K parameter for the Polar encoder

  virtual void encode(span<uint8_t> encoded, span<const uint8_t> data, const config_t& config) = 0;
};


} // namespace ocudu
