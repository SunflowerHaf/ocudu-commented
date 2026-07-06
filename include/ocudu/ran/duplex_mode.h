// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/duplex_mode.h  (30 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <algorithm>


namespace ocudu {

/// NR Duplex mode.

/// NR Duplex mode.
enum class duplex_mode {
  /// Paired FDD.
  /// Paired FDD.
  FDD = 0,
  /// Unpaired TDD.
  /// Unpaired TDD.
  TDD,
  /// Supplementary DownLink (Unpaired).
  /// Supplementary DownLink (Unpaired).
  SDL,
  /// Supplementary UpLink (Unpaired).
  /// Supplementary UpLink (Unpaired).
  SUL,
  INVALID
};


inline const char* to_string(duplex_mode mode)
{
  static constexpr const char* names[] = {"FDD", "TDD", "SDL", "SUL", "invalid"};
  return names[std::min((unsigned)mode, (unsigned)duplex_mode::INVALID)];
}


} // namespace ocudu
