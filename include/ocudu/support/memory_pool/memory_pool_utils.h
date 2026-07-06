// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/memory_pool/memory_pool_utils.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <cstdint>


namespace ocudu {

/// Checks if alignment is power of 2.

/// Checks if alignment is power of 2.
constexpr bool is_alignment_valid(std::size_t alignment)
{
  return alignment > 0 && (alignment & (alignment - 1U)) == 0U;
}

/// Checks whether the pointer is set with the correct alignment.

/// Checks whether the pointer is set with the correct alignment.
constexpr bool is_aligned(std::uintptr_t ptr, std::size_t alignment)
{
  return (ptr & (alignment - 1)) == 0;
}
inline bool is_aligned(void* ptr, std::size_t alignment)
{
  return is_aligned(reinterpret_cast<std::uintptr_t>(ptr), alignment);
}

/// \brief Moves the pointer by the given size in bytes.

/// \brief Moves the pointer by the given size in bytes.
constexpr void* advance_ptr(void* pos, std::size_t sz)
{
  return static_cast<char*>(pos) + sz;
}

/// Moves the pointer to the next aligned position.

/// Moves the pointer to the next aligned position.
constexpr std::uintptr_t align_next(std::uintptr_t pos, std::size_t alignment)
{
  return (pos + (alignment - 1)) & ~(alignment - 1);
}
inline void* align_next(void* pos, std::size_t alignment)
{
  return reinterpret_cast<void*>(align_next(reinterpret_cast<std::uintptr_t>(pos), alignment));
}


} // namespace ocudu
