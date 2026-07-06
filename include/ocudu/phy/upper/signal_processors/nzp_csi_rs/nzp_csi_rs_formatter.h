// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Formatters for signal processor related structures.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/upper/signal_processors/nzp_csi_rs/nzp_csi_rs_formatter.h  (49 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Formatters for signal processor related structures.

#pragma once


#include "ocudu/phy/support/precoding_formatters.h"
#include "ocudu/phy/upper/signal_processors/nzp_csi_rs/nzp_csi_rs_generator.h"


namespace fmt {
/// \brief Custom formatter for \c nzp_csi_rs_generator::config_t.
/// \brief Custom formatter for \c nzp_csi_rs_generator::config_t.
template <>
struct formatter<ocudu::nzp_csi_rs_generator::config_t> {
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
  auto format(const ocudu::nzp_csi_rs_generator::config_t& nzp_csi_config, FormatContext& ctx) const
  {
    helper.format_always(ctx, "prb=[{}, {})", nzp_csi_config.start_rb, nzp_csi_config.start_rb + nzp_csi_config.nof_rb);
    helper.format_always(ctx, "row={}", nzp_csi_config.csi_rs_mapping_table_row);
    helper.format_always(ctx, "Ki={}", ocudu::span<const unsigned>(nzp_csi_config.freq_allocation_ref_idx));
    helper.format_always(ctx, "l0={}", nzp_csi_config.symbol_l0);
    helper.format_always(ctx, "l1={}", nzp_csi_config.symbol_l1);
    helper.format_always(ctx, "CDM={}", to_string(nzp_csi_config.cdm));
    helper.format_always(ctx, "density={}", to_string(nzp_csi_config.freq_density));
    helper.format_if_verbose(ctx, "slot={}", nzp_csi_config.slot);
    helper.format_if_verbose(ctx, "cp={}", nzp_csi_config.cp.to_string());
    helper.format_if_verbose(ctx, "sc_id={}", nzp_csi_config.scrambling_id);
    helper.format_if_verbose(ctx, "amplitude={}", nzp_csi_config.amplitude);
    helper.format_if_verbose(ctx, "precoding={}", nzp_csi_config.precoding);


    return ctx.out();
  }
};


} // namespace fmt
