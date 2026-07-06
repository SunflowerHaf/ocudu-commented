// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/aggregation_level.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/error_handling.h"
#include <cstdint>


namespace ocudu {

/// Aggregation Level of PDCCH allocation.

/// Aggregation Level of PDCCH allocation.
enum class aggregation_level : uint8_t { n1 = 0, n2, n4, n8, n16 };

/// Number of possible aggregation levels.

/// Number of possible aggregation levels.
const size_t NOF_AGGREGATION_LEVELS = 5;

/// Calculates number of CCEs based on Aggregation Level as per TS38.211 Table 7.3.2.1-1.

/// Calculates number of CCEs based on Aggregation Level as per TS38.211 Table 7.3.2.1-1.
inline unsigned to_nof_cces(aggregation_level lvl)
{
  return 1U << static_cast<uint8_t>(lvl);
}

/// Calculates the index associated to the passed aggregation level.

/// Calculates the index associated to the passed aggregation level.
inline unsigned to_aggregation_level_index(aggregation_level lvl)
{
  return static_cast<unsigned>(lvl);
}

/// Return aggregation level enum value.

/// Return aggregation level enum value.
inline aggregation_level aggregation_index_to_level(uint8_t aggr_lvl_idx)
{
  return static_cast<aggregation_level>(aggr_lvl_idx);
}


} // namespace ocudu
