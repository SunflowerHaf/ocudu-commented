// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pusch/pusch_decoder_buffer.h  (43 lines)
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
#include "ocudu/phy/upper/log_likelihood_ratio.h"


namespace ocudu {

/// \brief PUSCH decoder buffer interface.
///
/// Interfaces the UL-SCH demultiplexer with the different message decoders (SCH data, HARQ ACK, CSI Part 1, and CSI
/// Part 2). The UL-SCH demultiplexer notifies processed continuous blocks of data using the method \ref on_new_softbits
/// and notifies the end of data using the method \ref on_end_softbits.

/// \brief PUSCH decoder buffer interface.
///
/// Interfaces the UL-SCH demultiplexer with the different message decoders (SCH data, HARQ ACK, CSI Part 1, and CSI
/// Part 2). The UL-SCH demultiplexer notifies processed continuous blocks of data using the method \ref on_new_softbits
/// and notifies the end of data using the method \ref on_end_softbits.
class pusch_decoder_buffer
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~pusch_decoder_buffer() = default;

  /// \brief Gets a view of the next block of demultiplexed soft bits.
  ///
  /// This method is temporal. It allows the UL-SCH demultiplexer to get a view of the soft bits storage in the decoder
  /// to avoid to copy.
  ///
  /// \param[in] block_size Block size of continuous soft bits to write.
  /// \return A read-write view of the next soft bits available for writing.

  /// \brief Gets a view of the next block of demultiplexed soft bits.
  ///
  /// This method is temporal. It allows the UL-SCH demultiplexer to get a view of the soft bits storage in the decoder
  /// to avoid to copy.
  ///
  /// \param[in] block_size Block size of continuous soft bits to write.
  /// \return A read-write view of the next soft bits available for writing.
  virtual span<log_likelihood_ratio> get_next_block_view(unsigned block_size) = 0;

  /// \brief Notifies a new block of soft bits.
  /// \param[in] softbits Soft bits belonging to a codeword.
  /// \remark \c demodulated and \c scrambled must have the same size.

  /// \brief Notifies a new block of soft bits.
  /// \param[in] softbits Soft bits belonging to a codeword.
  /// \remark \c demodulated and \c scrambled must have the same size.
  virtual void on_new_softbits(span<const log_likelihood_ratio> softbits) = 0;

  /// \brief Notifies the end of the softbits.
  ///
  /// It can be used by the decoder to start decoding.

  /// \brief Notifies the end of the softbits.
  ///
  /// It can be used by the decoder to start decoding.
  virtual void on_end_softbits() = 0;
};


} // namespace ocudu
