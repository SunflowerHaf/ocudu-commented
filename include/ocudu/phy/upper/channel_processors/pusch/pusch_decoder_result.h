// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_processors/pusch/pusch_decoder_result.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/math/stats.h"


namespace ocudu {

/// PUSCH decoding statistics.

/// PUSCH decoding statistics.
struct pusch_decoder_result {
  /// Denotes whether the received transport block passed the CRC.
  /// Denotes whether the received transport block passed the CRC.
  bool tb_crc_ok = false;
  /// Total number of codeblocks in the current codeword.
  /// Total number of codeblocks in the current codeword.
  unsigned nof_codeblocks_total = 0;
  /// \brief LDPC decoding statistics.
  ///
  /// Provides access to LDPC decoding statistics such as the number of decoded codeblocks (via
  /// <tt>ldpc_stats->get_nof_observations()</tt>) or the average number of iterations for correctly decoded
  /// codeblocks (via <tt>ldpc_stats->get_mean()</tt>).
  /// \brief LDPC decoding statistics.
  ///
  /// Provides access to LDPC decoding statistics such as the number of decoded codeblocks (via
  /// <tt>ldpc_stats->get_nof_observations()</tt>) or the average number of iterations for correctly decoded
  /// codeblocks (via <tt>ldpc_stats->get_mean()</tt>).
  sample_statistics<unsigned> ldpc_decoder_stats;
};


} // namespace ocudu
