// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/to_array.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <array>


namespace ocudu {


namespace detail {


template <class T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array_impl(T (&a)[N], std::index_sequence<I...>)
{
  return {{a[I]...}};
}


template <class T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array_impl(T (&&a)[N], std::index_sequence<I...>)
{
  return {{std::move(a[I])...}};
}


template <class T, std::size_t N, class Factory, std::size_t... Is>
constexpr std::array<T, N> make_array_impl(const Factory& factory, std::index_sequence<Is...> /* unused */)
{
  return {{factory(Is)...}};
}


} // namespace detail

/// Helper method to generate an std::array from a C array without needing to derive the size N.

/// Helper method to generate an std::array from a C array without needing to derive the size N.
template <class T, std::size_t N>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N])
{
  return detail::to_array_impl(a, std::make_index_sequence<N>{});
}
template <class T, std::size_t N>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&&a)[N])
{
  return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}

/// Helper method to generate an std::array using an array-element factory.

/// Helper method to generate an std::array using an array-element factory.
template <class T, std::size_t N, class Factory>
constexpr std::array<T, N> make_array(const Factory& factory)
{
  return detail::make_array_impl<T, N>(factory, std::make_index_sequence<N>());
}


} // namespace ocudu
