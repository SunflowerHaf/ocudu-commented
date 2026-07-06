// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/circular_vector.h  (58 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/static_vector.h"
#include <vector>


namespace ocudu {

/// \brief Circular vector container.
/// \tparam T Type of elements.
/// \tparam VectorContainer Underlying vector implementation. Must provide the same interface as std::vector.

/// \brief Circular vector container.
/// \tparam T Type of elements.
/// \tparam VectorContainer Underlying vector implementation. Must provide the same interface as std::vector.
template <typename T, typename VectorContainer = std::vector<T>>
class circular_vector
{
public:
  using value_type     = T;
  using iterator       = typename VectorContainer::iterator;
  using const_iterator = typename VectorContainer::const_iterator;


  circular_vector() = default;
  circular_vector(size_t n) : data(n) {}
  circular_vector(size_t n, const T& value) : data(n, value) {}


  auto begin() { return data.begin(); }
  auto begin() const { return data.begin(); }
  auto end() { return data.end(); }
  auto end() const { return data.end(); }


  size_t size() const { return data.size(); }
  bool   empty() const { return data.empty(); }


  T&       operator[](size_t pos) { return data[pos % size()]; }
  const T& operator[](size_t pos) const { return data[pos % size()]; }


  void resize(size_t n) { data.resize(n); }
  void resize(size_t n, const T& value) { data.resize(n, value); }


  void reserve(size_t n) { data.reserve(n); }
  void push_back(const T& value) { data.push_back(value); }
  void push_back(T&& value) { data.push_back(std::move(value)); }
  template <typename... Args>
  void emplace_back(Args&&... args)
  {
    data.emplace_back(std::forward<Args>(args)...);
  }


  void clear() { data.clear(); }


private:
  VectorContainer data;
};


template <typename T, size_t N>
using static_circular_vector = circular_vector<T, static_vector<T, N>>;


} // namespace ocudu
