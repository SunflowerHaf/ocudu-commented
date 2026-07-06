// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/logical_channel/lcid.h  (43 lines)
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
#include <type_traits>


namespace ocudu {

/// Logical Channel Identity used to associate one logical channel to the corresponding RLC bearer. Values (0..32)

/// Logical Channel Identity used to associate one logical channel to the corresponding RLC bearer. Values (0..32)
enum lcid_t : uint16_t {
  LCID_SRB0        = 0,
  LCID_SRB1        = 1,
  LCID_SRB2        = 2,
  LCID_SRB3        = 3,
  LCID_MIN_DRB     = 4,
  LCID_MAX_DRB     = 32,
  MAX_NOF_RB_LCIDS = 33,
  INVALID_LCID     = 64
};


constexpr lcid_t uint_to_lcid(std::underlying_type_t<lcid_t> val)
{
  return static_cast<lcid_t>(val);
}

/// Maximum value of Logical Channel ID.
/// \remark See TS 38.331, maxLC-ID.

/// Maximum value of Logical Channel ID.
/// \remark See TS 38.331, maxLC-ID.
constexpr lcid_t MAX_LCID = LCID_MAX_DRB;


constexpr bool is_srb(lcid_t lcid)
{
  return lcid <= LCID_SRB3;
}


inline bool is_lcid_valid(lcid_t lcid)
{
  return lcid <= MAX_LCID;
}


} // namespace ocudu
