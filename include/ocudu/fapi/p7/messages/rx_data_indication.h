// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/rx_data_indication.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/ran/harq_id.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace fapi {

/// Reception data indication PDU information.

/// Reception data indication PDU information.
struct rx_data_indication_pdu {
  uint32_t            handle = 0;
  rnti_t              rnti;
  harq_id_t           harq_id;
  span<const uint8_t> transport_block;
};

/// Reception data indication message.

/// Reception data indication message.
struct rx_data_indication {
  slot_point             slot;
  rx_data_indication_pdu pdu;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::rx_data_indication> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::rx_data_indication& msg, FormatContext& ctx) const
  {
    return format_to(ctx.out(),
                     "Rx_Data.indication slot={} rnti={} harq_id={} tbs={}",
                     msg.slot,
                     msg.pdu.rnti,
                     underlying(msg.pdu.harq_id),
                     msg.pdu.transport_block.size());
  }
};
} // namespace fmt
