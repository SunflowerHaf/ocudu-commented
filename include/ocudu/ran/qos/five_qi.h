// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/qos/five_qi.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/ocudu_assert.h"
#include "fmt/format.h"


namespace ocudu {

/// See TS 38.463: Five QI valid values: (0..255)

/// See TS 38.463: Five QI valid values: (0..255)
constexpr uint16_t MAX_FIVEQI = 255;

/// Five QI.

/// Five QI.
enum class five_qi_t : uint16_t { min = 0, max = MAX_FIVEQI, invalid = MAX_FIVEQI + 1 };

/// Convert Five QI type to integer.

/// Convert Five QI type to integer.
constexpr uint16_t five_qi_to_uint(five_qi_t five_qi)
{
  return static_cast<uint16_t>(five_qi);
}

/// Convert integer to Five QI type.

/// Convert integer to Five QI type.
constexpr five_qi_t uint_to_five_qi(uint16_t five_qi)
{
  ocudu_assert(
      five_qi < MAX_FIVEQI, "Invalid 5QI {} - Must be between [{}..{}]", five_qi, five_qi_t::min, five_qi_t::max);
  return static_cast<five_qi_t>(five_qi);
}


} // namespace ocudu

// Formatters

// Formatters
namespace fmt {
template <>
struct formatter<ocudu::five_qi_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::five_qi_t five_qi, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "5QI={:#x}", five_qi_to_uint(five_qi));
  }
};


} // namespace fmt
