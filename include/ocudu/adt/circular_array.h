// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/circular_array.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <array>
#include <cstddef>


namespace ocudu {

/// \brief Helper class to safely access elements of a std::array.
///
/// Protects from out-of-bounds access by applying modulo of its length when using the [] operator for element access.

/// \brief Helper class to safely access elements of a std::array.
///
/// Protects from out-of-bounds access by applying modulo of its length when using the [] operator for element access.
template <typename T, std::size_t N>
class circular_array
{
  std::array<T, N> data;


public:
  using iterator       = T*;
  using const_iterator = const T*;


  circular_array() = default;
  circular_array(const T& value) { data.fill(value); }


  T&       operator[](std::size_t pos) { return data[pos % N]; }
  const T& operator[](std::size_t pos) const { return data[pos % N]; }


  T*       begin() { return data.begin(); }
  const T* begin() const { return data.begin(); }


  T*       end() { return data.end(); }
  const T* end() const { return data.end(); }


  size_t size() const { return N; }
};


} // namespace ocudu
