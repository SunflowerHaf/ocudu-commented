// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pcch/paging_helper.h  (49 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/math/bit_ops.h"
#include <cstdint>


namespace ocudu {
namespace paging_helper {


namespace detail {

/// Helper to compute GF(2) polynomial division remainder.

/// Helper to compute GF(2) polynomial division remainder.
inline uint64_t gf2_mod(uint64_t D, uint64_t N)
{
  const uint64_t n_msb1 = find_first_msb_one(N);
  for (uint64_t d_msb1 = find_first_msb_one(D); D && d_msb1 >= n_msb1; d_msb1 = find_first_msb_one(D)) {
    uint64_t shift = d_msb1 - n_msb1;
    D ^= (N << shift);
  }
  return D;
}

/// Computes Hashed ID as per TS 38.304, clause 7.4.

/// Computes Hashed ID as per TS 38.304, clause 7.4.
inline uint32_t compute_hashed_ID(uint64_t tmsi48)
{
  constexpr static uint64_t Y1     = 0xc704dd7bU;
  constexpr static uint64_t crc32c = 0x104c11db7U;
  const uint64_t            Y3     = (tmsi48 & (mask_lsb_ones<uint64_t>(32))) << static_cast<uint64_t>(32U);
  // 1<<32 + 1<<26 + 1<<23 + ... + 1.
  // 1<<32 + 1<<26 + 1<<23 + ... + 1.
  const uint64_t Y2 = gf2_mod(Y3, crc32c);
  // Ones complement of the sum (modulo 2) of Y1 and Y2.
  // Ones complement of the sum (modulo 2) of Y1 and Y2.
  return static_cast<uint32_t>((~(Y1 ^ Y2)) & mask_lsb_ones<uint64_t>(32U));
}


} // namespace detail

/// Compute UE_ID_H according to TS 38.304, 7.4.
/// \param[in] tmsi48 5G-S-TMSI of 48 bits.
/// \return Value of UE_ID_H which contains the 13 MSBs of the Hashed ID.

/// Compute UE_ID_H according to TS 38.304, 7.4.
/// \param[in] tmsi48 5G-S-TMSI of 48 bits.
/// \return Value of UE_ID_H which contains the 13 MSBs of the Hashed ID.
inline uint32_t compute_UE_ID_H(uint64_t tmsi48)
{
  return detail::compute_hashed_ID(tmsi48) >> (32U - 13U);
}


} // namespace paging_helper
} // namespace ocudu
