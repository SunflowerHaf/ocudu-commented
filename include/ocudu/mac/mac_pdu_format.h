// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/mac/mac_pdu_format.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/mac
// MAC interface headers: the mac_cell_slot_handler (receives slot indications from the lower PHY), mac_ue_radio_bearer_config (per-UE logical channel configuration), mac_pdu_handler (delivers received MAC PDUs), mac_paging_information_handler, mac_rach_handler, and the MAC clock controller interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/logical_channel/lcid_dl_sch.h"


namespace ocudu {


constexpr unsigned FIXED_SIZED_MAC_CE_SUBHEADER_SIZE = 1;
constexpr unsigned MAC_SDU_SUBHEADER_LENGTH_THRES    = 256;
constexpr unsigned MIN_MAC_SDU_SUBHEADER_SIZE        = 2;
constexpr unsigned MAX_MAC_SDU_SUBHEADER_SIZE        = 3;

/// \brief Derive MAC SDU subheader size in bytes as per TS38.321, Section 6.1.

/// \brief Derive MAC SDU subheader size in bytes as per TS38.321, Section 6.1.
constexpr unsigned get_mac_sdu_subheader_size(unsigned payload)
{
  return payload == 0                                ? 0
         : payload >= MAC_SDU_SUBHEADER_LENGTH_THRES ? MAX_MAC_SDU_SUBHEADER_SIZE
                                                     : MIN_MAC_SDU_SUBHEADER_SIZE;
}

/// \brief Derive MAC SDU total size in bytes (includes subheader).

/// \brief Derive MAC SDU total size in bytes (includes subheader).
constexpr unsigned get_mac_sdu_required_bytes(unsigned payload)
{
  return payload + get_mac_sdu_subheader_size(payload);
}

/// \brief Derive MAC SDU payload size in bytes (without subheader) from the MAC SDU+subheader size.

/// \brief Derive MAC SDU payload size in bytes (without subheader) from the MAC SDU+subheader size.
constexpr unsigned get_mac_sdu_payload_size(unsigned mac_sdu_size)
{
  // Note: len(sdu)+len(subheader)==258 is impossible. If mac_sdu_size==258, we err on the side of lower payload and
  // return 255.
  // Note: len(sdu)+len(subheader)==258 is impossible. If mac_sdu_size==258, we err on the side of lower payload and
  // return 255.
  if (mac_sdu_size <= MAC_SDU_SUBHEADER_LENGTH_THRES + MIN_MAC_SDU_SUBHEADER_SIZE - 1) {
    return mac_sdu_size - MIN_MAC_SDU_SUBHEADER_SIZE;
  }
  return mac_sdu_size - MAX_MAC_SDU_SUBHEADER_SIZE;
}


} // namespace ocudu
