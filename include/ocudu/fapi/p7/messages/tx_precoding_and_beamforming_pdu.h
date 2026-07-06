// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/tx_precoding_and_beamforming_pdu.h  (24 lines)
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

/// Precoding and beamforming PDU.

/// Precoding and beamforming PDU.
struct tx_precoding_and_beamforming_pdu {
  /// Physical resource groups information.
  /// Physical resource groups information.
  struct prgs_info {
    uint16_t pm_index;
  };


  uint16_t prg_size;
  /// [Implementation-defined] Only a single PRG is used.
  /// [Implementation-defined] Only a single PRG is used.
  prgs_info prg;
};


} // namespace fapi
} // namespace ocudu
