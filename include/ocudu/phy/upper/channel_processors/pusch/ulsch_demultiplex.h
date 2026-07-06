// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pusch/ulsch_demultiplex.h  (86 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/mask_types.h"
#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/sch/modulation_scheme.h"

/// \file
/// \brief Uplink Shared Channel demultiplexer interface declaration.


/// \file
/// \brief Uplink Shared Channel demultiplexer interface declaration.

namespace ocudu {


class pusch_codeword_buffer;
class pusch_decoder_buffer;

/// \brief User interface of the Uplink Shared Channel (UL-SCH) demultiplexer.
///
/// Note that, for calculating the CSI Part 2 report size, it is necessary to decode the CSI Part 1. Consequently,
/// \ref ulsch_demultiplex::set_csi_part2 must be called with the size information obtained from CSI Part 1 before the
/// CSI Part 2 report can be demultiplexed.
///
/// All fields can be demultiplexed simultaneously if CSI Part 2 is not present (see \ref
/// ulsch_demultiplex::demultiplex).

/// \brief User interface of the Uplink Shared Channel (UL-SCH) demultiplexer.
///
/// Note that, for calculating the CSI Part 2 report size, it is necessary to decode the CSI Part 1. Consequently,
/// \ref ulsch_demultiplex::set_csi_part2 must be called with the size information obtained from CSI Part 1 before the
/// CSI Part 2 report can be demultiplexed.
///
/// All fields can be demultiplexed simultaneously if CSI Part 2 is not present (see \ref
/// ulsch_demultiplex::demultiplex).
class ulsch_demultiplex
{
public:
  /// Collects the necessary parameters for performing the UL-SCH demultiplex according to TS38.212 Section 6.2.7.
  /// Collects the necessary parameters for performing the UL-SCH demultiplex according to TS38.212 Section 6.2.7.
  struct configuration {
    /// Modulation scheme.
    /// Modulation scheme.
    modulation_scheme modulation;
    /// Number of layers {1, ..., 4}
    /// Number of layers {1, ..., 4}
    unsigned nof_layers;
    /// Number of Physical Resource Blocks allocated to the UL-SCH transmission.
    /// Number of Physical Resource Blocks allocated to the UL-SCH transmission.
    unsigned nof_prb;
    /// Index of the first allocated OFDM symbol within the slot.
    /// Index of the first allocated OFDM symbol within the slot.
    unsigned start_symbol_index;
    /// Number of allocated OFDM symbols.
    /// Number of allocated OFDM symbols.
    unsigned nof_symbols;
    /// Number of reserved bits for HARQ-ACK. Parameter \f$G^\textup{HARQ-ACK}_\textup{rvd}\f$.
    /// Number of reserved bits for HARQ-ACK. Parameter \f$G^\textup{HARQ-ACK}_\textup{rvd}\f$.
    unsigned nof_harq_ack_rvd;
    /// Transmission DM-RS Type.
    /// Transmission DM-RS Type.
    dmrs_config_type dmrs;
    /// Mask indicating which OFDM symbols in the slot contain DM-RS.
    /// Mask indicating which OFDM symbols in the slot contain DM-RS.
    symbol_slot_mask dmrs_symbol_mask;
    /// Number of CDM groups without data.
    /// Number of CDM groups without data.
    unsigned nof_cdm_groups_without_data;
    /// Number of HARQ-ACK information bits multiplexed in the PUSCH message. Parameter \f$O_\textup{HARQ-ACK}\f$.
    /// Number of HARQ-ACK information bits multiplexed in the PUSCH message. Parameter \f$O_\textup{HARQ-ACK}\f$.
    unsigned nof_harq_ack_bits;
    /// Number of encoded and rate-matched HARQ-ACK data bits. Parameter \f$G^\textup{HARQ-ACK}\f$.
    /// Number of encoded and rate-matched HARQ-ACK data bits. Parameter \f$G^\textup{HARQ-ACK}\f$.
    unsigned nof_enc_harq_ack_bits;
    /// Number of CSI Part 1 information bits multiplexed in the PUSCH message. Parameter \f$O_\textup{CSI-1}\f$.
    /// Number of CSI Part 1 information bits multiplexed in the PUSCH message. Parameter \f$O_\textup{CSI-1}\f$.
    unsigned nof_csi_part1_bits;
    /// Number of encoded and rate-matched CSI Part 1 data bits. Parameter \f$G^\textup{CSI-1}\f$.
    /// Number of encoded and rate-matched CSI Part 1 data bits. Parameter \f$G^\textup{CSI-1}\f$.
    unsigned nof_enc_csi_part1_bits;
  };

  /// Default destructor.

  /// Default destructor.
  virtual ~ulsch_demultiplex() = default;

  /// \brief Configures the CSI Part 2.
  /// \param[in] csi_part2              CSI Part 2 decoder buffer.
  /// \param[in] nof_csi_part2_bits     Number of CSI Part 2 information bits. Parameter \f$O_\textup{CSI-2}\f$.
  /// \param[in] nof_csi_part2_enc_bits Number of encoded and rate-matched CSI Part 2 data bits. Parameter
  /// \f$G^\textup{CSI-2}\f$.

  /// \brief Configures the CSI Part 2.
  /// \param[in] csi_part2              CSI Part 2 decoder buffer.
  /// \param[in] nof_csi_part2_bits     Number of CSI Part 2 information bits. Parameter \f$O_\textup{CSI-2}\f$.
  /// \param[in] nof_csi_part2_enc_bits Number of encoded and rate-matched CSI Part 2 data bits. Parameter
  /// \f$G^\textup{CSI-2}\f$.
  virtual void
  set_csi_part2(pusch_decoder_buffer& csi_part2, unsigned nof_csi_part2_bits, unsigned nof_csi_part2_enc_bits) = 0;

  /// \brief Demultiplexes Uplink Shared Channel (UL-SCH).
  ///
  /// Demultiplexes the different information fields from the UL-SCH transmission.
  ///
  /// \param[out] sch_data   Shared channel data soft bits.
  /// \param[out] harq_ack   HARQ-ACK information soft bits.
  /// \param[out] csi_part1  CSI Part 1 report soft bits.
  /// \param[in] config      UL-SCH demultiplexing parameters.
  /// \return A PUSCH codeword buffer, used to feed the PUSCH payload to the demultiplexer.

  /// \brief Demultiplexes Uplink Shared Channel (UL-SCH).
  ///
  /// Demultiplexes the different information fields from the UL-SCH transmission.
  ///
  /// \param[out] sch_data   Shared channel data soft bits.
  /// \param[out] harq_ack   HARQ-ACK information soft bits.
  /// \param[out] csi_part1  CSI Part 1 report soft bits.
  /// \param[in] config      UL-SCH demultiplexing parameters.
  /// \return A PUSCH codeword buffer, used to feed the PUSCH payload to the demultiplexer.
  virtual pusch_codeword_buffer& demultiplex(pusch_decoder_buffer& sch_data,
                                             pusch_decoder_buffer& harq_ack,
                                             pusch_decoder_buffer& csi_part1,
                                             const configuration&  config) = 0;
};


} // namespace ocudu
