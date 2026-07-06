// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/dl_csi_rs_pdu.h  (89 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/power_control_offset_ss.h"
#include "ocudu/ran/csi_rs/csi_rs_types.h"
#include "ocudu/ran/csi_rs/frequency_allocation_type.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/resource_allocation/rb_interval.h"
#include "ocudu/ran/subcarrier_spacing.h"
#include <variant>


namespace ocudu {
namespace fapi {

/// Downlink CSI-RS PDU information.

/// Downlink CSI-RS PDU information.
struct dl_csi_rs_pdu {
  /// Profile NR power parameters.
  /// Profile NR power parameters.
  struct power_profile_nr {
    int                     pwr_control_offset_db;
    power_control_offset_ss pwr_control_offset_ss;
  };

  /// Profile SSS power parameters.

  /// Profile SSS power parameters.
  struct power_profile_sss {
    float pwr_offset_db;
  };


  subcarrier_spacing                                scs;
  cyclic_prefix                                     cp;
  crb_interval                                      crbs;
  csi_rs_type                                       type;
  uint8_t                                           row;
  csi_rs::freq_allocation_mask_type                 freq_domain;
  uint8_t                                           symb_L0;
  uint8_t                                           symb_L1;
  csi_rs_cdm_type                                   cdm_type;
  csi_rs_freq_density_type                          freq_density;
  uint16_t                                          scramb_id;
  std::variant<power_profile_nr, power_profile_sss> power_config;
  crb_interval                                      bwp;
};


} // namespace fapi
} // namespace ocudu


namespace fmt {
template <>
struct formatter<ocudu::fapi::dl_csi_rs_pdu> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::fapi::dl_csi_rs_pdu& pdu, FormatContext& ctx) const
  {
    format_to(ctx.out(),
              "\n\t- CSI-RS type={} scs={} cp={} crbs={} row={} freq_domain={} symbL0={} symbL1={} cdm_type={} "
              "freq_density={} scramb_id={} bwp={}",
              to_string(pdu.type),
              to_string(pdu.scs),
              pdu.cp.to_string(),
              pdu.crbs,
              pdu.row,
              pdu.freq_domain,
              pdu.symb_L0,
              pdu.symb_L1,
              to_string(pdu.cdm_type),
              to_string(pdu.freq_density),
              pdu.bwp,
              pdu.scramb_id);


    if (const auto* profile_nr = std::get_if<ocudu::fapi::dl_csi_rs_pdu::power_profile_nr>(&pdu.power_config)) {
      format_to(ctx.out(),
                " Power configuration profile NR: power_control_offset_db={} power_control_offset_ss{}",
                profile_nr->pwr_control_offset_db,
                underlying(profile_nr->pwr_control_offset_ss));
    } else if (const auto* profile_sss =
                   std::get_if<ocudu::fapi::dl_csi_rs_pdu::power_profile_sss>(&pdu.power_config)) {
      format_to(ctx.out(), " Power configuration profile SSS: power_offset_db={}", profile_sss->pwr_offset_db);
    }


    return ctx.out();
  }
};
} // namespace fmt
