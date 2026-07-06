// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief LDPC rate matching.
// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/ldpc/ldpc_rate_matcher.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief LDPC rate matching.
#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/phy/upper/codeblock_metadata.h"


namespace ocudu {


class ldpc_encoder_buffer;

/// LDPC rate matching (i.e., bit selection and bit interleaving) interface.

/// LDPC rate matching (i.e., bit selection and bit interleaving) interface.
class ldpc_rate_matcher
{
public:
  /// Default virtual destructor.
  /// Default virtual destructor.
  virtual ~ldpc_rate_matcher() = default;

  /// \brief Carries out the rate matching of a codeblock.
  ///
  /// \param[out] output  Rate matched codeblock.
  /// \param[in]  input   Reference to an LDPC encoder buffer.
  /// \param[in]  cfg     Configuration parameters.
  /// \remark The sizes of \c input and \c output determine the behavior of the rate matching algorithm.

  /// \brief Carries out the rate matching of a codeblock.
  ///
  /// \param[out] output  Rate matched codeblock.
  /// \param[in]  input   Reference to an LDPC encoder buffer.
  /// \param[in]  cfg     Configuration parameters.
  /// \remark The sizes of \c input and \c output determine the behavior of the rate matching algorithm.
  virtual void rate_match(bit_buffer& output, const ldpc_encoder_buffer& input, const codeblock_metadata& cfg) = 0;
};


} // namespace ocudu
