// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/memory_pool/heap_memory_resource.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/support/ocudu_assert.h"
#include <memory>


namespace ocudu {


class heap_memory_resource
{
public:
  heap_memory_resource(size_t sz) : block(std::make_unique<uint8_t[]>(sz)), block_view(block.get(), sz)
  {
    ocudu_assert(block != nullptr, "Failed to allocate memory pool");
  }


  span<uint8_t> memory_block() const { return block_view; }


  size_t size() const { return block_view.size(); }


private:
  std::unique_ptr<uint8_t[]> block;
  span<uint8_t>              block_view;
};


} // namespace ocudu
