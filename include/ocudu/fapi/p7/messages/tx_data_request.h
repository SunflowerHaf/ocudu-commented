// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/tx_data_request.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/slot_pdu_capacity_constants.h"
#include "ocudu/ran/slot_point.h"
#include "ocudu/support/shared_transport_block.h"


namespace ocudu {
namespace fapi {

/// Transmission data request PDU information.

/// Transmission data request PDU information.
struct tx_data_req_pdu {
  tx_data_req_pdu() = default;


  tx_data_req_pdu(uint16_t pdu_index_, uint8_t cw_index_, shared_transport_block pdu_) :
    pdu_index(pdu_index_), cw_index(cw_index_), pdu(std::move(pdu_))
  {
  }


  uint16_t               pdu_index;
  uint8_t                cw_index;
  shared_transport_block pdu;
};

/// Transmission request message.

/// Transmission request message.
struct tx_data_request {
  slot_point                                              slot;
  static_vector<tx_data_req_pdu, MAX_PDSCH_PDUS_PER_SLOT> pdus;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::tx_data_request> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::tx_data_request& msg, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "Tx_Data.request slot={} nof_pdus={}", msg.slot, msg.pdus.size());
  }
};
} // namespace fmt
