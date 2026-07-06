// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/detail/unique_coroutine.h  (55 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/coroutine.h"
#include <utility>


namespace ocudu {
namespace detail {

/// Handle to coroutine object that ensures safe move ctor, move assignment and destruction.

/// Handle to coroutine object that ensures safe move ctor, move assignment and destruction.
template <typename Promise>
class unique_coroutine
{
public:
  using promise_type = Promise;


  unique_coroutine() = default;
  explicit unique_coroutine(coro_handle<promise_type> cb) : handle(cb) {}


  unique_coroutine(const unique_coroutine&)            = delete;
  unique_coroutine& operator=(const unique_coroutine&) = delete;
  unique_coroutine(unique_coroutine&& other) noexcept : handle(std::exchange(other.handle, nullptr)) {}
  unique_coroutine& operator=(unique_coroutine&& other) noexcept
  {
    if (not handle.empty()) {
      handle.destroy();
    }
    handle = std::exchange(other.handle, nullptr);
    return *this;
  }


  ~unique_coroutine()
  {
    if (not handle.empty()) {
      handle.destroy();
    }
  }


  coro_handle<promise_type>& operator*() { return handle; }


  bool empty() const { return handle.empty(); }


  void resume() { handle.resume(); }


  promise_type&       promise() { return handle.promise(); }
  const promise_type& promise() const { return handle.promise(); }


private:
  coro_handle<promise_type> handle;
};


} // namespace detail
} // namespace ocudu
