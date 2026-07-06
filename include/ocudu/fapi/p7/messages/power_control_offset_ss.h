// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/fapi/p7/messages/power_control_offset_ss.h  (52 lines)
//
// INTERFACE HEADER — include/ocudu/fapi
// FAPI (Functional API) interface headers: the MAC-facing side of the FAPI. Contains the full FAPI P5 (cell configuration) and P7 (per-slot scheduling) message types: DL_TTI.req, UL_TTI.req, TX_Data.req, RX_Data.ind, CRC.ind, UCI.ind, SRS.ind, and all the nested IE types. These structs cross the MAC↔PHY boundary every millisecond.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/ocudu_assert.h"
#include <cstdint>


namespace ocudu {
namespace fapi {

/// Power control offset SS defined as 'ratio of NZP CSI-RS EPRE to SSB/PBCH block EPRE' as per SCF-222 v4.0
/// section 2.2.4.5.

/// Power control offset SS defined as 'ratio of NZP CSI-RS EPRE to SSB/PBCH block EPRE' as per SCF-222 v4.0
/// section 2.2.4.5.
enum class power_control_offset_ss : uint8_t { dB_minus_3, dB0, dB3, dB6 };

/// Converts the given value to a power control offset SS value.

/// Converts the given value to a power control offset SS value.
inline power_control_offset_ss to_power_control_offset_ss(int value)
{
  switch (value) {
    case -3:
      return power_control_offset_ss::dB_minus_3;
    case 0:
      return power_control_offset_ss::dB0;
    case 3:
      return power_control_offset_ss::dB3;
    case 6:
      return power_control_offset_ss::dB6;
    default:
      ocudu_assert(0, "Invalid power control offset SS '{}'", value);
      break;
  }
  return power_control_offset_ss::dB0;
}

/// Converts power control offset SS value to an integer.

/// Converts power control offset SS value to an integer.
inline int to_int(power_control_offset_ss value)
{
  switch (value) {
    case power_control_offset_ss::dB_minus_3:
      return -3;
    case power_control_offset_ss::dB0:
      return 0;
    case power_control_offset_ss::dB3:
      return 3;
    case power_control_offset_ss::dB6:
      break;
  }
  return 6;
}


} // namespace fapi
} // namespace ocudu
