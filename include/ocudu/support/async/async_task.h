// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/async_task.h  (75 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/detail/base_task.h"


namespace ocudu {

/// Lazy awaitable coroutine type that outputs a result of type R when completed.
/// \tparam R Result of the task

/// Lazy awaitable coroutine type that outputs a result of type R when completed.
/// \tparam R Result of the task
template <typename R>
class async_task : public detail::common_task_crtp<async_task<R>, R>
{
public:
  using result_type = R;


  struct promise_type : public detail::promise_data<result_type, detail::task_promise_base> {
    struct final_awaiter {
      /// Lifetime of coroutine is bounded to the lazy_task object.
      /// Lifetime of coroutine is bounded to the lazy_task object.
      bool await_ready() const { return false; }

      /// \brief Tail-resumes suspending/awaiting coroutine continuation.
      /// Lazy tasks always have a continuation, if they went beyond the initial suspension point.

      /// \brief Tail-resumes suspending/awaiting coroutine continuation.
      /// Lazy tasks always have a continuation, if they went beyond the initial suspension point.
      coro_handle<> await_suspend(coro_handle<promise_type> cb) { return cb.promise().continuation; }


      void await_resume() {}

      /// Points to itself as an awaiter.

      /// Points to itself as an awaiter.
      final_awaiter& get_awaiter() { return *this; }
    };

    /// Initial suspension awaiter. Lazy_tasks always suspend at initial suspension point.

    /// Initial suspension awaiter. Lazy_tasks always suspend at initial suspension point.
    suspend_always initial_suspend() { return {}; }

    /// Final suspension awaiter. Tail-resumes continuation.

    /// Final suspension awaiter. Tail-resumes continuation.
    final_awaiter final_suspend() { return {}; }


    [[nodiscard]] async_task<R> get_return_object()
    {
      auto corohandle = coro_handle<promise_type>::from_promise(this);
      corohandle.resume();
      return async_task<R>{corohandle};
    }
  };


  async_task() = default;
  explicit async_task(coro_handle<promise_type> cb) : handle(cb) {}

  /// Retrieve awaiter interface.

  /// Retrieve awaiter interface.
  async_task<R>& get_awaiter() { return *this; }

  /// \brief Register suspending coroutine as continuation of the current lazy_task. Tail-resumes "this" lazy_task.
  /// Called solely when "this" lazy_task is at initial suspension point.
  /// \param h suspending coroutine that is calling await_suspend.
  /// \return Coroutine handle to tail-resume.

  /// \brief Register suspending coroutine as continuation of the current lazy_task. Tail-resumes "this" lazy_task.
  /// Called solely when "this" lazy_task is at initial suspension point.
  /// \param h suspending coroutine that is calling await_suspend.
  /// \return Coroutine handle to tail-resume.
  coro_handle<> await_suspend(coro_handle<> h) noexcept
  {
    ocudu_sanity_check(not this->empty(), "Awaiting an empty task");
    ocudu_sanity_check(handle.promise().continuation.empty(), "Lazy task can only be awaited once.");

    // Store continuation in promise, so that it gets called at "this" coroutine final suspension point.

    // Store continuation in promise, so that it gets called at "this" coroutine final suspension point.
    handle.promise().continuation = h;

    // We tail-resume the current awaiter task's coroutine, which is currently suspended at initial suspension point.

    // We tail-resume the current awaiter task's coroutine, which is currently suspended at initial suspension point.
    return *handle;
  }


private:
  friend class detail::common_task_crtp<async_task<R>, R>;


  detail::unique_coroutine<promise_type> handle;
};


} // namespace ocudu
