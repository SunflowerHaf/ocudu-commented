// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/du_types.h  (63 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/du_cell_index.h"
#include "fmt/format.h"
#include <cstdint>
#include <type_traits>


namespace ocudu {

/// Maximum number of UEs supported by DU (implementation-defined).

/// Maximum number of UEs supported by DU (implementation-defined).
enum du_ue_index_t : uint16_t {
  MIN_DU_UE_INDEX         = 0,
  MAX_NOF_DU_UES_PER_CELL = 2048,
  MAX_DU_UE_INDEX         = 8191,
  MAX_NOF_DU_UES          = 8192,
  INVALID_DU_UE_INDEX     = MAX_NOF_DU_UES
};

/// Convert integer to DU UE index type.

/// Convert integer to DU UE index type.
constexpr du_ue_index_t to_du_ue_index(std::underlying_type_t<du_ue_index_t> idx)
{
  return static_cast<du_ue_index_t>(idx);
}


constexpr bool is_du_ue_index_valid(du_ue_index_t ue_idx)
{
  return ue_idx < MAX_NOF_DU_UES;
}

/// \brief DU-specific index to group of cells that might be aggregated into a UE-specific CellGroup, if the UE
/// is CA-capable.

/// \brief DU-specific index to group of cells that might be aggregated into a UE-specific CellGroup, if the UE
/// is CA-capable.
enum du_cell_group_index_t : uint16_t {
  MAX_DU_CELL_GROUPS          = du_cell_index_t::MAX_NOF_DU_CELLS,
  INVALID_DU_CELL_GROUP_INDEX = MAX_DU_CELL_GROUPS
};


} // namespace ocudu


namespace fmt {


template <>
struct formatter<ocudu::du_ue_index_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::du_ue_index_t ue_idx, FormatContext& ctx) const
  {
    if (ocudu::is_du_ue_index_valid(ue_idx)) {
      return format_to(ctx.out(), "{}", underlying(ue_idx));
    }
    return format_to(ctx.out(), "invalid");
  }
};


} // namespace fmt
