// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/rnti.h  (71 lines)
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
#include <type_traits>


namespace ocudu {

/// Possible RNTI values.
/// \remark See TS 38.331 - RNTI-Value and TS 38.321, Table 7.1-1: RNTI Values. Values: (0..65535)
/// \remark See TS 38.321, 5.1.3 and 5.1.4 to obtain the list of possible RA-RNTIs and MSGB-RNTIs.

/// Possible RNTI values.
/// \remark See TS 38.331 - RNTI-Value and TS 38.321, Table 7.1-1: RNTI Values. Values: (0..65535)
/// \remark See TS 38.321, 5.1.3 and 5.1.4 to obtain the list of possible RA-RNTIs and MSGB-RNTIs.
enum class rnti_t : uint16_t {
  INVALID_RNTI = 0x0,
  MIN_RA_RNTI  = 0x1,
  // 0x4600 == 17920 == 14 * 80 * 8 * 2.
  // 0x4600 == 17920 == 14 * 80 * 8 * 2.
  MAX_RA_RNTI   = 0x4600,
  MIN_MSGB_RNTI = 0x4601,
  // 0x8c00 == 35840 == 14 * 80 * 8 * 4.
  // 0x8c00 == 35840 == 14 * 80 * 8 * 4.
  MAX_MSGB_RNTI = 0x8c00,
  MIN_CRNTI     = 0x1,
  // ...
  // ...
  MAX_CRNTI         = 0xffef,
  MIN_RESERVED_RNTI = 0xfff0,
  // ...
  // ...
  MAX_RESERVED_RNTI = 0xfffd,
  P_RNTI            = 0xfffe,
  SI_RNTI           = 0xffff
};

/// Checks whether RNTI value corresponds to a C-RNTI value.

/// Checks whether RNTI value corresponds to a C-RNTI value.
constexpr bool is_crnti(rnti_t rnti)
{
  return rnti <= rnti_t::MAX_CRNTI and rnti >= rnti_t::MIN_CRNTI;
}

/// Converts integer to RNTI value.

/// Converts integer to RNTI value.
constexpr rnti_t to_rnti(std::underlying_type_t<rnti_t> number)
{
  return static_cast<rnti_t>(number);
}

/// Converts RNTI value to integer.

/// Converts RNTI value to integer.
constexpr uint16_t to_value(rnti_t rnti)
{
  return static_cast<uint16_t>(rnti);
}


} // namespace ocudu

// Formatters

// Formatters
namespace fmt {
template <>
struct formatter<ocudu::rnti_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::rnti_t rnti, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{:#x}", to_value(rnti));
  }
};


} // namespace fmt
