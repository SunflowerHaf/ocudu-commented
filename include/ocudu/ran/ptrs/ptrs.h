// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/ptrs/ptrs.h  (80 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_integer.h"


namespace ocudu {

/// Phase Tracking Reference Signals (PT-RS) frequency domain density.

/// Phase Tracking Reference Signals (PT-RS) frequency domain density.
enum class ptrs_frequency_density : uint8_t { two = 2, four = 4 };

/// Converts PT-RS frequency domain density to a string.

/// Converts PT-RS frequency domain density to a string.
inline const char* to_string(ptrs_frequency_density freq_density)
{
  switch (freq_density) {
    case ptrs_frequency_density::two:
      return "two";
    case ptrs_frequency_density::four:
      return "four";
  }
  return "invalid";
}

/// Converts PT-RS frequency domain density to an integer.

/// Converts PT-RS frequency domain density to an integer.
inline unsigned to_value(ptrs_frequency_density freq_density)
{
  return static_cast<unsigned>(freq_density);
}

/// Phase Tracking Reference Signals (PT-RS) time domain density.

/// Phase Tracking Reference Signals (PT-RS) time domain density.
enum class ptrs_time_density : uint8_t { one = 1, two = 2, four = 4 };

/// Converts PT-RS time domain density to a string.

/// Converts PT-RS time domain density to a string.
inline const char* to_string(ptrs_time_density time_density)
{
  switch (time_density) {
    case ptrs_time_density::one:
      return "one";
    case ptrs_time_density::two:
      return "two";
    case ptrs_time_density::four:
      return "four";
  }
  return "invalid";
}

/// Converts PT-RS time domain density to an integer.

/// Converts PT-RS time domain density to an integer.
inline unsigned to_value(ptrs_time_density time_density)
{
  return static_cast<unsigned>(time_density);
}

/// Phase Tracking Reference Signals (PT-RS) RE offset.

/// Phase Tracking Reference Signals (PT-RS) RE offset.
enum class ptrs_re_offset : uint8_t { offset00 = 0, offset01 = 1, offset10 = 2, offset11 = 3 };

/// Converts PT-RS RE offset to a string.

/// Converts PT-RS RE offset to a string.
inline const char* to_string(ptrs_re_offset re_offset)
{
  switch (re_offset) {
    case ptrs_re_offset::offset00:
      return "offset00";
    case ptrs_re_offset::offset01:
      return "offset01";
    case ptrs_re_offset::offset10:
      return "offset10";
    case ptrs_re_offset::offset11:
      return "offset11";
  }
  return "invalid";
}

/// Converts PT-RS RE offset to an integer.

/// Converts PT-RS RE offset to an integer.
inline unsigned to_value(ptrs_re_offset re_offset)
{
  return static_cast<unsigned>(re_offset);
}


} // namespace ocudu
