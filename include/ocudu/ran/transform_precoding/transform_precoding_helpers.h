// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Transform precoding valid sizes.
///
/// A number of physical blocs for transform precoding is valid if satisfies \f$M_{RB} = 2^{\alpha _2}\cdot 3^{\alpha
/// _3}\cdot 5^{\alpha _5}\f$ where \f$\alpha _2\f$, \f$\alpha _3\f$ and \f$\alpha _3\f$ are non-negative integers.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/transform_precoding/transform_precoding_helpers.h  (93 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Transform precoding valid sizes.
///
/// A number of physical blocs for transform precoding is valid if satisfies \f$M_{RB} = 2^{\alpha _2}\cdot 3^{\alpha
/// _3}\cdot 5^{\alpha _5}\f$ where \f$\alpha _2\f$, \f$\alpha _3\f$ and \f$\alpha _3\f$ are non-negative integers.

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/ran/resource_block.h"
#include <array>
#include <optional>


namespace ocudu::transform_precoding {

/// Gets a boolean span where each position indicates if it is a valid number of RB for transform precoding.

/// Gets a boolean span where each position indicates if it is a valid number of RB for transform precoding.
inline span<const bool> get_valid_nof_prbs()
{
  static constexpr std::array<bool, MAX_NOF_PRBS + 1> mask = {
      false, true,  true,  true,  true,  true,  true,  false, true,  true,  true,  false, true,  false, false, true,
      true,  false, true,  false, true,  false, false, false, true,  true,  false, true,  false, false, true,  false,
      true,  false, false, false, true,  false, false, false, true,  false, false, false, false, true,  false, false,
      true,  false, true,  false, false, false, true,  false, false, false, false, false, true,  false, false, false,
      true,  false, false, false, false, false, false, false, true,  false, false, true,  false, false, false, false,
      true,  true,  false, false, false, false, false, false, false, false, true,  false, false, false, false, false,
      true,  false, false, false, true,  false, false, false, false, false, false, false, true,  false, false, false,
      false, false, false, false, false, false, false, false, true,  false, false, false, false, true,  false, false,
      true,  false, false, false, false, false, false, true,  false, false, false, false, false, false, false, false,
      true,  false, false, false, false, false, true,  false, false, false, false, false, false, false, false, false,
      true,  false, true,  false, false, false, false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, true,  false, false, false, false, false, false, false, false, false, false, false,
      true,  false, false, false, false, false, false, false, true,  false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, true,  false, false, false, false, false, false, false,
      false, true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false,
      true,  false, false, true,  false, false, false, false, false, false, true,  false, false, false, false, false,
      true,  false, false, false, false, false, false, false, false, false, false, false, false, false, true,  false,
      false, false, false, false};
  return mask;
}

/// Determines whether a number of PRB is valid.

/// Determines whether a number of PRB is valid.
inline bool is_nof_prbs_valid(unsigned nof_prb)
{
  span<const bool> valid_nof_prb = get_valid_nof_prbs();
  if (nof_prb >= valid_nof_prb.size()) {
    return false;
  }
  return valid_nof_prb[nof_prb];
}

/// \brief Get the smallest valid number of PRBs for transform precoding that is not smaller than the given input.
/// \return A number of PRBs larger than or equal to the given number of PRBs.

/// \brief Get the smallest valid number of PRBs for transform precoding that is not smaller than the given input.
/// \return A number of PRBs larger than or equal to the given number of PRBs.
inline std::optional<unsigned> get_nof_prbs_upper_bound(unsigned nof_prb)
{
  span<const bool> valid_nof_prb = get_valid_nof_prbs();
  if (nof_prb > valid_nof_prb.size()) {
    return std::nullopt;
  }


  const auto* nearest = std::find(valid_nof_prb.begin() + nof_prb, valid_nof_prb.end(), true);
  if (nearest == valid_nof_prb.end()) {
    return std::nullopt;
  }


  return std::distance(valid_nof_prb.begin(), nearest);
}

/// \brief Get the largest valid number of PRBs for transform precoding that is not greater than the given input.
/// \return A number of PRBs smaller than or equal to the given number of PRBs.

/// \brief Get the largest valid number of PRBs for transform precoding that is not greater than the given input.
/// \return A number of PRBs smaller than or equal to the given number of PRBs.
inline std::optional<unsigned> get_nof_prbs_lower_bound(unsigned nof_prb)
{
  span<const bool> valid_nof_prb = get_valid_nof_prbs();
  if (nof_prb > valid_nof_prb.size()) {
    return std::nullopt;
  }

  // Limit search to the first "nof_prb" PRBs.
  // NOTE: +1 is to take into account the \c valid_nof_prb size, which is \c MAX_NOF_PRBS + 1.

  // Limit search to the first "nof_prb" PRBs.
  // NOTE: +1 is to take into account the \c valid_nof_prb size, which is \c MAX_NOF_PRBS + 1.
  valid_nof_prb = valid_nof_prb.first(nof_prb + 1);


  auto nearest = std::find(valid_nof_prb.rbegin(), valid_nof_prb.rend(), true);
  if (nearest == valid_nof_prb.rend()) {
    return std::nullopt;
  }


  return std::distance(valid_nof_prb.begin(), (++nearest).base());
}


} // namespace ocudu::transform_precoding
