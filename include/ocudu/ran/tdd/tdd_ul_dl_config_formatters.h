// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/tdd/tdd_ul_dl_config_formatters.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/tdd/tdd_ul_dl_config.h"
#include "ocudu/support/format/fmt_basic_parser.h"
#include "fmt/std.h"


namespace fmt {


template <>
struct formatter<ocudu::tdd_ul_dl_pattern> : public basic_parser {
  template <typename FormatContext>
  auto format(const ocudu::tdd_ul_dl_pattern& cfg, FormatContext& ctx) const
  {
    return format_to(ctx.out(),
                     "period={} dl_slots={} dl_symbols={} ul_slots={} ul_symbols={}",
                     cfg.dl_ul_tx_period_nof_slots,
                     cfg.nof_dl_slots,
                     cfg.nof_dl_symbols,
                     cfg.nof_ul_slots,
                     cfg.nof_ul_symbols);
  }
};


template <>
struct formatter<ocudu::tdd_ul_dl_config_common> : public basic_parser {
  template <typename FormatContext>
  auto format(const ocudu::tdd_ul_dl_config_common& cfg, FormatContext& ctx) const
  {
    return format_to(
        ctx.out(), "scs={} pattern1={{{}}} pattern2={{{}}}", fmt::underlying(cfg.ref_scs), cfg.pattern1, cfg.pattern2);
  }
};


} // namespace fmt
