// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/prs/formatters.h  (49 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/support/precoding_formatters.h"
#include "ocudu/phy/upper/signal_processors/prs/prs_generator_configuration.h"
#include "ocudu/ran/precoding/precoding_weight_matrix_formatters.h"


namespace fmt {

/// \brief Custom formatter for \c pdcch_processor::coreset_description.

/// \brief Custom formatter for \c pdcch_processor::coreset_description.
template <>
struct formatter<ocudu::prs_generator_configuration> {
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
  auto format(const ocudu::prs_generator_configuration& config, FormatContext& ctx) const
  {
    helper.format_if_verbose(ctx, "slot={}", config.slot);
    helper.format_if_verbose(ctx, "cp={}", config.cp);
    helper.format_always(ctx, "n_id={}", config.n_id_prs);
    helper.format_always(ctx, "comb_size={}", fmt::underlying(config.comb_size));
    helper.format_always(ctx, "comb_offset={}", config.comb_offset);
    helper.format_always(
        ctx,
        "t_alloc={}",
        ocudu::interval<unsigned>(config.start_symbol, config.start_symbol + static_cast<unsigned>(config.duration)));
    helper.format_if_verbose(ctx, "rb_start={}", config.prb_start);
    helper.format_always(ctx, "f_alloc={}", config.freq_alloc);
    helper.format_if_verbose(ctx, "power_offset={}", config.power_offset_dB);
    helper.format_if_verbose(ctx, "precoding={}", config.precoding);


    return ctx.out();
  }
};


} // namespace fmt
