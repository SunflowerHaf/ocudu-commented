// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/support/tmpl_utils.h  (75 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <cstddef>
#include <cstdint>
#include <tuple>
#include <type_traits>


namespace ocudulog {


namespace detail {

///
/// Implementation of the std::index_sequence C++14 library utility.
///


///
/// Implementation of the std::index_sequence C++14 library utility.
///

template <std::size_t...>
struct index_sequence {};


template <std::size_t N, std::size_t... Next>
struct index_sequence_helper : public index_sequence_helper<N - 1U, N - 1U, Next...> {};


template <std::size_t... Next>
struct index_sequence_helper<0U, Next...> {
  using type = index_sequence<Next...>;
};


template <std::size_t N>
using make_index_sequence = typename index_sequence_helper<N>::type;

///
/// Implementation of the std::get<T> C++14 library utility.
///


///
/// Implementation of the std::get<T> C++14 library utility.
///

template <typename T, typename Tuple>
struct tuple_index;


template <typename T, typename... Ts>
struct tuple_index<T, std::tuple<T, Ts...>> {
  static constexpr std::size_t value = 0;
};


template <typename T, typename U, typename... Ts>
struct tuple_index<T, std::tuple<U, Ts...>> {
  static constexpr std::size_t value = 1 + tuple_index<T, std::tuple<Ts...>>::value;
};


template <typename T, typename... Ts>
constexpr std::size_t get_type_index_in_tuple()
{
  return tuple_index<T, std::tuple<Ts...>>::value;
}

///
/// Traits to restrict template parameter to iterators over uint8_t, e.g. for byte_buffer and friends.
///


///
/// Traits to restrict template parameter to iterators over uint8_t, e.g. for byte_buffer and friends.
///

template <typename...>
using void_t = void;


template <typename, typename = void>
struct is_byte_iterable : public std::false_type {};


template <typename T>
struct is_byte_iterable<
    T,
    void_t<decltype(++std::declval<T>()),
           typename std::enable_if<std::is_same<typename T::value_type, uint8_t>::value, int>::type>>
  : public std::true_type {};


} // namespace detail


} // namespace ocudulog
