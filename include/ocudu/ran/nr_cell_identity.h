// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/nr_cell_identity.h  (107 lines)
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
#include "ocudu/ran/gnb_id.h"
#include "ocudu/support/ocudu_assert.h"
#include "fmt/format.h"
#include <cstdint>
#include <cstdlib>
#include <string>


namespace ocudu {

/// \brief 36-bit identifying an NR Cell Id as specified in subclause 9.3.1.7 of 3GPP TS 38.413.
/// \remark The leftmost (22-32) bits of the NR Cell Identity correspond to the gNB ID and remaining (4-14) bits for
/// Sector ID.

/// \brief 36-bit identifying an NR Cell Id as specified in subclause 9.3.1.7 of 3GPP TS 38.413.
/// \remark The leftmost (22-32) bits of the NR Cell Identity correspond to the gNB ID and remaining (4-14) bits for
/// Sector ID.
class nr_cell_identity
{
  constexpr nr_cell_identity(uint64_t val_) : val(val_) {}


public:
  static constexpr nr_cell_identity min() { return nr_cell_identity{0x0}; }
  static constexpr nr_cell_identity max() { return nr_cell_identity{((uint64_t)1U << 36U) - 1U}; }


  nr_cell_identity() : val(0) {}


  static expected<nr_cell_identity> create(uint64_t val)
  {
    if (val > max().val) {
      return make_unexpected(default_error_t{});
    }
    return nr_cell_identity{val};
  }


  static expected<nr_cell_identity> create(gnb_id_t gnb_id, uint16_t sector_id)
  {
    if (gnb_id.bit_length < 22 or gnb_id.bit_length > 32) {
      // invalid bit length.
      // invalid bit length.
      return make_unexpected(default_error_t{});
    }
    if (sector_id >= (1U << (36U - gnb_id.bit_length))) {
      // invalid sector id.
      // invalid sector id.
      return make_unexpected(default_error_t{});
    }
    return nr_cell_identity{(uint64_t)gnb_id.id << (36U - gnb_id.bit_length) | sector_id};
  }


  static expected<nr_cell_identity> parse_hex(const std::string& hex_str)
  {
    const unsigned digits = nof_bits() / 4;
    if (hex_str.size() > digits) {
      return make_unexpected(default_error_t{});
    }
    char*    p;
    uint64_t n = std::strtoul(hex_str.c_str(), &p, 16);
    if (*p != 0) {
      return make_unexpected(default_error_t{});
    }
    return nr_cell_identity{n};
  }


  uint64_t value() const { return val; }

  /// Extract Sector ID from NR Cell Identity.

  /// Extract Sector ID from NR Cell Identity.
  uint16_t sector_id(unsigned nof_sector_id_bits) const
  {
    ocudu_assert(nof_sector_id_bits >= 4 and nof_sector_id_bits <= 14, "Invalid number of Sector Id bits");
    return val & ((1U << nof_sector_id_bits) - 1U);
  }

  /// Extract gNB-DU ID from NR Cell Identity.

  /// Extract gNB-DU ID from NR Cell Identity.
  gnb_id_t gnb_id(unsigned nof_gnb_id_bits) const
  {
    ocudu_assert(nof_gnb_id_bits >= 22 and nof_gnb_id_bits <= 32, "Invalid number of gNB-DU ID bits");
    return gnb_id_t{static_cast<uint32_t>(val >> (36U - nof_gnb_id_bits)), static_cast<uint8_t>(nof_gnb_id_bits)};
  }


  static size_t nof_bits() { return 36; }


  bool operator==(const nr_cell_identity& nci) const { return val == nci.val; }
  bool operator!=(const nr_cell_identity& nci) const { return !(*this == nci); }
  bool operator<(const nr_cell_identity& nci) const { return val < nci.val; }
  bool operator<=(const nr_cell_identity& nci) const { return val <= nci.val; }
  bool operator>(const nr_cell_identity& nci) const { return val > nci.val; }
  bool operator>=(const nr_cell_identity& nci) const { return val >= nci.val; }


private:
  uint64_t val;
};


} // namespace ocudu


namespace fmt {


template <>
struct formatter<ocudu::nr_cell_identity> : formatter<uint64_t> {
  template <typename FormatContext>
  auto format(const ocudu::nr_cell_identity& val, FormatContext& ctx) const
  {
    return formatter<uint64_t>::format(val.value(), ctx);
  }
};


} // namespace fmt
