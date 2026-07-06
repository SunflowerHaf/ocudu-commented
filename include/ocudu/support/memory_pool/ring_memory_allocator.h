// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/memory_pool/ring_memory_allocator.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/memory_pool/heap_memory_resource.h"
#include "ocudu/support/ocudu_assert.h"


namespace ocudu {

/// \brief This memory allocator allocates chunks of a contiguous memory region in a circular fashion.

/// \brief This memory allocator allocates chunks of a contiguous memory region in a circular fashion.
class ring_memory_allocator
{
public:
  explicit ring_memory_allocator(span<uint8_t> mem_block_) : mem_block(mem_block_) {}


  void* allocate(size_t sz) noexcept
  {
    ocudu_assert(sz <= mem_block.size(), "Invalid allocation size ({} > {})", sz, mem_block.size());


    if (next_offset + sz > mem_block.size()) {
      // Wrap-around.
      // Wrap-around.
      next_offset = sz;
      return mem_block.data();
    } else {
      uint8_t* ptr = mem_block.data() + next_offset;
      next_offset += sz;
      return ptr;
    }
  }


  void deallocate(void* p) noexcept
  {
    ocudu_assert(static_cast<uint8_t*>(p) - mem_block.data() < (ssize_t)mem_block.size(),
                 "Deallocating invalid memory pointer");
  }


private:
  size_t        next_offset = 0;
  span<uint8_t> mem_block;
};


} // namespace ocudu
