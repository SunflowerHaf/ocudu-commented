// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/expected.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "TartanLlama/expected.hpp"


namespace ocudu {


struct default_error_t {};
struct default_success_t {};


template <typename E>
using unexpected = tl::unexpected<E>;


template <typename E>
unexpected<std::decay_t<E>> make_unexpected(E&& e)
{
  return unexpected<std::decay_t<E>>(std::forward<E>(e));
}


template <typename T = default_success_t, typename E = default_error_t>
using expected = tl::expected<T, E>;


namespace detail {
template <typename T>
struct is_expected : std::false_type {};
template <typename V, typename E>
struct is_expected<expected<V, E>> : std::true_type {};
} // namespace detail


template <typename E>
using error_type = expected<default_success_t, E>;


} // namespace ocudu
