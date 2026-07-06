// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/pusch_tpmi_formatter.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pusch/pusch_tpmi_select.h"
#include "ocudu/support/format/delimited_formatter.h"


namespace fmt {

/// \brief Custom formatter for \c pusch_tpmi_select_info.

/// \brief Custom formatter for \c pusch_tpmi_select_info.
template <>
struct formatter<ocudu::pusch_tpmi_select_info> {
public:
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return helper.parse(ctx);
  }


  template <typename FormatContext>
  auto format(const ocudu::pusch_tpmi_select_info& context, FormatContext& ctx) const
  {
    unsigned max_nof_layers = context.get_max_nof_layers();
    for (unsigned i_nof_layers = 1; i_nof_layers <= max_nof_layers; ++i_nof_layers) {
      const auto& info = context.get_tpmi_select(i_nof_layers);
      helper.format_always(ctx,
                           "{}_layer: tpmi={} sinr=({:+.1f})dB",
                           i_nof_layers,
                           info.tpmi,
                           ocudu::span<const float>(info.sinr_dB_layer));
    }


    return ctx.out();
  }


private:
  ocudu::delimited_formatter helper;
};


} // namespace fmt
