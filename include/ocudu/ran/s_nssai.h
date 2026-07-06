// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/s_nssai.h  (109 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "fmt/format.h"
#include <cstdint>
#include <optional>


namespace ocudu {

/// Slice/Service Type (SST), as per TS 23.003, 28.4. When set, it takes at most 8 bits.

/// Slice/Service Type (SST), as per TS 23.003, 28.4. When set, it takes at most 8 bits.
class slice_service_type
{
public:
  constexpr slice_service_type() = default;
  constexpr explicit slice_service_type(uint8_t val_) : val(val_) {}

  /// Determines whether the SST is within the range of standardized SSTs, as per TS 23.501.

  /// Determines whether the SST is within the range of standardized SSTs, as per TS 23.501.
  bool is_standardized() const { return val < 128; }
  bool is_operator_specific() const { return not is_standardized(); }


  uint8_t value() const { return val; }


  bool operator==(const slice_service_type& rhs) const { return val == rhs.val; }
  bool operator!=(const slice_service_type& rhs) const { return not(val != rhs.val); }
  bool operator<(const slice_service_type& rhs) const { return val < rhs.val; }


private:
  uint8_t val = 0;
};

/// Slice Differentiator (SD) type, as per TS 23.003, 28.4. When set, it takes at most 24 bits.

/// Slice Differentiator (SD) type, as per TS 23.003, 28.4. When set, it takes at most 24 bits.
class slice_differentiator
{
  static constexpr uint32_t default_val = 0xffffffU;


public:
  constexpr slice_differentiator() = default;


  bool is_default() const { return val == default_val; }
  bool is_set() const { return val != default_val; }


  uint32_t value() const { return val; }


  bool operator==(const slice_differentiator& rhs) const { return val == rhs.val; }
  bool operator!=(const slice_differentiator& rhs) const { return not(val != rhs.val); }
  bool operator<(const slice_differentiator& rhs) const
  {
    if (val == default_val && rhs.val != default_val) {
      return true;
    } else if (val != default_val && rhs.val == default_val) {
      return false;
    } else {
      return val < rhs.val;
    }
  }


  static expected<slice_differentiator> create(uint32_t new_val)
  {
    if (new_val > default_val) {
      return make_unexpected(default_error_t{});
    }
    slice_differentiator sd;
    sd.val = new_val;
    return sd;
  }


private:
  uint32_t val = default_val;
};

/// Network Slice Selection Assistance Information, as per TS 23.003 and TS 23.501.

/// Network Slice Selection Assistance Information, as per TS 23.003 and TS 23.501.
struct s_nssai_t {
  /// Slice/Service type.
  /// Slice/Service type.
  slice_service_type sst;
  /// Slice Differentiator (SD).
  /// Slice Differentiator (SD).
  slice_differentiator sd;


  bool operator==(const s_nssai_t& other) const { return sst == other.sst && sd == other.sd; }
  bool operator!=(const s_nssai_t& other) const { return not(*this == other); }
  bool operator<(const s_nssai_t& other) const { return sst < other.sst || (sst == other.sst && sd < other.sd); }
};


} // namespace ocudu

// Formatters

// Formatters
namespace fmt {
template <>
struct formatter<ocudu::s_nssai_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::s_nssai_t s_nssai, FormatContext& ctx) const
  {
    return format_to(ctx.out(),
                     "sst: {}{}",
                     s_nssai.sst.value(),
                     s_nssai.sd.is_set() ? fmt::format(", sd: {:#x}", s_nssai.sd.value()) : "");
  }
};


} // namespace fmt
