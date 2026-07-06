// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/srs_indication.h  (72 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "formatter/formatter_helpers.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/slot_point.h"
#include "ocudu/ran/srs/srs_channel_matrix.h"
#include <optional>


namespace ocudu {
namespace fapi {

/// Encodes SRS positioning report.

/// Encodes SRS positioning report.
struct srs_positioning_report {
  /// TUL-RTOA as defined in TS 38.215 on section 5.1.
  /// TUL-RTOA as defined in TS 38.215 on section 5.1.
  std::optional<phy_time_unit> ul_relative_toa;
  std::optional<float>         rsrp;
};

/// SRS indication pdu.

/// SRS indication pdu.
struct srs_indication_pdu {
  uint32_t                              handle = 0;
  rnti_t                                rnti;
  std::optional<phy_time_unit>          timing_advance_offset;
  std::optional<srs_channel_matrix>     matrix;
  std::optional<srs_positioning_report> positioning;
};

/// SRS indication message.

/// SRS indication message.
struct srs_indication {
  slot_point         slot;
  srs_indication_pdu pdu;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::srs_indication> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::srs_indication& msg, FormatContext& ctx) const
  {
    format_to(ctx.out(), "SRS.indication slot={} rnti={}", msg.slot, msg.pdu.rnti);


    ocudu::fapi::append_time_advance(ctx, msg.pdu.timing_advance_offset, msg.slot.scs());


    if (msg.pdu.positioning.has_value()) {
      if (msg.pdu.positioning->ul_relative_toa) {
        format_to(ctx.out(), " RTOA_s={}", *msg.pdu.positioning->rsrp);
      }
      if (msg.pdu.positioning->rsrp) {
        format_to(ctx.out(), " RSRP={}", *msg.pdu.positioning->rsrp);
      }
    }


    if (msg.pdu.matrix.has_value()) {
      format_to(ctx.out(), " With channel matrix");
    }


    return ctx.out();
  }
};
} // namespace fmt
