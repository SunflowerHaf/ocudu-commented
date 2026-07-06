// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_format_type.h  (136 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/ocudu_assert.h"


namespace ocudu {

/// \brief PRACH preamble formats.
///
/// PRACH preamble formats are described in TS38.211 Table 6.3.3.1-1 and 6.3.3.1-2.

/// \brief PRACH preamble formats.
///
/// PRACH preamble formats are described in TS38.211 Table 6.3.3.1-1 and 6.3.3.1-2.
enum class prach_format_type : uint8_t {
  zero = 0,
  one,
  two,
  three,
  A1,
  A2,
  A3,
  B1,
  B4,
  C0,
  C2,
  A1_B1,
  A2_B2,
  A3_B3,
  invalid
};


constexpr const char* to_string(prach_format_type format)
{
  switch (format) {
    case prach_format_type::zero:
      return "0";
    case prach_format_type::one:
      return "1";
    case prach_format_type::two:
      return "2";
    case prach_format_type::three:
      return "3";
    case prach_format_type::A1:
      return "A1";
    case prach_format_type::A1_B1:
      return "A1/B1";
    case prach_format_type::A2:
      return "A2";
    case prach_format_type::A2_B2:
      return "A2/B2";
    case prach_format_type::A3:
      return "A3";
    case prach_format_type::A3_B3:
      return "A3/B3";
    case prach_format_type::B1:
      return "B1";
    case prach_format_type::B4:
      return "B4";
    case prach_format_type::C0:
      return "C0";
    case prach_format_type::C2:
      return "C2";
    case prach_format_type::invalid:
    default:
      break;
  }
  return "invalid";
}


inline prach_format_type to_prach_format_type(const char* string)
{
  using int_type = std::underlying_type_t<prach_format_type>;
  for (int_type i_format     = static_cast<int_type>(prach_format_type::zero),
                i_format_end = static_cast<int_type>(prach_format_type::invalid);
       i_format != i_format_end;
       ++i_format) {
    prach_format_type format = static_cast<prach_format_type>(i_format);
    if (strcmp(string, to_string(format)) == 0) {
      return format;
    }
  }


  return prach_format_type::invalid;
}

/// \brief Checks if the preamble format is long.
///
/// Long preambles are listed in TS38.211 Table 6.3.3.1-1.

/// \brief Checks if the preamble format is long.
///
/// Long preambles are listed in TS38.211 Table 6.3.3.1-1.
constexpr bool is_long_preamble(prach_format_type type)
{
  return (type <= prach_format_type::three);
}

/// \brief Checks if the preamble format is short.
///
/// Short preambles are listed in TS38.211 Table 6.3.3.1-2.

/// \brief Checks if the preamble format is short.
///
/// Short preambles are listed in TS38.211 Table 6.3.3.1-2.
constexpr bool is_short_preamble(prach_format_type type)
{
  return (type < prach_format_type::invalid) && (type >= prach_format_type::A1);
}

/// \brief Gets the PRACH time-domain occasion duration in symbols relative to the RA subcarrier spacing.
///
/// Corresponds to parameter \f$N_\textup{dur}^\textup{RA}\f$ is TS38.211 Section 5.3.2. It is selected from TS38.211
/// Tables 6.3.3.2-2, 6.3.3.2-3 and 6.3.3.2-4.
///
/// \param[in] format PRACH preamble format.
/// \return The PRACH time-domain occasion duration for short PRACH formats, and 0 otherwise.

/// \brief Gets the PRACH time-domain occasion duration in symbols relative to the RA subcarrier spacing.
///
/// Corresponds to parameter \f$N_\textup{dur}^\textup{RA}\f$ is TS38.211 Section 5.3.2. It is selected from TS38.211
/// Tables 6.3.3.2-2, 6.3.3.2-3 and 6.3.3.2-4.
///
/// \param[in] format PRACH preamble format.
/// \return The PRACH time-domain occasion duration for short PRACH formats, and 0 otherwise.
inline unsigned get_preamble_duration(prach_format_type format)
{
  switch (format) {
    case prach_format_type::zero:
    case prach_format_type::one:
    case prach_format_type::two:
    case prach_format_type::three:
    case prach_format_type::invalid:
    default:
      return 0;
    case prach_format_type::A1:
    case prach_format_type::B1:
    case prach_format_type::A1_B1:
    case prach_format_type::C0:
      return 2;
    case prach_format_type::A2:
    case prach_format_type::A2_B2:
      return 4;
    case prach_format_type::A3:
    case prach_format_type::A3_B3:
    case prach_format_type::C2:
      return 6;
    case prach_format_type::B4:
      return 12;
  }
}


} // namespace ocudu
