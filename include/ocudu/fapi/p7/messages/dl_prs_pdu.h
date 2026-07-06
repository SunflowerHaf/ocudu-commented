// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/dl_prs_pdu.h  (65 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/tx_precoding_and_beamforming_pdu.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/prs/prs.h"
#include "ocudu/ran/resource_allocation/rb_interval.h"
#include "ocudu/ran/subcarrier_spacing.h"
#include <optional>


namespace ocudu {
namespace fapi {

/// Downlink PRS PDU information.

/// Downlink PRS PDU information.
struct dl_prs_pdu {
  subcarrier_spacing               scs;
  cyclic_prefix                    cp;
  uint16_t                         nid_prs;
  prs_comb_size                    comb_size;
  uint8_t                          comb_offset;
  prs_num_symbols                  num_symbols;
  uint8_t                          first_symbol;
  crb_interval                     crbs;
  std::optional<float>             prs_power_offset_db;
  tx_precoding_and_beamforming_pdu precoding_and_beamforming;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::dl_prs_pdu> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::dl_prs_pdu& pdu, FormatContext& ctx) const
  {
    format_to(ctx.out(),
              "\n\t- PRS scs={} cp={} nid_prs={} comb_size={} comb_offset={} symb={}:{} CRBs={} Precoding and "
              "Beamforming prg_size={}",
              to_string(pdu.scs),
              pdu.cp.to_string(),
              pdu.nid_prs,
              underlying(pdu.comb_size),
              pdu.comb_offset,
              pdu.first_symbol,
              underlying(pdu.num_symbols),
              pdu.crbs,
              pdu.precoding_and_beamforming.prg_size);


    if (pdu.prs_power_offset_db.has_value()) {
      format_to(ctx.out(), " prs_power_offset_db={}", *pdu.prs_power_offset_db);
    }


    return ctx.out();
  }
};
} // namespace fmt
