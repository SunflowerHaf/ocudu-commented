// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/units.h  (154 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/strong_type.h"
#include "fmt/format.h"
#include <climits>


namespace ocudu {


namespace units {


namespace detail {
/// Tag struct used to uniquely identify the bit units type.
/// Tag struct used to uniquely identify the bit units type.
struct bit_tag {
  /// Text representation for the units.
  /// Text representation for the units.
  static const char* str() { return "bits"; }
};

/// Tag struct used to uniquely identify the byte units type.

/// Tag struct used to uniquely identify the byte units type.
struct byte_tag {
  /// Text representation for the units.
  /// Text representation for the units.
  static const char* str() { return "bytes"; }
};
} // namespace detail


class bytes;

/// \brief Abstraction of bit as a unit of digital information.
///
/// An object of this type will represent an amount of digital information expressed in bits.

/// \brief Abstraction of bit as a unit of digital information.
///
/// An object of this type will represent an amount of digital information expressed in bits.
class bits : public strong_type<unsigned,
                                detail::bit_tag,
                                strong_arithmetic,
                                strong_increment_decrement,
                                strong_multiplication_with<unsigned>>
{
  /// Type alias for the base class of the bits units class.
  /// Type alias for the base class of the bits units class.
  using bits_base = strong_type<unsigned,
                                detail::bit_tag,
                                strong_arithmetic,
                                strong_increment_decrement,
                                strong_multiplication_with<unsigned>>;


public:
  using bits_base::bits_base;


  constexpr bits(const bits_base& other) : bits_base(other) {}

  /// Returns true if the amount of digital information expressed as bits is a multiple of a byte.

  /// Returns true if the amount of digital information expressed as bits is a multiple of a byte.
  constexpr bool is_byte_exact() const { return ((value() % CHAR_BIT) == 0); }

  /// Returns the amount of digital information expressed as an integer number of bytes, rounded down.

  /// Returns the amount of digital information expressed as an integer number of bytes, rounded down.
  constexpr bytes truncate_to_bytes() const;

  /// Returns the amount of digital information expressed as an integer number of bytes, rounded up.

  /// Returns the amount of digital information expressed as an integer number of bytes, rounded up.
  constexpr bytes round_up_to_bytes() const;
};

/// \brief Abstraction of byte as a unit of digital information.
///
/// An object of this class will represent an amount of digital information expressed in bytes. The class also provides
/// a method to convert such amount into a number of information bits.

/// \brief Abstraction of byte as a unit of digital information.
///
/// An object of this class will represent an amount of digital information expressed in bytes. The class also provides
/// a method to convert such amount into a number of information bits.
class bytes : public strong_type<unsigned,
                                 detail::byte_tag,
                                 strong_arithmetic,
                                 strong_increment_decrement,
                                 strong_multiplication_with<unsigned>>
{
  /// Type alias for the base class of the byte units class.
  /// Type alias for the base class of the byte units class.
  using bytes_base = strong_type<unsigned,
                                 detail::byte_tag,
                                 strong_arithmetic,
                                 strong_increment_decrement,
                                 strong_multiplication_with<unsigned>>;


public:
  using bytes_base::bytes_base;


  constexpr bytes(const bytes_base& other) : bytes_base(other) {}


  explicit constexpr operator bits() const { return to_bits(); }

  /// Returns the amount of digital information as a number of bits.

  /// Returns the amount of digital information as a number of bits.
  constexpr bits to_bits() const { return bits(value() * CHAR_BIT); }
};


constexpr bytes bits::truncate_to_bytes() const
{
  return bytes(value() / CHAR_BIT);
}


constexpr bytes bits::round_up_to_bytes() const
{
  return bytes((value() + CHAR_BIT - 1) / CHAR_BIT);
}


namespace literals {

/// User defined literal for byte units.

/// User defined literal for byte units.
constexpr bytes operator""_bytes(unsigned long long n)
{
  return bytes(n);
}

/// User defined literal for bit units.

/// User defined literal for bit units.
constexpr bits operator""_bits(unsigned long long n)
{
  return bits(n);
}


} // namespace literals
} // namespace units
} // namespace ocudu


namespace fmt {

/// Formatter for bit units.

/// Formatter for bit units.
template <>
struct formatter<ocudu::units::bits> : public formatter<ocudu::units::bits::value_type> {
  template <typename FormatContext>
  auto format(ocudu::units::bits s, FormatContext& ctx) const
  {
    return fmt::format_to(ctx.out(), "{}{}", s.value(), ocudu::units::bits::tag_type::str());
  }
};

/// Formatter for byte units.

/// Formatter for byte units.
template <>
struct formatter<ocudu::units::bytes> : public formatter<ocudu::units::bytes::value_type> {
  bool print_units = false;


  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    auto it = ctx.begin();
    while (it != ctx.end() and *it != '}') {
      if (*it == 'B') {
        print_units = true;
      }
      ++it;
    }
    return it;
  }


  template <typename FormatContext>
  auto format(ocudu::units::bytes s, FormatContext& ctx) const
  {
    return fmt::format_to(ctx.out(), "{}{}", s.value(), print_units ? ocudu::units::bytes::tag_type::str() : "");
  }
};


} // namespace fmt
