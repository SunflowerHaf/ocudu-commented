// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/uci_pusch_pdu.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/uci_pdu_definitions.h"
#include "ocudu/ran/phy_time_unit.h"


namespace ocudu {
namespace fapi {

/// PUSCH UCI PDU information.

/// PUSCH UCI PDU information.
struct uci_pusch_pdu {
  uint32_t                     handle = 0U;
  rnti_t                       rnti;
  int16_t                      ul_sinr_metric;
  std::optional<phy_time_unit> timing_advance_offset;
  uint16_t                     rssi;
  uint16_t                     rsrp;
  std::optional<uci_harq_pdu>  harq;
  std::optional<uci_csi_part1> csi_part1;
  std::optional<uci_csi_part2> csi_part2;
};


} // namespace fapi
} // namespace ocudu
