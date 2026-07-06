// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/dmrs/dmrs.h  (71 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include <cstdint>


namespace ocudu {

/// \brief Position of first DM-RS for Downlink (see TS 38.211, clause 7.4.1.1.1) and Uplink (see TS 38.211,
/// clause 6.4.1.1.3).

/// \brief Position of first DM-RS for Downlink (see TS 38.211, clause 7.4.1.1.1) and Uplink (see TS 38.211,
/// clause 6.4.1.1.3).
enum class dmrs_typeA_position { pos2 = 2, pos3 = 3 };


inline unsigned to_symbol_index(dmrs_typeA_position pos)
{
  return static_cast<unsigned>(pos);
}

/// \brief Type of DM-RS to be used in DL and UL.
/// \remark See TS 38.331, DMRS-DownlinkConfig and DMRS-UplinkConfig.

/// \brief Type of DM-RS to be used in DL and UL.
/// \remark See TS 38.331, DMRS-DownlinkConfig and DMRS-UplinkConfig.
enum class dmrs_config_type { type1 = 1, type2, not_set };

/// \brief Position for additional DM-RS in DL (see TS 38.211, Tables 7.4.1.1.2-3 and 7.4.1.1.2-4).
/// \remark See TS 38.331, DMRS-DownlinkConfig and DMRS-UplinkConfig.

/// \brief Position for additional DM-RS in DL (see TS 38.211, Tables 7.4.1.1.2-3 and 7.4.1.1.2-4).
/// \remark See TS 38.331, DMRS-DownlinkConfig and DMRS-UplinkConfig.
enum class dmrs_additional_positions { pos0 = 0, pos1, pos2, pos3 };


inline dmrs_additional_positions uint_to_dmrs_additional_positions(uint8_t dmrs_add_pos)
{
  return static_cast<dmrs_additional_positions>(dmrs_add_pos);
}

/// \brief The maximum number of OFDM symbols for DL front loaded DM-RS.
///
/// If set to len2, the UE determines the actual number of DM-RS symbols by the associated DCI. (see TS 38.214,
/// clause 7.4.1.1.2).
/// \remark See TS 38.214, DMRS-DownlinkConfig.

/// \brief The maximum number of OFDM symbols for DL front loaded DM-RS.
///
/// If set to len2, the UE determines the actual number of DM-RS symbols by the associated DCI. (see TS 38.214,
/// clause 7.4.1.1.2).
/// \remark See TS 38.214, DMRS-DownlinkConfig.
enum class dmrs_max_length { len1 = 1, len2, not_set };

/// Gets the number of resource elements occupied by DM-RS per PRB and symbol for a given type of DM-RS.

/// Gets the number of resource elements occupied by DM-RS per PRB and symbol for a given type of DM-RS.
constexpr unsigned get_nof_re_per_prb(dmrs_config_type type)
{
  return type == dmrs_config_type::type1 ? 6 : 4;
}

/// Gets the maximum number of CDM groups without data for a given type of DM-RS.

/// Gets the maximum number of CDM groups without data for a given type of DM-RS.
constexpr unsigned get_max_nof_cdm_groups_without_data(dmrs_config_type type)
{
  return type == dmrs_config_type::type1 ? 2 : 3;
}

/// Returns a string with the DM-RS type.

/// Returns a string with the DM-RS type.
constexpr const char* to_string(dmrs_config_type type)
{
  ocudu_assert(type != dmrs_config_type::not_set, "Invalid DM-RS type.");
  return (type == dmrs_config_type::type1) ? "Type1" : "Type2";
}

/// FMT formatting function

/// FMT formatting function
inline std::string format_as(dmrs_config_type type)
{
  return to_string(type);
}

/// \brief Data type used to represent a DM-RS symbol mask for PDSCH and PUSCH transmissions.
///
/// Each bit set in the bitset represents a symbol within the slot. The first bit corresponds to the first symbol.

/// \brief Data type used to represent a DM-RS symbol mask for PDSCH and PUSCH transmissions.
///
/// Each bit set in the bitset represents a symbol within the slot. The first bit corresponds to the first symbol.
using dmrs_symbol_mask = bounded_bitset<14>;


} // namespace ocudu
