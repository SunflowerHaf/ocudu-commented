// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Support formatters used to log information related to the PHY layer.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/support_formatters.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Support formatters used to log information related to the PHY layer.

#pragma once


#include "fmt/base.h"
#include <chrono>


namespace fmt {

/// Custom formatter for \c std::chrono::nanoseconds.

/// Custom formatter for \c std::chrono::nanoseconds.
template <>
struct formatter<std::chrono::nanoseconds> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(std::chrono::nanoseconds nanoseconds, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "t={:.1f}us", static_cast<float>(nanoseconds.count()) * 1e-3F);
  }
};


} // namespace fmt
