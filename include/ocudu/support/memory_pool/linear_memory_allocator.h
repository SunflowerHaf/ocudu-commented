// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/memory_pool/linear_memory_allocator.h  (44 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/memory_pool/memory_pool_utils.h"
#include "ocudu/support/ocudu_assert.h"
#include <cstdint>


namespace ocudu {

/// \brief Linear allocator for a contiguous memory block.
///
/// This type of allocator doesn't provide a deallocation mechanism.

/// \brief Linear allocator for a contiguous memory block.
///
/// This type of allocator doesn't provide a deallocation mechanism.
class linear_memory_allocator
{
public:
  linear_memory_allocator(void* memory_resource, std::size_t memory_resource_size) :
    mem_start(static_cast<uint8_t*>(memory_resource)), mem_res_size(memory_resource_size)
  {
    ocudu_sanity_check(mem_start != nullptr and mem_res_size != 0, "Invalid memory resource");
  }


  std::size_t size() const { return mem_res_size; }
  std::size_t nof_bytes_left() const { return mem_res_size - mem_offset; }
  std::size_t nof_bytes_allocated() const { return mem_offset; }


  void* memory_resource_start() const { return mem_start; }


  void* allocate(std::size_t sz, std::size_t al) noexcept
  {
    void* p    = align_next(mem_start + mem_offset, al);
    mem_offset = (static_cast<uint8_t*>(p) - mem_start) + sz;
    ocudu_sanity_check(mem_offset <= mem_res_size, "Out of memory");
    return p;
  }


private:
  uint8_t*    mem_start;
  std::size_t mem_res_size;
  std::size_t mem_offset = 0;
};


} // namespace ocudu
