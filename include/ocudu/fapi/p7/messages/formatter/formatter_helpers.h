// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/formatter/formatter_helpers.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/phy_time_unit.h"
#include <optional>


namespace ocudu {
namespace fapi {

/// Appends the timing advance value to the given buffer if there is a timing advance.

/// Appends the timing advance value to the given buffer if there is a timing advance.
template <typename FormatContext>
inline auto append_time_advance(FormatContext& ctx, std::optional<phy_time_unit> timing_advance, subcarrier_spacing scs)
{
  if (!timing_advance) {
    return ctx.out();
  }


  return format_to(ctx.out(), " ta={} ({:.1f}ns)", timing_advance->to_Ta(scs), timing_advance->to_seconds() * 1e9);
}


} // namespace fapi
} // namespace ocudu
