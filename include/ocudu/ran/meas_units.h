// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/meas_units.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>


namespace ocudu {

/// RSRP value range in dBm used in RSRP measurements and thresholds, as specified in TS 38.331, "RSRP Range" and in
/// TS 38.133, Table 10.1.6.1-1.
/// For measurements, the value -156 means "<-156", the value -155 means between [-156, -155), and so on, until -30
/// which means >=-31. Value -29 is not used for measurements.
/// For RSRP thresholds, the value -29 represents infinity.

/// RSRP value range in dBm used in RSRP measurements and thresholds, as specified in TS 38.331, "RSRP Range" and in
/// TS 38.133, Table 10.1.6.1-1.
/// For measurements, the value -156 means "<-156", the value -155 means between [-156, -155), and so on, until -30
/// which means >=-31. Value -29 is not used for measurements.
/// For RSRP thresholds, the value -29 represents infinity.
struct rsrp_range {
  rsrp_range() = default;
  explicit rsrp_range(int dBm) : val(dBm + 156) { ocudu_assert(dBm >= -156 and dBm <= -29, "Invalid RSRP dBm value"); }

  /// RSRP in dBm, ranging between [-156, -29].

  /// RSRP in dBm, ranging between [-156, -29].
  int16_t dBm() const { return static_cast<int16_t>(val) - 156; }

  /// Representation of RSRP with an index ranging between [0, 29] for the Table 10.1.6.1-1, TS 38.133.

  /// Representation of RSRP with an index ranging between [0, 29] for the Table 10.1.6.1-1, TS 38.133.
  uint8_t count() const { return val; }

  /// Infinity RSRP value.

  /// Infinity RSRP value.
  static rsrp_range infinity() { return rsrp_range{-29}; }


  static rsrp_range min() { return rsrp_range{-156}; }
  static rsrp_range max() { return rsrp_range{-28}; }


  bool operator==(const rsrp_range& other) const { return val == other.val; }
  bool operator!=(const rsrp_range& other) const { return val != other.val; }
  bool operator<(const rsrp_range& other) const { return val < other.val; }
  bool operator>(const rsrp_range& other) const { return val > other.val; }
  bool operator<=(const rsrp_range& other) const { return val <= other.val; }
  bool operator>=(const rsrp_range& other) const { return val >= other.val; }


private:
  uint8_t val{0};
};


} // namespace ocudu
