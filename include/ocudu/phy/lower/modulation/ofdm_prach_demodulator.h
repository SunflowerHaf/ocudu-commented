// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/lower/modulation/ofdm_prach_demodulator.h  (62 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/prach_buffer.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {

/// \brief OFDM PRACH demodulator.
///
/// Performs OFDM demodulation for all the PRACH frequency- and time-domain occasions within a PRACH slot as per
/// TS38.211 Section 5.3.2.

/// \brief OFDM PRACH demodulator.
///
/// Performs OFDM demodulation for all the PRACH frequency- and time-domain occasions within a PRACH slot as per
/// TS38.211 Section 5.3.2.
class ofdm_prach_demodulator
{
public:
  /// Collects the necessary parameters to demodulate PRACH frequency- and time-domain occasions within a slot.
  /// Collects the necessary parameters to demodulate PRACH frequency- and time-domain occasions within a slot.
  struct configuration {
    /// \brief OFDM slot in which the PRACH window starts.
    ///
    /// The slot contains uplink resource grid subcarrier spacing. Expresses the numerology \f$\mu\f$.
    /// \brief OFDM slot in which the PRACH window starts.
    ///
    /// The slot contains uplink resource grid subcarrier spacing. Expresses the numerology \f$\mu\f$.
    slot_point slot;
    /// PRACH preamble format.
    /// PRACH preamble format.
    prach_format_type format;
    /// Number of time-domain occasions.
    /// Number of time-domain occasions.
    unsigned nof_td_occasions;
    /// Number of frequency-domain occasions.
    /// Number of frequency-domain occasions.
    unsigned nof_fd_occasions;
    /// Starting symbol index for the first PRACH TD occasion within the slot {0, ..., 13} at \c pusch_scs.
    /// Starting symbol index for the first PRACH TD occasion within the slot {0, ..., 13} at \c pusch_scs.
    unsigned start_symbol;
    /// PRACH frequency location (see \ref prach_buffer_context::rb_offset).
    /// PRACH frequency location (see \ref prach_buffer_context::rb_offset).
    unsigned rb_offset;
    /// Uplink resource grid size (see \ref prach_buffer_context::nof_prb_ul_grid).
    /// Uplink resource grid size (see \ref prach_buffer_context::nof_prb_ul_grid).
    unsigned nof_prb_ul_grid;
    /// Destination port identifier.
    /// Destination port identifier.
    unsigned port;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~ofdm_prach_demodulator() = default;

  /// \brief Demodulates a PRACH occasion as described in TS38.211 Section 5.3.2.
  ///
  /// For long preambles, the input shall contain the cyclic prefix of length \f$N_{CP,l}^{RA}\f$) and a time-domain
  /// sequence of length \f$N_u\f$. Also, the number of time-domain occasions must be one.
  ///
  /// For short preamble formats, the input shall correspond to one slot at \ref configuration::pusch_scs.
  ///
  /// An assertion is triggered if:
  /// - the input samples are not sufficient,
  /// - the buffer dimensions cannot contain the demodulated sequences, or
  /// - the port identifier exceeds the number of ports contained in the destination buffer.
  ///
  /// \param[out] buffer    Frequency-domain signal corresponding to one PRACH receive occasion.
  /// \param[in] input      PRACH receive window baseband samples.
  /// \param[in] config     PRACH demodulator configuration parameters.

  /// \brief Demodulates a PRACH occasion as described in TS38.211 Section 5.3.2.
  ///
  /// For long preambles, the input shall contain the cyclic prefix of length \f$N_{CP,l}^{RA}\f$) and a time-domain
  /// sequence of length \f$N_u\f$. Also, the number of time-domain occasions must be one.
  ///
  /// For short preamble formats, the input shall correspond to one slot at \ref configuration::pusch_scs.
  ///
  /// An assertion is triggered if:
  /// - the input samples are not sufficient,
  /// - the buffer dimensions cannot contain the demodulated sequences, or
  /// - the port identifier exceeds the number of ports contained in the destination buffer.
  ///
  /// \param[out] buffer    Frequency-domain signal corresponding to one PRACH receive occasion.
  /// \param[in] input      PRACH receive window baseband samples.
  /// \param[in] config     PRACH demodulator configuration parameters.
  virtual void demodulate(prach_buffer& buffer, span<const cf_t> input, const configuration& config) = 0;
};
} // namespace ocudu
