// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/logical_channel/lcid_dl_sch.h  (127 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/logical_channel/lcid.h"
#include "ocudu/support/ocudu_assert.h"
#include "fmt/format.h"


namespace ocudu {

/// \brief LCID representation for PDSCH.

/// \brief LCID representation for PDSCH.
class lcid_dl_sch_t
{
  using underlying_type = std::underlying_type_t<lcid_t>;


public:
  /// 3GPP 38.321, Table 6.2.1-1 - Values of LCID for DL-SCH Index
  /// 3GPP 38.321, Table 6.2.1-1 - Values of LCID for DL-SCH Index
  enum options : underlying_type {
    CCCH = 0b000000,

    /// Identity of the logical channel

    /// Identity of the logical channel
    LCID1 = 1,
    // ...
    // ...
    LCID32 = 32,

    /// Reserved

    /// Reserved
    MIN_RESERVED = 33,
    MAX_RESERVED = 51,


    RECOMMENDED_BIT_RATE = 0b101111,

    // TODO: Add remaining.


    // TODO: Add remaining.

    SCELL_ACTIV_4_OCTET = 0b111001,
    SCELL_ACTIV_1_OCTET = 0b111010,


    LONG_DRX_CMD  = 0b111011,
    DRX_CMD       = 0b111100,
    TA_CMD        = 0b111101,
    UE_CON_RES_ID = 0b111110,
    PADDING       = 0b111111
  };


  constexpr lcid_dl_sch_t(underlying_type lcid_ = PADDING) : lcid_val(lcid_)
  {
    ocudu_assert(lcid_ <= PADDING, "Invalid LCID");
  }
  constexpr lcid_dl_sch_t& operator=(underlying_type lcid)
  {
    ocudu_assert(lcid <= PADDING, "Invalid LCID");
    lcid_val = lcid;
    return *this;
  }

  /// convert lcid_dl_sch_t to underlying integer type via cast.

  /// convert lcid_dl_sch_t to underlying integer type via cast.
  explicit constexpr operator underlying_type() const { return lcid_val; }

  /// convert lcid_dl_sch_t to underlying integer type.

  /// convert lcid_dl_sch_t to underlying integer type.
  constexpr underlying_type value() const { return lcid_val; }

  /// Whether LCID is an MAC CE

  /// Whether LCID is an MAC CE
  constexpr bool is_ce() const { return lcid_val <= PADDING and lcid_val >= RECOMMENDED_BIT_RATE; }

  /// Whether LCID belongs to a Radio Bearer Logical Channel

  /// Whether LCID belongs to a Radio Bearer Logical Channel
  constexpr bool is_sdu() const { return lcid_val <= LCID32 and lcid_val >= CCCH; }


  constexpr lcid_t to_lcid() const
  {
    ocudu_assert(is_sdu(), "Invalid to_lcid() access to lcid={}", lcid_val);
    return (lcid_t)lcid_val;
  }

  /// Returns false for all reserved values in Table 6.2.1-1 and 6.2.1-2

  /// Returns false for all reserved values in Table 6.2.1-1 and 6.2.1-2
  constexpr bool is_valid() const
  {
    return lcid_val <= PADDING and (lcid_val < MIN_RESERVED or lcid_val > MAX_RESERVED);
  }


  constexpr bool is_var_len_ce() const { return false; }


  constexpr uint32_t sizeof_ce() const
  {
    // Values taken from TS38.321, Section 6.1.3.
    // Values taken from TS38.321, Section 6.1.3.
    switch (lcid_val) {
      case SCELL_ACTIV_4_OCTET:
        return 4;
      case SCELL_ACTIV_1_OCTET:
        return 1;
      case LONG_DRX_CMD:
      case DRX_CMD:
        return 0;
      case TA_CMD:
        return 1;
      case UE_CON_RES_ID:
        return 6;
      case PADDING:
        return 0;
      default:
        break;
    }
    return 0;
  }


  constexpr bool operator==(lcid_dl_sch_t other) const { return lcid_val == other.lcid_val; }
  constexpr bool operator!=(lcid_dl_sch_t other) const { return lcid_val != other.lcid_val; }


private:
  underlying_type lcid_val;
};


} // namespace ocudu


namespace fmt {

/// FMT formatter of slot_point type.

/// FMT formatter of slot_point type.
template <>
struct formatter<ocudu::lcid_dl_sch_t> : public formatter<uint16_t> {
  template <typename FormatContext>
  auto format(ocudu::lcid_dl_sch_t lcid, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", (uint16_t)lcid);
  }
};


} // namespace fmt
