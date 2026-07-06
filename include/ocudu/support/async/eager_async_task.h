// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/eager_async_task.h  (76 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/coroutine.h"
#include "ocudu/support/async/detail/base_task.h"


namespace ocudu {

/// Eager coroutine type that outputs a result of type R, when completed.
/// \tparam R Result of the task.

/// Eager coroutine type that outputs a result of type R, when completed.
/// \tparam R Result of the task.
template <typename R>
class eager_async_task : public detail::common_task_crtp<eager_async_task<R>, R>
{
public:
  using result_type = R;


  struct promise_type : public detail::promise_data<result_type, detail::task_promise_base> {
    /// base_task final awaiter type. It runs pending continuations and suspends.
    /// base_task final awaiter type. It runs pending continuations and suspends.
    struct final_awaiter {
      promise_type* me;


      bool await_ready() const { return false; }

      /// Tail-resumes continuation, if it was previously stored via an AWAIT call.
      /// \param h suspending coroutine.

      /// Tail-resumes continuation, if it was previously stored via an AWAIT call.
      /// \param h suspending coroutine.
      coro_handle<> await_suspend(coro_handle<promise_type> h)
      {
        return not me->continuation.empty() ? me->continuation : noop_coroutine();
      }


      void await_resume() {}

      /// Points to itself as an awaiter.

      /// Points to itself as an awaiter.
      final_awaiter& get_awaiter() { return *this; }
    };

    /// Initial suspension awaiter. Eager tasks never suspend at initial suspension point.

    /// Initial suspension awaiter. Eager tasks never suspend at initial suspension point.
    suspend_never initial_suspend() { return {}; }

    /// Final suspension awaiter.

    /// Final suspension awaiter.
    final_awaiter final_suspend() { return {this}; }


    [[nodiscard]] eager_async_task<R> get_return_object()
    {
      auto corohandle = coro_handle<promise_type>::from_promise(this);
      corohandle.resume();
      return eager_async_task<R>{corohandle};
    }
  };


  eager_async_task() = default;
  explicit eager_async_task(coro_handle<promise_type> cb) : handle(cb) {}

  /// Awaiter interface.

  /// Awaiter interface.
  eager_async_task<R>& get_awaiter() { return *this; }

  /// \brief Register suspending coroutine as continuation of the current async_task.
  ///
  /// Given that "this" task type is eager, it can be at any suspension point when await_suspend is called.
  /// \param h suspending coroutine that is calling await_suspend.

  /// \brief Register suspending coroutine as continuation of the current async_task.
  ///
  /// Given that "this" task type is eager, it can be at any suspension point when await_suspend is called.
  /// \param h suspending coroutine that is calling await_suspend.
  void await_suspend(coro_handle<> h) noexcept
  {
    ocudu_sanity_check(not this->empty(), "Awaiting an empty async_task");
    ocudu_sanity_check(handle.promise().continuation.empty(), "Async task can only be awaited once.");
    handle.promise().continuation = h;
  }


private:
  friend class detail::common_task_crtp<eager_async_task<R>, R>;


  detail::unique_coroutine<promise_type> handle;
};


} // namespace ocudu
