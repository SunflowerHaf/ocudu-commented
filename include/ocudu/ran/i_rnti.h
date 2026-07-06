// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/i_rnti.h  (174 lines)
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


namespace ocudu {

/// \brief Common type for Full-I-RNTI (40 Bit) as specified in TS 38.331 section 6.3.2 and TS 38.300 Annex F.
/// \remark The I-RNTI is composed of an I-RNTI profile, a gNB ID and a UE ID. The lengths of the gNB ID and UE ID are
/// defined by the used I-RNTI profile. The UE ID part of I-RNTI should not be derived from gNB UE ID to avoid the
/// possibility of UE tracking as specified in TS 33.501 section 6.8.2.1.2.
/// Note: Currently only Full-I-RNTI profile 0 is supported, the number of UE ID bits is configurable.

/// \brief Common type for Full-I-RNTI (40 Bit) as specified in TS 38.331 section 6.3.2 and TS 38.300 Annex F.
/// \remark The I-RNTI is composed of an I-RNTI profile, a gNB ID and a UE ID. The lengths of the gNB ID and UE ID are
/// defined by the used I-RNTI profile. The UE ID part of I-RNTI should not be derived from gNB UE ID to avoid the
/// possibility of UE tracking as specified in TS 33.501 section 6.8.2.1.2.
/// Note: Currently only Full-I-RNTI profile 0 is supported, the number of UE ID bits is configurable.
class full_i_rnti_t
{
public:
  /// Creates an Full-I-RNTI from a gNB ID and UE ID.
  /// \param[in] gnb_id_ gNB ID.
  /// \param[in] ue_id_ UE ID.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  /// Creates an Full-I-RNTI from a gNB ID and UE ID.
  /// \param[in] gnb_id_ gNB ID.
  /// \param[in] ue_id_ UE ID.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  constexpr full_i_rnti_t(uint32_t gnb_id_, uint32_t ue_id_, uint8_t nof_ue_bits_)
  {
    val =
        (static_cast<uint64_t>(gnb_id_ << nof_ue_bits_) + (ue_id_ & ((static_cast<uint16_t>(1) << nof_ue_bits_) - 1))) &
        0x3fffffffff;


    max_val = (static_cast<uint64_t>(gnb_id_ << nof_ue_bits_) + (static_cast<uint32_t>(1 << nof_ue_bits_) - 1)) &
              0x3fffffffff;
    min_val = (gnb_id_ << nof_ue_bits_) & 0x3fffffffff;
  }

  /// Returns the maximum Full-I-RNTI value.

  /// Returns the maximum Full-I-RNTI value.
  constexpr uint64_t max() const { return max_val; }

  /// Returns the minimum Full-I-RNTI value.

  /// Returns the minimum Full-I-RNTI value.
  constexpr uint32_t min() const { return min_val; }

  /// Creates an Full-I-RNTI from an Full-I-RNTI integer representation.
  /// \param[in] value Integer representation of the Full-I-RNTI.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  /// \return The created Full-I-RNTI or an error if the value is invalid.

  /// Creates an Full-I-RNTI from an Full-I-RNTI integer representation.
  /// \param[in] value Integer representation of the Full-I-RNTI.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  /// \return The created Full-I-RNTI or an error if the value is invalid.
  static expected<full_i_rnti_t> from_uint(uint64_t value, uint8_t nof_ue_bits_)
  {
    if (value > 0x3fffffffff) {
      return make_unexpected(default_error_t{});
    }


    auto gnb_id_val = static_cast<uint32_t>(value >> nof_ue_bits_);
    auto ue_id_val  = static_cast<uint32_t>(value - (gnb_id_val << nof_ue_bits_));
    return full_i_rnti_t{gnb_id_val, ue_id_val, nof_ue_bits_};
  }

  /// Returns the Full-I-RNTI value.

  /// Returns the Full-I-RNTI value.
  uint64_t value() const { return val; }


