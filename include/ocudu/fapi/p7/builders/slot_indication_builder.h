// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/builders/slot_indication_builder.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/fapi/p7/messages/slot_indication.h"
#include "ocudu/ran/slot_point_extended.h"


namespace ocudu {
namespace fapi {

/// Builds and returns a slot.indication message with the given parameters, as per SCF-222 v4.0 section 3.4.1 in table
/// Slot indication message body.

/// Builds and returns a slot.indication message with the given parameters, as per SCF-222 v4.0 section 3.4.1 in table
/// Slot indication message body.
inline slot_indication build_slot_indication(slot_point_extended                                slot,
                                             std::chrono::time_point<std::chrono::system_clock> time_point)
{
  slot_indication msg;


  msg.slot       = slot;
  msg.time_point = time_point;


  return msg;
}


} // namespace fapi
} // namespace ocudu
