// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/crc_indication.h  (81 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "formatter/formatter_helpers.h"
#include "ocudu/ran/harq_id.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/slot_point.h"
#include <optional>


namespace ocudu {
namespace fapi {

/// Reception data indication PDU information.

/// Reception data indication PDU information.
struct crc_ind_pdu {
  uint32_t                     handle = 0;
  rnti_t                       rnti;
  harq_id_t                    harq_id;
  bool                         tb_crc_status_ok;
  int16_t                      ul_sinr_metric;
  std::optional<phy_time_unit> timing_advance_offset;
  uint16_t                     rssi;
  uint16_t                     rsrp;
};

/// CRC indication message.

/// CRC indication message.
struct crc_indication {
  slot_point  slot;
  crc_ind_pdu pdu;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::crc_indication> {
private:
  /// Converts the given FAPI CRC SINR to dB as per SCF-222 v4.0 section 3.4.8.
  /// Converts the given FAPI CRC SINR to dB as per SCF-222 v4.0 section 3.4.8.
  static float to_crc_ul_sinr(int sinr) { return static_cast<float>(sinr) * 0.002F; }

  /// Converts the given FAPI CRC RSSI to dB as per SCF-222 v4.0 section 3.4.8.

  /// Converts the given FAPI CRC RSSI to dB as per SCF-222 v4.0 section 3.4.8.
  static float to_crc_ul_rssi(unsigned rssi) { return static_cast<float>(static_cast<int>(rssi) - 1280) * 0.1F; }

  /// Converts the given FAPI CRC RSRP to dB as per SCF-222 v4.0 section 3.4.8.

  /// Converts the given FAPI CRC RSRP to dB as per SCF-222 v4.0 section 3.4.8.
  static float to_crc_ul_rsrp(unsigned rsrp) { return static_cast<float>(static_cast<int>(rsrp) - 1280) * 0.1F; }


public:
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::crc_indication& msg, FormatContext& ctx) const
  {
    format_to(ctx.out(),
              "CRC.indication slot={} rnti={} harq_id={} tb_status={}",
              msg.slot,
              msg.pdu.rnti,
              underlying(msg.pdu.harq_id),
              msg.pdu.tb_crc_status_ok ? "OK" : "KO");


    ocudu::fapi::append_time_advance(ctx, msg.pdu.timing_advance_offset, msg.slot.scs());


    if (msg.pdu.ul_sinr_metric != std::numeric_limits<decltype(msg.pdu.ul_sinr_metric)>::min()) {
      format_to(ctx.out(), " sinr={:.1f}", to_crc_ul_sinr(msg.pdu.ul_sinr_metric));
    }
    if (msg.pdu.rssi != std::numeric_limits<decltype(msg.pdu.rssi)>::max()) {
      format_to(ctx.out(), " rssi={:.1f}", to_crc_ul_rssi(msg.pdu.rssi));
    }
    if (msg.pdu.rsrp != std::numeric_limits<decltype(msg.pdu.rsrp)>::max()) {
      format_to(ctx.out(), " rsrp={:.1f}", to_crc_ul_rsrp(msg.pdu.rsrp));
    }


    return ctx.out();
  }
};
} // namespace fmt
