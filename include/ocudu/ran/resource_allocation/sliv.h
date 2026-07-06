// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/resource_allocation/sliv.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <type_traits>


namespace ocudu {

/// \brief Convert SLIV to start S and length L.
/// \param[in] N Max length.
/// \param[in] sliv An index giving a combination (jointly encoded) of start and length indicator (SLIV).
/// \param[out] S Start.
/// \param[out] L Length.

/// \brief Convert SLIV to start S and length L.
/// \param[in] N Max length.
/// \param[in] sliv An index giving a combination (jointly encoded) of start and length indicator (SLIV).
/// \param[out] S Start.
/// \param[out] L Length.
template <typename Integer>
constexpr void sliv_to_s_and_l(unsigned N, unsigned sliv, Integer& S, Integer& L)
{
  static_assert(std::is_integral<Integer>::value, "Non-integer type passed as S + L output.");
  unsigned low  = sliv % N;
  unsigned high = sliv / N;
  if (high + 1 + low <= N) {
    S = low;
    L = high + 1;
  } else {
    S = N - 1 - low;
    L = N - high + 1;
  }
}

/// \brief Convert start S and length L into SLIV.
/// \param[in] N Max length.
/// \param[out] S Start symbols.
/// \param[out] L Length.
/// \return An index giving a combination (jointly encoded) of start symbols and length indicator (SLIV).

/// \brief Convert start S and length L into SLIV.
/// \param[in] N Max length.
/// \param[out] S Start symbols.
/// \param[out] L Length.
/// \return An index giving a combination (jointly encoded) of start symbols and length indicator (SLIV).
constexpr unsigned sliv_from_s_and_l(unsigned N, unsigned S, unsigned L)
{
  if ((L - 1) <= N / 2) {
    return N * (L - 1) + S;
  }
  return N * (N - L + 1) + (N - 1 - S);
}


} // namespace ocudu
