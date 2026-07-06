// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/time_alignment_config.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/strong_type.h"
#include <chrono>
#include <type_traits>


namespace ocudu {

/// \c maxNrofTAGs, TS 38.331.

/// \c maxNrofTAGs, TS 38.331.
const unsigned MAX_NOF_TIME_ALIGNMENT_GROUPS = 4;

/// \c TimeAlignmentTimer, TS 38.331.

/// \c TimeAlignmentTimer, TS 38.331.
enum class time_alignment_timer {
  ms500    = 500,
  ms750    = 750,
  ms1280   = 1280,
  ms1920   = 1920,
  ms2560   = 2560,
  ms5120   = 5120,
  ms10240  = 10240,
  infinity = 0
};

/// Return the value of \ref time_alignment_timer.

/// Return the value of \ref time_alignment_timer.
inline std::chrono::milliseconds time_alignment_timer_to_msec(time_alignment_timer timer)
{
  return std::chrono::milliseconds{static_cast<std::underlying_type_t<time_alignment_timer>>(timer)};
}

/// Time Alignment Group (TAG), as per TS 38.331.

/// Time Alignment Group (TAG), as per TS 38.331.
struct time_alignment_group {
  using id_t = strong_type<uint8_t, time_alignment_group, strong_equality>;


  id_t                 tag_id;
  time_alignment_timer ta_timer;


  bool operator==(const time_alignment_group& rhs) const { return tag_id == rhs.tag_id && ta_timer == rhs.ta_timer; }
  bool operator!=(const time_alignment_group& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
