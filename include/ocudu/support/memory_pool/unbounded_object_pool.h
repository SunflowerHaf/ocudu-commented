// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/memory_pool/unbounded_object_pool.h  (71 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#ifdef ENABLE_TSAN
#include <sanitizer/tsan_interface.h>
#endif


#include "cameron314/concurrentqueue.h"
#include <memory>


namespace ocudu {

/// Unbounded, thread-safe object pool. Ideal for large objects. Use with caution.

/// Unbounded, thread-safe object pool. Ideal for large objects. Use with caution.
template <typename T>
class unbounded_object_pool
{
  struct pool_deleter {
    pool_deleter() = default;
    pool_deleter(unbounded_object_pool& parent_) : parent(&parent_) {}
    void operator()(T* ptr)
    {
      if (ptr != nullptr) {
        std::unique_ptr<T> obj{ptr};
#ifdef ENABLE_TSAN
        __tsan_release((void*)obj.get());
#endif
        parent->objects.enqueue(std::move(obj));
      }
    }


    unbounded_object_pool* parent;
  };


public:
  using ptr = std::unique_ptr<T, pool_deleter>;


  unbounded_object_pool(unsigned initial_capacity) : objects(initial_capacity)
  {
    for (unsigned i = 0; i != initial_capacity; ++i) {
      objects.enqueue(std::make_unique<T>());
    }
  }
  unbounded_object_pool(unsigned initial_capacity, unsigned expected_nof_deallocation_contexts) :
    objects(initial_capacity, 0, expected_nof_deallocation_contexts)
  {
    for (unsigned i = 0; i != initial_capacity; ++i) {
      objects.enqueue(std::make_unique<T>());
    }
  }


  ptr get()
  {
    std::unique_ptr<T> popped;
    if (objects.try_dequeue(popped)) {
#ifdef ENABLE_TSAN
      __tsan_acquire((void*)popped.get());
#endif
      return ptr{popped.release(), pool_deleter{*this}};
    }
    return ptr{new T(), pool_deleter{*this}};
  }


  unsigned current_capacity_approx() const { return objects.size_approx(); }


private:
  moodycamel::ConcurrentQueue<std::unique_ptr<T>> objects;
};


} // namespace ocudu
