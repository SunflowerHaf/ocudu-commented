// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/uci_pucch_pdu_format_0_1.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/phy_time_unit.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/uci/uci_mapping.h"
#include <optional>


namespace ocudu {
namespace fapi {

/// SR PDU for format 0 or 1.

/// SR PDU for format 0 or 1.
struct sr_pdu_format_0_1 {
  bool sr_detected;
};

/// UCI HARQ PDU for format 0 or 1.

/// UCI HARQ PDU for format 0 or 1.
struct uci_harq_format_0_1 {
  /// Maximum number of HARQs.
  /// Maximum number of HARQs.
  static constexpr unsigned MAX_NUM_HARQ = 2U;


  static_vector<uci_pucch_f0_or_f1_harq_values, MAX_NUM_HARQ> harq_values;
};

/// UCI PUCCH for format 0 or 1.

/// UCI PUCCH for format 0 or 1.
struct uci_pucch_pdu_format_0_1 {
  enum class format_type : uint8_t { format_0, format_1 };


  uint32_t                           handle = 0U;
  rnti_t                             rnti;
  format_type                        pucch_format;
  int16_t                            ul_sinr_metric;
  std::optional<phy_time_unit>       timing_advance_offset;
  uint16_t                           rssi;
  uint16_t                           rsrp;
  std::optional<sr_pdu_format_0_1>   sr;
  std::optional<uci_harq_format_0_1> harq;
};


} // namespace fapi
} // namespace ocudu
