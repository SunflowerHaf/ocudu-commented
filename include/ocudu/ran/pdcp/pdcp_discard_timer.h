// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcp/pdcp_discard_timer.h  (89 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "fmt/format.h"
#include <cstdint>


namespace ocudu {

/// PDCP NR discard timer values.
/// This timer is configured only for DRBs. In the transmitter, a new timer is started upon reception of an SDU from
/// upper layer.
/// See TS 38.322 for timer description and TS 38.331 for valid timer durations.

/// PDCP NR discard timer values.
/// This timer is configured only for DRBs. In the transmitter, a new timer is started upon reception of an SDU from
/// upper layer.
/// See TS 38.322 for timer description and TS 38.331 for valid timer durations.
enum class pdcp_discard_timer {
  ms10     = 10,
  ms20     = 20,
  ms30     = 30,
  ms40     = 40,
  ms50     = 50,
  ms60     = 60,
  ms75     = 75,
  ms100    = 100,
  ms150    = 150,
  ms200    = 200,
  ms250    = 250,
  ms300    = 300,
  ms500    = 500,
  ms750    = 750,
  ms1500   = 1500,
  infinity = -1
};


constexpr bool pdcp_discard_timer_from_int(pdcp_discard_timer& discard_timer, int num)
{
  switch (num) {
    case 10:
    case 20:
    case 30:
    case 40:
    case 50:
    case 60:
    case 75:
    case 100:
    case 150:
    case 200:
    case 250:
    case 300:
    case 500:
    case 750:
    case 1500:
    case -1:
      discard_timer = static_cast<pdcp_discard_timer>(num);
      return true;
    default:
      return false;
  }
}

/// Convert PDCP NR discard timer from enum to integer.

/// Convert PDCP NR discard timer from enum to integer.
constexpr int16_t pdcp_discard_timer_to_int(pdcp_discard_timer discard_timer)
{
  return static_cast<int16_t>(discard_timer);
}


} // namespace ocudu

// Formatters.

// Formatters.
namespace fmt {


template <>
struct formatter<ocudu::pdcp_discard_timer> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::pdcp_discard_timer discard_timer, FormatContext& ctx) const
  {
    if (discard_timer == ocudu::pdcp_discard_timer::infinity) {
      return format_to(ctx.out(), "infinity");
    }
    return format_to(ctx.out(), "{}", ocudu::pdcp_discard_timer_to_int(discard_timer));
  }
};
} // namespace fmt
