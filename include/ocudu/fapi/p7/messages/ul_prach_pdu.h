// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/ul_prach_pdu.h  (52 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/interval.h"
#include "ocudu/ran/prach/prach_format_type.h"


namespace ocudu {
namespace fapi {

/// Uplink PRACH PDU information.

/// Uplink PRACH PDU information.
struct ul_prach_pdu {
  using preambles_interval = interval<uint8_t, false>;


  uint8_t            num_prach_ocas;
  prach_format_type  prach_format;
  uint8_t            index_fd_ra;
  uint8_t            prach_start_symbol;
  uint16_t           num_cs;
  uint32_t           handle = 0U;
  uint8_t            num_fd_ra;
  preambles_interval preambles;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::ul_prach_pdu> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::ul_prach_pdu& pdu, FormatContext& ctx) const
  {
    return format_to(ctx.out(),
                     "\n\t- PRACH num_prach_ocas={} format={} fd_ra={}:{} symb={} z_corr={} preambles={}",
                     pdu.num_prach_ocas,
                     to_string(pdu.prach_format),
                     pdu.index_fd_ra,
                     pdu.num_fd_ra,
                     pdu.prach_start_symbol,
                     pdu.num_cs,
                     pdu.preambles);
  }
};
} // namespace fmt
