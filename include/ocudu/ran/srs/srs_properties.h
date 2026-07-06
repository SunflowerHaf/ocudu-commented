// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/srs/srs_properties.h  (73 lines)
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

/// Transmission comb size, as per \c transmissionComb, in \c SRS-Config, TS 38.331, or \f$K_{TC}\f$, as per
/// Section 6.4.1.4.1, TS 38.211. Values {2, 4}.

/// Transmission comb size, as per \c transmissionComb, in \c SRS-Config, TS 38.331, or \f$K_{TC}\f$, as per
/// Section 6.4.1.4.1, TS 38.211. Values {2, 4}.
enum class tx_comb_size : uint8_t { n2 = 2, n4 = 4 };

/// Transmission comb pos size, as per \c transmissionComb, in \c SRS-Config, TS 38.331, or \f$K_{TC}\f$, as per
/// Section 6.4.1.4.1, TS 38.211. Values {2, 4, 8}.

/// Transmission comb pos size, as per \c transmissionComb, in \c SRS-Config, TS 38.331, or \f$K_{TC}\f$, as per
/// Section 6.4.1.4.1, TS 38.211. Values {2, 4, 8}.
enum class tx_comb_pos_size : uint8_t { n2 = 2, n4 = 4, n8 = 8 };

/// \brief \c groupOrSequenceHopping, parameter for configuring group or sequence hopping.
/// \remark See TS 38.211, clause 6.4.1.4.2, or TS 38.331, "SRS-Resource".

/// \brief \c groupOrSequenceHopping, parameter for configuring group or sequence hopping.
/// \remark See TS 38.211, clause 6.4.1.4.2, or TS 38.331, "SRS-Resource".
enum class srs_group_or_sequence_hopping { neither, group_hopping, sequence_hopping };

/// \brief \c resourceType, as per TS 38.331, "SRS-Resource".

/// \brief \c resourceType, as per TS 38.331, "SRS-Resource".
enum class srs_resource_type { aperiodic, semi_persistent, periodic };

/// \brief SRS resource usage.
/// \remark See TS 38.214, clause 6.2.1.

/// \brief SRS resource usage.
/// \remark See TS 38.214, clause 6.2.1.
enum class srs_usage : uint8_t { beam_management, codebook, non_codebook, antenna_switching };

/// Convert SRS resource type to string.

/// Convert SRS resource type to string.
inline std::string_view to_string(srs_resource_type res_type)
{
  switch (res_type) {
    case srs_resource_type::aperiodic:
      return "aperiodic";
    case srs_resource_type::semi_persistent:
      return "semi-persistent";
    case srs_resource_type::periodic:
      return "periodic";
    default:
      break;
  }
  return "Invalid srs resource type";
}

/// Definition of the SRS number of symbols.

/// Definition of the SRS number of symbols.
enum srs_nof_symbols : uint8_t {
  n1 = 1,
  n2 = 2,
  n4 = 4,
};


enum class srs_periodicity : uint16_t {
  sl1    = 1,
  sl2    = 2,
  sl4    = 4,
  sl5    = 5,
  sl8    = 8,
  sl10   = 10,
  sl16   = 16,
  sl20   = 20,
  sl32   = 32,
  sl40   = 40,
  sl64   = 64,
  sl80   = 80,
  sl160  = 160,
  sl320  = 320,
  sl640  = 640,
  sl1280 = 1280,
  sl2560 = 2560
};


} // namespace ocudu
