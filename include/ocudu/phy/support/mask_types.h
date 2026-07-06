// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/phy/support/mask_types.h  (83 lines)
//
// INTERFACE HEADER — include/ocudu/phy
// Physical layer interface headers (~233 files): the largest include tree. Contains: upper_phy_rx_symbol_handler and upper_phy_rg_gateway (the DL/UL boundary between upper and lower PHY), resource_grid (the frequency-domain IQ sample grid), channel processor interfaces (PDSCH, PUSCH, PUCCH, PRACH, SRS processors), DFT interface, channel estimation interfaces, LDPC encoder/decoder interfaces, rate-matcher interfaces, modulator/demodulator interfaces, and all the supporting data types (resource_element_mapping, re_buffer, modulation_scheme, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/resource_block.h"


namespace ocudu {

/// \brief Represents a symbol mask within a slot.
///
/// Inherits from \c bounded_bitset<MAX_NSYMB_PER_SLOT>.

/// \brief Represents a symbol mask within a slot.
///
/// Inherits from \c bounded_bitset<MAX_NSYMB_PER_SLOT>.
class symbol_slot_mask : public bounded_bitset<MAX_NSYMB_PER_SLOT>
{
public:
  /// Default constructor - It creates a mask containing \c MAX_NSYMB_PER_SLOT bits.
  /// Default constructor - It creates a mask containing \c MAX_NSYMB_PER_SLOT bits.
  constexpr symbol_slot_mask(unsigned nsymb = MAX_NSYMB_PER_SLOT) : bounded_bitset(nsymb) {}

  /// Copy constructor from another \c bounded_bitset<MAX_NSYMB_PER_SLOT>.

  /// Copy constructor from another \c bounded_bitset<MAX_NSYMB_PER_SLOT>.
  constexpr symbol_slot_mask(const bounded_bitset& other) : bounded_bitset(other) {}

  /// Constructor from an initializer list.

  /// Constructor from an initializer list.
  constexpr symbol_slot_mask(const std::initializer_list<const bool>& list) : bounded_bitset(list) {}
};

/// \brief Represents a RE mask within a PRB.
///
/// Inherits from \c bounded_bitset<NOF_SUBCARRIERS_PER_RB>.

/// \brief Represents a RE mask within a PRB.
///
/// Inherits from \c bounded_bitset<NOF_SUBCARRIERS_PER_RB>.
class re_prb_mask : public bounded_bitset<NOF_SUBCARRIERS_PER_RB>
{
public:
  /// Default constructor - It creates a mask containing \c NOF_SUBCARRIERS_PER_RB bits.
  /// Default constructor - It creates a mask containing \c NOF_SUBCARRIERS_PER_RB bits.
  constexpr re_prb_mask() : bounded_bitset(NOF_SUBCARRIERS_PER_RB) {}

  /// Copy constructor from another \c bounded_bitset<NOF_SUBCARRIERS_PER_RB>.

  /// Copy constructor from another \c bounded_bitset<NOF_SUBCARRIERS_PER_RB>.
  constexpr re_prb_mask(const bounded_bitset& other) : bounded_bitset(other) {}

  /// Constructor from an initializer list.

  /// Constructor from an initializer list.
  constexpr re_prb_mask(const std::initializer_list<const bool>& list) : bounded_bitset(list) {}
};


} // namespace ocudu


namespace fmt {

/// \brief Custom formatter for symbol_slot_mask.

/// \brief Custom formatter for symbol_slot_mask.
template <>
struct formatter<ocudu::symbol_slot_mask> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::symbol_slot_mask& mask, FormatContext& ctx) const
  {
    fmt::format_to(ctx.out(), "{:i}", static_cast<ocudu::bounded_bitset<ocudu::MAX_NSYMB_PER_SLOT>>(mask));
    return ctx.out();
  }
};

/// \brief Custom formatter for re_prb_mask.

/// \brief Custom formatter for re_prb_mask.
template <>
struct formatter<ocudu::re_prb_mask> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(const ocudu::re_prb_mask& mask, FormatContext& ctx) const
  {
    fmt::format_to(ctx.out(), "{:i}", static_cast<ocudu::bounded_bitset<ocudu::NOF_SUBCARRIERS_PER_RB>>(mask));
    return ctx.out();
  }
};


} // namespace fmt
