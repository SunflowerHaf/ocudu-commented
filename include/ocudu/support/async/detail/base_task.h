// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/detail/base_task.h  (71 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/detail/promise_data.h"
#include "ocudu/support/async/detail/unique_coroutine.h"


namespace ocudu {
namespace detail {


struct task_promise_base {
  /// True if the result of task has been stored.
  /// True if the result of task has been stored.
  bool has_value = false;
  /// Pending continuation task.
  /// Pending continuation task.
  coro_handle<> continuation;

  /// Check if return has been stored.

  /// Check if return has been stored.
  bool ready() const { return has_value; }
};

/// Common functionality to lazy and eager async tasks.

/// Common functionality to lazy and eager async tasks.
template <typename Derived, typename Result>
class common_task_crtp
{
public:
  using result_type = Result;

  /// Checks if async task has an handle.

  /// Checks if async task has an handle.
  bool empty() const { return derived().handle.empty(); }

  /// Returns true if base_task is complete.

  /// Returns true if base_task is complete.
  bool ready() const { return empty() or derived().handle.promise().ready(); }

  /// Called to get result of task once it is complete.

  /// Called to get result of task once it is complete.
  template <typename Res = std::decay_t<result_type>, std::enable_if_t<not std::is_same_v<Res, void>, bool> = true>
  const Res& get() const&
  {
    ocudu_assert(not empty() and derived().handle.promise().ready(), "Called task::get() for task that is not ready");
    return derived().handle.promise().get();
  }

  /// Called to get result of task once it is complete.

  /// Called to get result of task once it is complete.
  template <typename Res = std::decay_t<result_type>, std::enable_if_t<not std::is_same_v<Res, void>, bool> = true>
  Res get() &&
  {
    ocudu_assert(not empty() and derived().handle.promise().ready(), "Called task::get() for task that is not ready");
    return std::move(derived().handle.promise()).get();
  }

  /// Awaiter interface.

  /// Awaiter interface.
  bool await_ready() const noexcept { return derived().handle.empty() or derived().handle.promise().ready(); }
  template <typename Res = result_type>
  detail::enable_if_nonvoid<Res> await_resume()
  {
    ocudu_sanity_check(not empty(), "Resuming an empty base_task");
    return derived().handle.promise().get();
  }
  template <typename Res = result_type>
  detail::enable_if_void<Res> await_resume()
  {
    ocudu_sanity_check(not empty(), "Resuming an empty base_task");
  }


private:
  Derived&       derived() { return static_cast<Derived&>(*this); }
  const Derived& derived() const { return static_cast<const Derived&>(*this); }
};


} // namespace detail
} // namespace ocudu
