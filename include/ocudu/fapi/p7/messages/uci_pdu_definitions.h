// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/uci_pdu_definitions.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/uci/uci_payload_type.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace fapi {

/// UCI CSI Part 1 information.

/// UCI CSI Part 1 information.
struct uci_csi_part1 {
  uci_pusch_or_pucch_f2_3_4_detection_status detection_status;
  units::bits                                expected_bit_length;
  uci_payload_type                           payload;
};

/// UCI CSI Part 2 information.

/// UCI CSI Part 2 information.
struct uci_csi_part2 {
  uci_pusch_or_pucch_f2_3_4_detection_status detection_status;
  units::bits                                expected_bit_length;
  uci_payload_type                           payload;
};

/// UCI HARQ PDU information.

/// UCI HARQ PDU information.
struct uci_harq_pdu {
  uci_pusch_or_pucch_f2_3_4_detection_status detection_status;
  units::bits                                expected_bit_length;
  uci_payload_type                           payload;
};


} // namespace fapi
} // namespace ocudu
