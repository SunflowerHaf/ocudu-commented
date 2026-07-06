// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/detail/type_storage.h  (61 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/compiler.h"
#include <cstddef>
#include <cstdint>
#include <new>
#include <type_traits>
#include <utility>


namespace ocudu {
namespace detail {

/// Helper class to store, construct, destruct and access an object stored in a memory buffer.
/// This class shouldn't be used outside of library code, as it is inherently unsafe.
/// \tparam T         Type of object stored.
/// \tparam MinSize   Lower bound for the embedded buffer size.
/// \tparam AlignSize Lower bound for the alignment of the embedded buffer.

/// Helper class to store, construct, destruct and access an object stored in a memory buffer.
/// This class shouldn't be used outside of library code, as it is inherently unsafe.
/// \tparam T         Type of object stored.
/// \tparam MinSize   Lower bound for the embedded buffer size.
/// \tparam AlignSize Lower bound for the alignment of the embedded buffer.
template <typename T, size_t MinSize = 0, size_t AlignSize = 0>
struct type_storage {
  using value_type = T;

  /// Emplace object in embedded buffer via ctor call T(Args&&...). UB if object was already created.

  /// Emplace object in embedded buffer via ctor call T(Args&&...). UB if object was already created.
  template <typename... Args>
  void emplace(Args&&... args) noexcept(std::is_nothrow_constructible_v<T, Args&&...>)
  {
    new (&buffer) T(std::forward<Args>(args)...);
  }
  /// Destroy object stored in embedded buffer. UB if object was not previously created.
  /// Destroy object stored in embedded buffer. UB if object was not previously created.
  void destroy() noexcept
  {
#ifndef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
    // Note: gcc12.2 gives a likely false alarm.
    // Note: gcc12.2 gives a likely false alarm.
    get().~T();
#ifndef __clang__
#pragma GCC diagnostic pop
#endif
  }

  /// Get created object handle. UB if object is not created.

  /// Get created object handle. UB if object is not created.
  T&       get() noexcept { return *std::launder(reinterpret_cast<T*>(buffer)); }
  const T& get() const noexcept { return *std::launder(reinterpret_cast<const T*>(buffer)); }


  void*       addr() noexcept { return static_cast<void*>(&buffer); }
  const void* addr() const noexcept { return static_cast<void*>(&buffer); }
  explicit    operator void*() noexcept { return addr(); }


  static constexpr size_t obj_size   = sizeof(T) > MinSize ? sizeof(T) : MinSize;
  static constexpr size_t align_size = alignof(T) > AlignSize ? alignof(T) : AlignSize;

  /// Embedded memory buffer.

  /// Embedded memory buffer.
  alignas(align_size) char buffer[obj_size];
};


} // namespace detail
} // namespace ocudu
