// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/support/byte_buffer_chain.cpp  (38 lines)
//
// LIBRARY: lib/support
// General-purpose C++ utilities: async task executors, thread pools, timer manager, memory pools, span/expected/bounded_integer types, signal dispatcher, config parsers, format helpers, synchronisation primitives (stop_event, sync_event), and versioning. Not 5G-specific — these could be a standalone C++ utility library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/adt/byte_buffer_chain.h"
#include "ocudu/adt/detail/byte_buffer_segment_pool.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/support/memory_pool/memory_pool_utils.h"


using namespace ocudu;


byte_buffer_chain::byte_buffer_chain(void* mem) :
  mem_block(mem),
  // Number of slices that fit in the memory block.
  // Number of slices that fit in the memory block.
  max_slices(detail::get_default_byte_buffer_segment_pool().memory_block_size() / sizeof(buffer_storage_type)),
  // Initialize slice array in the allocated memory block.
  // Initialize slice array in the allocated memory block.
  slices_ptr(static_cast<byte_buffer_slice*>(align_next(mem_block.get(), alignof(buffer_storage_type))))
{
  ocudu_assert(mem, "Invalid memory block");
}


expected<byte_buffer_chain> byte_buffer_chain::create()
{
  // Allocate memory block from pool for the array of slices.
  // Allocate memory block from pool for the array of slices.
  auto* mem_block = detail::get_default_byte_buffer_segment_pool().allocate_node();
  if (mem_block == nullptr) {
    ocudulog::fetch_basic_logger("ALL").warning("POOL: Failed to allocate memory block for byte_buffer_chain");
    return make_unexpected(default_error_t{});
  }


  return byte_buffer_chain{mem_block};
}


void byte_buffer_chain::block_deleter::operator()(void* p)
{
  if (p != nullptr) {
    detail::byte_buffer_segment_pool::get_instance().deallocate_node(p);
  }
}
