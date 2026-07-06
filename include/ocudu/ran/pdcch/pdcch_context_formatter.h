// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/pdcch_context_formatter.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pdcch/pdcch_context.h"
#include "ocudu/support/format/delimited_formatter.h"


namespace fmt {

/// \brief Custom formatter for \c pdcch_context.

/// \brief Custom formatter for \c pdcch_context.
template <>
struct formatter<ocudu::pdcch_context> {
public:
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return helper.parse(ctx);
  }


  template <typename FormatContext>
  auto format(const ocudu::pdcch_context& context, FormatContext& ctx) const
  {
    helper.format_always(ctx, "ss_id={}", fmt::underlying(context.ss_id));
    helper.format_always(ctx, "format={}", context.dci_format);
    if (context.harq_feedback_timing.has_value()) {
      helper.format_if_verbose(ctx, "harq_feedback_timing={}", context.harq_feedback_timing.value());
    }
    return ctx.out();
  }


private:
  ocudu::delimited_formatter helper;
};


} // namespace fmt
