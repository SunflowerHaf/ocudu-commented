// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/dci_format.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <array>
#include <cstdint>


namespace ocudu {

/// Supported DL DCI formats.

/// Supported DL DCI formats.
enum class dci_dl_format : uint8_t { f1_0, f1_1, f2_0 };

/// Supported UL DCI formats.

/// Supported UL DCI formats.
enum class dci_ul_format : uint8_t { f0_0, f0_1 };


inline const char* dci_format_to_string(dci_dl_format type)
{
  static constexpr std::array<const char*, 4> names = {"1_0", "1_1", "2_0", "invalid"};
  unsigned                                    idx   = static_cast<unsigned>(type);
  return names[idx < names.size() ? idx : names.size() - 1];
}


inline const char* dci_format_to_string(dci_ul_format type)
{
  static constexpr std::array<const char*, 3> names = {"0_0", "0_1", "invalid"};
  unsigned                                    idx   = static_cast<unsigned>(type);
  return names[idx < names.size() ? idx : names.size() - 1];
}


} // namespace ocudu
