// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/common/error_code.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <cstdint>


namespace ocudu {
namespace fapi {

/// Encodes the error codes.

/// Encodes the error codes.
enum class error_code_id : uint8_t {
  msg_ok                               = 0x0,
  msg_invalid_state                    = 0x1,
  msg_invalid_config                   = 0x2,
  out_of_sync                          = 0x3,
  msg_slot_err                         = 0x4,
  msg_bch_missing                      = 0x5,
  msg_invalid_sfn                      = 0x6,
  msg_ul_dci_err                       = 0x7,
  msg_tx_err                           = 0x8,
  msg_invalid_phy_id                   = 0x9,
  msg_uninstantiated_phy               = 0xa,
  msg_invalid_dfe_profile              = 0xb,
  phy_profile_incompatible_running_phy = 0xc
};


} // namespace fapi
} // namespace ocudu
