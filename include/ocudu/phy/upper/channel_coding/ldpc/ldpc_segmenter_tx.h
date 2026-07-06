// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief LDPC codeblock segmentation (transmit side).
// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/ldpc/ldpc_segmenter_tx.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief LDPC codeblock segmentation (transmit side).
#pragma once


#include "ocudu/phy/upper/codeblock_metadata.h"


namespace ocudu {


class ldpc_segmenter_buffer;

/// Carries out the segmentation of a transport block into a number of codeblocks.

/// Carries out the segmentation of a transport block into a number of codeblocks.
class ldpc_segmenter_tx
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~ldpc_segmenter_tx() = default;

  /// \brief Configures a new transport block for performing the segmentation on a codeblock basis without intermediate
  /// buffers.
  ///
  /// If needed, a CRC is attached to the generated segment, according to TS38.212 Section 5.2.2. Moreover, the
  /// transport block CRC is attached to the last segment, as per TS38.212 Section 7.2.1. The function also computes
  /// relevant segment metadata (e.g., coded and rate-matched lengths) according to TS38.212 Section 5.4.2.1.
  ///
  /// \param[in] cfg Parameters affecting splitting and codeblock metadata.
  /// \return A reference to the LDPC segmenter buffer.

  /// \brief Configures a new transport block for performing the segmentation on a codeblock basis without intermediate
  /// buffers.
  ///
  /// If needed, a CRC is attached to the generated segment, according to TS38.212 Section 5.2.2. Moreover, the
  /// transport block CRC is attached to the last segment, as per TS38.212 Section 7.2.1. The function also computes
  /// relevant segment metadata (e.g., coded and rate-matched lengths) according to TS38.212 Section 5.4.2.1.
  ///
  /// \param[in] cfg Parameters affecting splitting and codeblock metadata.
  /// \return A reference to the LDPC segmenter buffer.
  virtual const ldpc_segmenter_buffer& new_transmission(const segmenter_config& cfg) = 0;
};


} // namespace ocudu
