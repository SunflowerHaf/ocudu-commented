// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/ssb/pbch_encoder.h  (64 lines)
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
#include "ocudu/ran/pci.h"
#include "ocudu/ran/ssb/ssb_configuration.h"
#include "ocudu/ran/ssb/ssb_properties.h"
#include <array>


namespace ocudu {

/// PBCH encoder interface.

/// PBCH encoder interface.
class pbch_encoder
{
public:
  /// Generated payload length. TS38.212 refers to it as \e A.
  /// Generated payload length. TS38.212 refers to it as \e A.
  static constexpr unsigned A = 32;
  /// Higher layer generated payload length. TS38.212 refers to it as \e A_hat.
  /// Higher layer generated payload length. TS38.212 refers to it as \e A_hat.
  static constexpr unsigned A_HAT = 24;
  /// CRC length in bits.
  /// CRC length in bits.
  static constexpr unsigned CRC_LEN = 24;
  /// Payload size plus CRC length.
  /// Payload size plus CRC length.
  static constexpr unsigned B = (A + CRC_LEN);
  /// Number of rate matched bits.
  /// Number of rate matched bits.
  static constexpr unsigned E = 864;
  /// Polar encoder order, logarithmic representation.
  /// Polar encoder order, logarithmic representation.
  static constexpr unsigned POLAR_N_MAX_LOG = 9;
  /// Number of encoded bits.
  /// Number of encoded bits.
  static constexpr unsigned POLAR_N_MAX = (1U << POLAR_N_MAX_LOG);

  /// Describes a PBCH message to encode.

  /// Describes a PBCH message to encode.
  struct pbch_msg_t {
    /// Physical cell identifier.
    /// Physical cell identifier.
    pci_t N_id;
    /// SSB candidate index in a 5ms burst.
    /// SSB candidate index in a 5ms burst.
    ssb_id_t ssb_idx;
    /// Maximum number of SS/PBCH block candidates in a 5ms burst, described in TS38.213 Section 4.1.
    /// Maximum number of SS/PBCH block candidates in a 5ms burst, described in TS38.213 Section 4.1.
    unsigned L_max;
    /// Flag: true if the SS/PBCH block transmission is in an odd half frame, false otherwise.
    /// Flag: true if the SS/PBCH block transmission is in an odd half frame, false otherwise.
    bool hrf;
    /// Actual PBCH payload provided by higher layers.
    /// Actual PBCH payload provided by higher layers.
    std::array<uint8_t, A_HAT> payload;
    /// System Frame Number.
    /// System Frame Number.
    unsigned sfn;
    /// \brief Subcarrier offset.
    ///
    /// Corresponds to parameter \f$k_{SSB}\f$ as defined in TS38.211 Section 7.4.3.1. The value range is {0, ..., 11}
    /// if \f$L_{MAX} = 64\f$, {0, ..., 23} otherwise.
    /// \brief Subcarrier offset.
    ///
    /// Corresponds to parameter \f$k_{SSB}\f$ as defined in TS38.211 Section 7.4.3.1. The value range is {0, ..., 11}
    /// if \f$L_{MAX} = 64\f$, {0, ..., 23} otherwise.
    ssb_subcarrier_offset k_ssb;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~pbch_encoder() = default;

  /// \brief Encodes a PBCH message.
  /// \param[out] encoded Encoded data.
  /// \param[in]  pbch_msg PBCH message to encode.

  /// \brief Encodes a PBCH message.
  /// \param[out] encoded Encoded data.
  /// \param[in]  pbch_msg PBCH message to encode.
  virtual void encode(span<uint8_t> encoded, const pbch_msg_t& pbch_msg) = 0;
};


} // namespace ocudu
