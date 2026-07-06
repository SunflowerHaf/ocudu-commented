// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/dl_ssb_pdu.h  (75 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/pci.h"
#include "ocudu/ran/ssb/ssb_configuration.h"
#include <variant>


namespace ocudu {
namespace fapi {

/// Downlink SSB PDU information.

/// Downlink SSB PDU information.
struct dl_ssb_pdu {
  /// Profile NR power parameters.
  /// Profile NR power parameters.
  struct power_profile_nr {
    ssb_pss_to_sss_epre beta_pss;
  };

  /// Profile SSS power parameters.

  /// Profile SSS power parameters.
  struct power_profile_sss {
    float beta_pss_db;
  };


  pci_t                                             phys_cell_id;
  std::variant<power_profile_nr, power_profile_sss> power_config;
  ssb_id_t                                          ssb_block_index;
  ssb_subcarrier_offset                             subcarrier_offset;
  ssb_offset_to_pointA                              ssb_offset_pointA;
  /// \note Payload encoded as: 0,0,0,0,0,0,0,0,a0,a1,a2,...,a21,a22,a23, with the most significant bit being the
  /// leftmost (in this case a0 in position 24 of the uint32_t).
  /// \note The timing bits should be added by the underlying PHY.
  /// \note Payload encoded as: 0,0,0,0,0,0,0,0,a0,a1,a2,...,a21,a22,a23, with the most significant bit being the
  /// leftmost (in this case a0 in position 24 of the uint32_t).
  /// \note The timing bits should be added by the underlying PHY.
  uint32_t           bch_payload;
  ssb_pattern_case   case_type;
  subcarrier_spacing scs;
  uint8_t            L_max;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::dl_ssb_pdu> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::dl_ssb_pdu& pdu, FormatContext& ctx) const
  {
    format_to(ctx.out(),
              "\n\t- SSB pci={} ssb_block_index={} k_SSB={} pointA={} bch_payload={}"
              "ssb_pattern_case={} scs={} L_max={}",
              pdu.phys_cell_id,
              pdu.ssb_block_index,
              pdu.subcarrier_offset.value(),
              pdu.ssb_offset_pointA.value(),
              pdu.bch_payload,
              to_string(pdu.case_type),
              to_string(pdu.scs),
              pdu.L_max);


    if (const auto* profile_nr = std::get_if<ocudu::fapi::dl_ssb_pdu::power_profile_nr>(&pdu.power_config)) {
      format_to(ctx.out(), " Power configuration profile NR: beta_pss={}", underlying(profile_nr->beta_pss));
    } else if (const auto* profile_sss = std::get_if<ocudu::fapi::dl_ssb_pdu::power_profile_sss>(&pdu.power_config)) {
      format_to(ctx.out(), " Power configuration profile SSS: beta_pss_db={}", profile_sss->beta_pss_db);
    }


    return ctx.out();
  }
};
} // namespace fmt
