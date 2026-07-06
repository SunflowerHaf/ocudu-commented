// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/gtpu/gtpu_teid.h  (60 lines)
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
#include "fmt/format.h"
#include <chrono>


namespace ocudu {

/// \brief GTP-U Tunnel Identifier.

/// \brief GTP-U Tunnel Identifier.
struct gtpu_teid_tag {};
using gtpu_teid_t =
    strong_type<uint32_t, struct gtpu_teid_tag, strong_equality, strong_equality_with<uint32_t>, strong_comparison>;


struct gtpu_teid_hasher_t {
  std::size_t operator()(const gtpu_teid_t& teid) const { return std::hash<uint32_t>()(teid.value()); }
};


struct gtpu_teid_compare_t {
  bool operator()(const gtpu_teid_t& lhs, const gtpu_teid_t& rhs) const
  {
    return std::less<>{}(lhs.value(), rhs.value());
  }
};

/// \brief Convert integer to GTP-U TEID value.

/// \brief Convert integer to GTP-U TEID value.
constexpr gtpu_teid_t int_to_gtpu_teid(uint32_t teid_val)
{
  return gtpu_teid_t{teid_val};
}

/// \brief TEID for path management messages via GTP-U, e.g. echo request, echo response,...

/// \brief TEID for path management messages via GTP-U, e.g. echo request, echo response,...
constexpr gtpu_teid_t GTPU_PATH_MANAGEMENT_TEID = int_to_gtpu_teid(0);

/// \brief Smallest TEID value that is not used for path management.

/// \brief Smallest TEID value that is not used for path management.
constexpr gtpu_teid_t GTPU_TEID_MIN = int_to_gtpu_teid(1);

/// \brief Largest TEID value that is not used for path management.

/// \brief Largest TEID value that is not used for path management.
constexpr gtpu_teid_t GTPU_TEID_MAX = int_to_gtpu_teid(std::numeric_limits<uint32_t>::max());

/// \brief Default error indication suppression time for recently released TEIDs.

/// \brief Default error indication suppression time for recently released TEIDs.
constexpr std::chrono::milliseconds GTPU_DEFAULT_TEID_RELEASE_LINGER_TIME{100};


} // namespace ocudu


namespace fmt {


template <>
struct formatter<ocudu::gtpu_teid_t> : public formatter<std::string> {
  template <typename FormatContext>
  auto format(const ocudu::gtpu_teid_t& t, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{:#08x}", t.value());
  }
};


} // namespace fmt
