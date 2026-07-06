// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/ul_dci_request.h  (47 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/dl_pdcch_pdu.h"
#include "ocudu/ran/slot_pdu_capacity_constants.h"


namespace ocudu {
namespace fapi {

/// Uplink DCI PDU information.

/// Uplink DCI PDU information.
struct ul_dci_pdu {
  dl_pdcch_pdu pdu;
};

/// Uplink DCI request message.

/// Uplink DCI request message.
struct ul_dci_request {
  slot_point                                            slot;
  static_vector<ul_dci_pdu, MAX_UL_PDCCH_PDUS_PER_SLOT> pdus;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::ul_dci_request> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::ul_dci_request& msg, FormatContext& ctx) const
  {
    format_to(ctx.out(), "UL_DCI.request slot={}", msg.slot);


    for (const auto& pdu : msg.pdus) {
      format_to(ctx.out(), "{}", pdu.pdu);
    }


    return ctx.out();
  }
};
} // namespace fmt