  bool operator==(const full_i_rnti_t& i_rnti) const { return val == i_rnti.val; }
  bool operator!=(const full_i_rnti_t& i_rnti) const { return val != i_rnti.val; }
  bool operator<(const full_i_rnti_t& i_rnti) const { return val < i_rnti.val; }
  bool operator<=(const full_i_rnti_t& i_rnti) const { return val <= i_rnti.val; }
  bool operator>(const full_i_rnti_t& i_rnti) const { return val > i_rnti.val; }
  bool operator>=(const full_i_rnti_t& i_rnti) const { return val >= i_rnti.val; }


private:
  uint64_t val     = 0;
  uint64_t max_val = 0;
  uint32_t min_val = 0;
};

/// \brief Common type for Short-I-RNTI (20 Bit) as specified in TS 38.331 section 6.3.2 and TS 38.300 Annex F.
/// \remark The I-RNTI is composed of an I-RNTI profile, a gNB ID and a UE ID. The lengths of the gNB ID and UE ID are
/// defined by the used I-RNTI profile. The UE ID part of I-RNTI should not be derived from gNB UE ID to avoid the
/// possibility of UE tracking as specified in TS 33.501 section 6.8.2.1.2.
/// Note: Currently only Short-I-RNTI profile 0 is supported, the number of UE ID bits is configurable.

/// \brief Common type for Short-I-RNTI (20 Bit) as specified in TS 38.331 section 6.3.2 and TS 38.300 Annex F.
/// \remark The I-RNTI is composed of an I-RNTI profile, a gNB ID and a UE ID. The lengths of the gNB ID and UE ID are
/// defined by the used I-RNTI profile. The UE ID part of I-RNTI should not be derived from gNB UE ID to avoid the
/// possibility of UE tracking as specified in TS 33.501 section 6.8.2.1.2.
/// Note: Currently only Short-I-RNTI profile 0 is supported, the number of UE ID bits is configurable.
class short_i_rnti_t
{
public:
  /// Creates an Short-I-RNTI from a gNB ID and UE ID.
  /// \param[in] gnb_id_ gNB ID.
  /// \param[in] ue_id_ UE ID.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  /// Creates an Short-I-RNTI from a gNB ID and UE ID.
  /// \param[in] gnb_id_ gNB ID.
  /// \param[in] ue_id_ UE ID.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  constexpr short_i_rnti_t(uint32_t gnb_id_, uint32_t ue_id_, uint8_t nof_ue_bits_)
  {
    val =
        (static_cast<uint32_t>(gnb_id_ << nof_ue_bits_) + (ue_id_ & ((static_cast<uint16_t>(1) << nof_ue_bits_) - 1))) &
        0x7ffff;


    max_val =
        (static_cast<uint32_t>(gnb_id_ << nof_ue_bits_) + (static_cast<uint32_t>(1 << nof_ue_bits_) - 1)) & 0x7ffff;


    min_val = (gnb_id_ << nof_ue_bits_) & 0x7ffff;
  }

  /// Returns the maximum Short-I-RNTI value.

  /// Returns the maximum Short-I-RNTI value.
  constexpr uint32_t max() const { return max_val; }

  /// Returns the minimum Short-I-RNTI value.

  /// Returns the minimum Short-I-RNTI value.
  constexpr uint32_t min() const { return min_val; }

  /// Creates an Short-I-RNTI from an Short-I-RNTI integer representation.
  /// \param[in] value Integer representation of the Short-I-RNTI.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.

  /// Creates an Short-I-RNTI from an Short-I-RNTI integer representation.
  /// \param[in] value Integer representation of the Short-I-RNTI.
  /// \param[in] nof_ue_bits_ Number of bits used for the UE ID.
  static expected<short_i_rnti_t> from_uint(uint32_t value, uint8_t nof_ue_bits_)
  {
    if (value > 0x7ffff) {
      return make_unexpected(default_error_t{});
    }


    auto gnb_id_val = static_cast<uint32_t>(value >> nof_ue_bits_);
    auto ue_id_val  = (value - (gnb_id_val << nof_ue_bits_));
    return short_i_rnti_t{gnb_id_val, ue_id_val, nof_ue_bits_};
  }

  /// Returns the Short-I-RNTI value.

  /// Returns the Short-I-RNTI value.
  uint32_t value() const { return val; }


  bool operator==(const short_i_rnti_t& i_rnti) const { return val == i_rnti.val; }
  bool operator!=(const short_i_rnti_t& i_rnti) const { return val != i_rnti.val; }
  bool operator<(const short_i_rnti_t& i_rnti) const { return val < i_rnti.val; }
  bool operator<=(const short_i_rnti_t& i_rnti) const { return val <= i_rnti.val; }
  bool operator>(const short_i_rnti_t& i_rnti) const { return val > i_rnti.val; }
  bool operator>=(const short_i_rnti_t& i_rnti) const { return val >= i_rnti.val; }


private:
  uint32_t val     = 0;
  uint32_t max_val = 0;
  uint32_t min_val = 0;
};

/// \brief Common type for Full- and Short-I-RNTI pair.

/// \brief Common type for Full- and Short-I-RNTI pair.
struct i_rntis_t {
  short_i_rnti_t short_i_rnti;
  full_i_rnti_t  full_i_rnti;
};


} // namespace ocudu

// Formatters

// Formatters
namespace fmt {


template <>
struct formatter<ocudu::full_i_rnti_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::full_i_rnti_t i_rnti, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "full-i-rnti={:#x}", i_rnti.value());
  }
};


template <>
struct formatter<ocudu::short_i_rnti_t> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::short_i_rnti_t i_rnti, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "short-i-rnti={:#x}", i_rnti.value());
  }
};


} // namespace fmt
