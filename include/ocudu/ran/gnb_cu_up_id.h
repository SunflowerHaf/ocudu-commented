// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/gnb_cu_up_id.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "fmt/format.h"
#include <cstdint>


namespace ocudu {

/// \brief Global NodeB CU UP ID used to uniquely identify the gNB-CU-UP at least within a gNB-CU-CP.
/// \remark See TS 38.463 Section 9.3.1.15: GNB-CU-UP-ID valid values: (0..2^36-1).

/// \brief Global NodeB CU UP ID used to uniquely identify the gNB-CU-UP at least within a gNB-CU-CP.
/// \remark See TS 38.463 Section 9.3.1.15: GNB-CU-UP-ID valid values: (0..2^36-1).
enum class gnb_cu_up_id_t : uint64_t { min = 0, max = 68719476735, invalid = max + 1 };

/// Converts an integer to a GNB-CU-UP-ID type.

/// Converts an integer to a GNB-CU-UP-ID type.
constexpr gnb_cu_up_id_t uint_to_gnb_cu_up_id(uint64_t id)
{
  return static_cast<gnb_cu_up_id_t>(id);
}

/// Converts a GNB-CU-UP-ID to an integer.

/// Converts a GNB-CU-UP-ID to an integer.
constexpr uint64_t gnb_cu_up_id_to_uint(gnb_cu_up_id_t gnb_cu_up_id)
{
  return static_cast<uint64_t>(gnb_cu_up_id);
}


} // namespace ocudu


namespace fmt {

// gnb_cu_up_id_t formatter

// gnb_cu_up_id_t formatter
template <>
struct formatter<ocudu::gnb_cu_up_id_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::gnb_cu_up_id_t o, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", ocudu::gnb_cu_up_id_to_uint(o));
  }
};


} // namespace fmt
