// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Cyclic Prefix types and related slot size.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/cyclic_prefix.h  (121 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/// \file
/// \brief Cyclic Prefix types and related slot size.

#pragma once


#include "ocudu/ran/phy_time_unit.h"
#include "ocudu/support/math/math_utils.h"
#include <algorithm>


namespace ocudu {

/// Describes a cyclic prefix configuration with its helper methods.

/// Describes a cyclic prefix configuration with its helper methods.
class cyclic_prefix
{
public:
  /// Cyclic Prefix types, as described in TS 38.211.
  /// Cyclic Prefix types, as described in TS 38.211.
  enum options {
    /// Indicates normal cyclic prefix length.
    /// Indicates normal cyclic prefix length.
    NORMAL = 0,
    /// Indicates extended cyclic prefix length.
    /// Indicates extended cyclic prefix length.
    EXTENDED
  };

  /// Indicates the cyclic prefix type.

  /// Indicates the cyclic prefix type.
  options value = NORMAL;

  /// Default constructor as normal.

  /// Default constructor as normal.
  constexpr cyclic_prefix() = default;

  /// Construct from value. It allows implicit conversion from a cyclic prefix option.

  /// Construct from value. It allows implicit conversion from a cyclic prefix option.
  constexpr cyclic_prefix(options opt) : value(opt) {}

  /// Implicit conversion to enumerate.

  /// Implicit conversion to enumerate.
  constexpr operator options() const { return value; }

  /// Get the string value.

  /// Get the string value.
  std::string to_string() const
  {
    if (value == NORMAL) {
      return "normal";
    }
    return "extended";
  }

  /// \brief Checks the validity of the DFT size and subcarrier spacing for the current cyclic prefix.
  ///
  /// A cyclic prefix is valid if it results in an integer number of samples. Othwerwise, it is not valid.
  ///
  /// \param[in] scs      Subcarrier spacing.
  /// \param[in] dft_size DFT size.
  /// \return True if the cyclic prefix is valid for the given SCS and DFT size.

  /// \brief Checks the validity of the DFT size and subcarrier spacing for the current cyclic prefix.
  ///
  /// A cyclic prefix is valid if it results in an integer number of samples. Othwerwise, it is not valid.
  ///
  /// \param[in] scs      Subcarrier spacing.
  /// \param[in] dft_size DFT size.
  /// \return True if the cyclic prefix is valid for the given SCS and DFT size.
  bool is_valid(subcarrier_spacing scs, unsigned dft_size) const
  {
    // All units are in multiples of the constant kappa.
    // All units are in multiples of the constant kappa.
    unsigned cp_len = 144U >> to_numerology_value(scs);
    if (value == EXTENDED) {
      cp_len = 512U >> to_numerology_value(scs);
    }


    auto sampling_rate_Hz = to_sampling_rate_Hz<unsigned>(scs, dft_size);

    // The cyclic prefix lengths must result in an integer number of samples.

    // The cyclic prefix lengths must result in an integer number of samples.
    return phy_time_unit::from_units_of_kappa(cp_len).is_sample_accurate(sampling_rate_Hz) &&
           phy_time_unit::from_units_of_kappa(16).is_sample_accurate(sampling_rate_Hz);
  }

  /// \brief Calculates the cyclic prefix length in samples as per TS38.211 Section 5.3.1.
  /// \param[in] symbol_idx Symbol index within the subframe.
  /// \param[in] scs        Subcarrier spacing numerology.
  /// \return The cyclic prefix length in PHY time units.

  /// \brief Calculates the cyclic prefix length in samples as per TS38.211 Section 5.3.1.
  /// \param[in] symbol_idx Symbol index within the subframe.
  /// \param[in] scs        Subcarrier spacing numerology.
  /// \return The cyclic prefix length in PHY time units.
  constexpr phy_time_unit get_length(unsigned symbol_idx, subcarrier_spacing scs) const
  {
    // All units are in multiples of the constant kappa.
    // All units are in multiples of the constant kappa.
    unsigned cp_len = 144U >> to_numerology_value(scs);
    if (value == EXTENDED) {
      cp_len = 512U >> to_numerology_value(scs);
    } else if (symbol_idx == 0 || symbol_idx == 7 * pow2(to_numerology_value(scs))) {
      cp_len += 16;
    }


    return phy_time_unit::from_units_of_kappa(cp_len);
  }
};

/// Defines the number of OFDM symbols per slot, according to TS 38.211 Tables 4.3.2-1 and 4.3.2-2.

/// Defines the number of OFDM symbols per slot, according to TS 38.211 Tables 4.3.2-1 and 4.3.2-2.
constexpr unsigned get_nsymb_per_slot(cyclic_prefix cp)
{
  if (cp == cyclic_prefix::EXTENDED) {
    return 12;
  }
  return 14;
}

/// Returns the maximum number of OFDM symbols per slot.

/// Returns the maximum number of OFDM symbols per slot.
constexpr unsigned MAX_NSYMB_PER_SLOT =
    std::max(get_nsymb_per_slot(cyclic_prefix::NORMAL), get_nsymb_per_slot(cyclic_prefix::EXTENDED));


} // namespace ocudu


namespace fmt {

/// FMT formatter of slot_point type.

/// FMT formatter of slot_point type.
template <>
struct formatter<ocudu::cyclic_prefix> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }
  template <typename FormatContext>
  auto format(ocudu::cyclic_prefix cp, FormatContext& ctx) const
  {
    return format_to(ctx.out(), "{}", cp.to_string());
  }
};


} // namespace fmt
