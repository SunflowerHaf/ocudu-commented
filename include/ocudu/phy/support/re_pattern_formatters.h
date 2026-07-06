// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/re_pattern_formatters.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/re_pattern.h"
#include "ocudu/support/format/delimited_formatter.h"
#include "fmt/format.h"


namespace fmt {

/// \brief Custom formatter for \c re_pattern.

/// \brief Custom formatter for \c re_pattern.
template <>
struct formatter<ocudu::re_pattern> {
  /// Helper used to parse formatting options and format fields.
  /// Helper used to parse formatting options and format fields.
  ocudu::delimited_formatter helper;

  /// Default constructor.

  /// Default constructor.
  formatter() = default;


  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return helper.parse(ctx);
  }


  template <typename FormatContext>
  auto format(const ocudu::re_pattern& pattern, FormatContext& ctx) const
  {
    helper.format_always(
        ctx, "symb={:n}", static_cast<ocudu::bounded_bitset<ocudu::MAX_NSYMB_PER_SLOT>>(pattern.symbols));
    helper.format_always(ctx, "rb={:n}", pattern.crb_mask);
    helper.format_always(
        ctx, "re={:n}", static_cast<ocudu::bounded_bitset<ocudu::NOF_SUBCARRIERS_PER_RB>>(pattern.re_mask));


    return ctx.out();
  }
};


} // namespace fmt
