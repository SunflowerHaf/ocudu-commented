// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/ul_tti_request.h  (71 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/ul_prach_pdu.h"
#include "ocudu/fapi/p7/messages/ul_pucch_pdu.h"
#include "ocudu/fapi/p7/messages/ul_pusch_pdu.h"
#include "ocudu/fapi/p7/messages/ul_srs_pdu.h"
#include "ocudu/ran/slot_pdu_capacity_constants.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace fapi {

/// Common uplink PDU information.

/// Common uplink PDU information.
struct ul_tti_request_pdu {
  std::variant<ul_prach_pdu, ul_pusch_pdu, ul_pucch_pdu, ul_srs_pdu> pdu;
};

/// Uplink TTI request message.

/// Uplink TTI request message.
struct ul_tti_request {
  slot_point                                              slot;
  static_vector<ul_tti_request_pdu, MAX_UL_PDUS_PER_SLOT> pdus;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::ul_tti_request> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::ul_tti_request& msg, FormatContext& ctx) const
  {
    format_to(ctx.out(), "UL_TTI.request slot={}", msg.slot);


    for (const auto& pdu : msg.pdus) {
      if (const auto* prach_pdu = std::get_if<ocudu::fapi::ul_prach_pdu>(&pdu.pdu)) {
        format_to(ctx.out(), "{}", *prach_pdu);
        continue;
      }


      if (const auto* pucch_pdu = std::get_if<ocudu::fapi::ul_pucch_pdu>(&pdu.pdu)) {
        format_to(ctx.out(), "{}", *pucch_pdu);
        continue;
      }


      if (const auto* pusch_pdu = std::get_if<ocudu::fapi::ul_pusch_pdu>(&pdu.pdu)) {
        format_to(ctx.out(), "{}", *pusch_pdu);
        continue;
      }


      if (const auto* srs_pdu = std::get_if<ocudu::fapi::ul_srs_pdu>(&pdu.pdu)) {
        format_to(ctx.out(), "{}", *srs_pdu);
        continue;
      }


      ocudu_assert(0, "UL_TTI.request PDU type value not recognized.");
    }


    return ctx.out();
  }
};
} // namespace fmt
