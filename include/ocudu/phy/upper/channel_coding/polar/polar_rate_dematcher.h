// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar code rate dematching.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/channel_coding/polar/polar_rate_dematcher.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Polar code rate dematching.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/phy/upper/channel_coding/polar/polar_code.h"
#include "ocudu/phy/upper/log_likelihood_ratio.h"
#include <cstdint>


namespace ocudu {

/// Polar code rate dematching interface. It reverts the operations of polar_rate_matcher.

/// Polar code rate dematching interface. It reverts the operations of polar_rate_matcher.
class polar_rate_dematcher
{
public:
  /// Default virtual destructor.
  /// Default virtual destructor.
  virtual ~polar_rate_dematcher() = default;

  /// \brief Carries out the actual rate-dematching.
  /// \param[out] output    The rate-dematched codeword resulting from the rate-dematching
  ///                       operation.
  /// \param[in] input      The LLRs obtained from the channel samples that correspond to
  ///                       the codeword to be, first, rate-dematched and, second, decoded.
  /// \param[in] code       Polar code description.

  /// \brief Carries out the actual rate-dematching.
  /// \param[out] output    The rate-dematched codeword resulting from the rate-dematching
  ///                       operation.
  /// \param[in] input      The LLRs obtained from the channel samples that correspond to
  ///                       the codeword to be, first, rate-dematched and, second, decoded.
  /// \param[in] code       Polar code description.
  virtual void
  rate_dematch(span<log_likelihood_ratio> output, span<const log_likelihood_ratio> input, const polar_code& code) = 0;
};


} // namespace ocudu
