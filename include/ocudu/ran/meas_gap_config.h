// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/meas_gap_config.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/slot_point.h"
#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {

/// Measurement Gap Repetition Period (MGRP) in msec, as per TS 38.331.

/// Measurement Gap Repetition Period (MGRP) in msec, as per TS 38.331.
enum class meas_gap_repetition_period : uint8_t { ms20 = 20, ms40 = 40, ms80 = 80, ms160 = 160 };

/// Measurement Gap Length (MGL) in msec, as per TS 38.331.

/// Measurement Gap Length (MGL) in msec, as per TS 38.331.
enum class meas_gap_length : uint8_t { ms1dot5, ms3, ms3dot5, ms4, ms5dot5, ms6 };

/// Configuration of a Measurement Gap as per TS 38.331, GapConfig.

/// Configuration of a Measurement Gap as per TS 38.331, GapConfig.
struct meas_gap_config {
  /// Gap offset of the pattern in msec. Value must be between 0 and gap repetition period - 1.
  /// Gap offset of the pattern in msec. Value must be between 0 and gap repetition period - 1.
  unsigned offset;
  /// Measurement Gap Length (MGL).
  /// Measurement Gap Length (MGL).
  meas_gap_length mgl;
  /// Measurement Gap Repetition Period (MGRP).
  /// Measurement Gap Repetition Period (MGRP).
  meas_gap_repetition_period mgrp;


  bool operator==(const meas_gap_config& other) const
  {
    return offset == other.offset && mgl == other.mgl && mgrp == other.mgrp;
  }
  bool operator!=(const meas_gap_config& other) const { return !(*this == other); }
};

/// Convert measurement gap length into a float in milliseconds.

/// Convert measurement gap length into a float in milliseconds.
inline float meas_gap_length_to_msec(meas_gap_length len)
{
  static constexpr std::array<float, 6> vals{1.5, 3, 3.5, 4, 5.5, 6};
  return vals[static_cast<unsigned>(len)];
}

/// Determines whether a slot is inside the measurement gap.

/// Determines whether a slot is inside the measurement gap.
inline bool is_inside_meas_gap(const meas_gap_config& gap, slot_point sl)
{
  const unsigned slot_per_sf  = sl.nof_slots_per_subframe();
  unsigned       period_slots = static_cast<uint8_t>(gap.mgrp) * slot_per_sf;
  unsigned       length_slots = std::ceil(meas_gap_length_to_msec(gap.mgl) * slot_per_sf);
  unsigned       slot_mod     = (sl - gap.offset * slot_per_sf).to_uint() % period_slots;
  return slot_mod <= length_slots;
}


} // namespace ocudu
