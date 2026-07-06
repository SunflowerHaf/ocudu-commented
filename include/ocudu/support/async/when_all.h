// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/when_all.h  (191 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/async_task.h"
#include "ocudu/support/async/eager_async_task.h"
#include <memory>
#include <vector>


namespace ocudu {


namespace detail {

/// Join state owned by when_all_awaitable, referenced by all child wrappers.
/// Heap-allocated so its address stays stable when when_all_awaitable is moved into mem_buffer.

/// Join state owned by when_all_awaitable, referenced by all child wrappers.
/// Heap-allocated so its address stays stable when when_all_awaitable is moved into mem_buffer.
template <typename R>
struct when_all_context {
  explicit when_all_context(size_t n) : remaining(n), results(n) {}


  size_t         remaining;
  coro_handle<>  continuation;
  std::vector<R> results;
};

/// Void specialization: no result storage needed.

/// Void specialization: no result storage needed.
template <>
struct when_all_context<void> {
  explicit when_all_context(size_t n) : remaining(n) {}

  /// Decrements the counter and returns true if this is the last child to arrive.

  /// Decrements the counter and returns true if this is the last child to arrive.
  bool arrive() { return --remaining == 0; }


  size_t        remaining;
  coro_handle<> continuation;
};

/// Wrapper coroutine (eager): awaits one child task, stores its result, then decrements the join counter.
/// If this is the last child to finish, it sets its own continuation to the parent so that
/// final_suspend tail-resumes the parent - avoiding any inline reentrancy.

/// Wrapper coroutine (eager): awaits one child task, stores its result, then decrements the join counter.
/// If this is the last child to finish, it sets its own continuation to the parent so that
/// final_suspend tail-resumes the parent - avoiding any inline reentrancy.
template <typename R>
struct when_all_child_wrapper {
  when_all_child_wrapper(async_task<R>& task_, when_all_context<R>& ctx_, size_t idx_) :
    task(task_), ctx(ctx_), idx(idx_)
  {
  }


  async_task<R>&       task; // non-owning; owned by when_all_awaitable::child_tasks_
  when_all_context<R>& ctx;
  size_t               idx;


  void operator()(coro_context<eager_async_task<void>>& coro_ctx)
  {
    CORO_BEGIN(coro_ctx);
    CORO_AWAIT_VALUE(ctx.results[idx], task);
    if (--ctx.remaining == 0) {
      // Last child - tail-resume parent from our own final_suspend.
      // Last child - tail-resume parent from our own final_suspend.
      coro_context__.promise().continuation = ctx.continuation;
    }
    CORO_RETURN();
  }
};

/// Void specialization: no result to store; otherwise identical to the non-void wrapper.

/// Void specialization: no result to store; otherwise identical to the non-void wrapper.
template <>
struct when_all_child_wrapper<void> {
  when_all_child_wrapper(async_task<void>& task_, when_all_context<void>& ctx_) : task(task_), ctx(ctx_) {}


  async_task<void>&       task;
  when_all_context<void>& ctx;


  void operator()(coro_context<eager_async_task<void>>& coro_ctx)
  {
    CORO_BEGIN(coro_ctx);
    CORO_AWAIT(task);
    if (ctx.arrive()) {
      coro_context__.promise().continuation = ctx.continuation;
    }
    CORO_RETURN();
  }
};


} // namespace detail

/// \brief Awaitable that suspends the caller until all tasks in the input list complete.
///
/// All tasks are started eagerly at construction via a lightweight wrapper coroutine per child. Each
/// wrapper runs up to the child task's first I/O suspension. When the last wrapper finishes, it
/// tail-resumes the parent from final_suspend - so the parent is never resumed inline (no reentrancy
/// risk). Results are returned in the same order as the input tasks regardless of completion order.
/// An empty task list completes immediately: await_ready() returns true and the caller is not suspended.
///
/// Failure is not propagated via exceptions; each child task encodes success or failure in its return
/// value. The caller must inspect individual results after CORO_AWAIT.
///
/// \note Designed for single-threaded cooperative schedulers - no atomics or locks used.
/// \tparam R Result type of each task. Use the void specialization for tasks with no return value.

/// \brief Awaitable that suspends the caller until all tasks in the input list complete.
///
/// All tasks are started eagerly at construction via a lightweight wrapper coroutine per child. Each
/// wrapper runs up to the child task's first I/O suspension. When the last wrapper finishes, it
/// tail-resumes the parent from final_suspend - so the parent is never resumed inline (no reentrancy
/// risk). Results are returned in the same order as the input tasks regardless of completion order.
/// An empty task list completes immediately: await_ready() returns true and the caller is not suspended.
///
/// Failure is not propagated via exceptions; each child task encodes success or failure in its return
/// value. The caller must inspect individual results after CORO_AWAIT.
///
/// \note Designed for single-threaded cooperative schedulers - no atomics or locks used.
/// \tparam R Result type of each task. Use the void specialization for tasks with no return value.
template <typename R>
class when_all_awaitable
{
public:
  explicit when_all_awaitable(std::vector<async_task<R>> tasks) :
    ctx_(std::make_unique<detail::when_all_context<R>>(tasks.size())), child_tasks_(std::move(tasks))
  {
    wrappers_.reserve(child_tasks_.size());
    for (size_t i = 0; i < child_tasks_.size(); ++i) {
      // Eager launch: wrapper runs immediately up to its first CORO_AWAIT (child task's first I/O suspension).
      // Eager launch: wrapper runs immediately up to its first CORO_AWAIT (child task's first I/O suspension).
      wrappers_.push_back(launch_async<detail::when_all_child_wrapper<R>>(child_tasks_[i], *ctx_, i));
    }
  }


  when_all_awaitable(const when_all_awaitable&)            = delete;
  when_all_awaitable& operator=(const when_all_awaitable&) = delete;
  when_all_awaitable(when_all_awaitable&&)                 = default;
  when_all_awaitable& operator=(when_all_awaitable&&)      = default;


  when_all_awaitable& get_awaiter() { return *this; }

  /// Returns true if all tasks already completed synchronously during construction.

  /// Returns true if all tasks already completed synchronously during construction.
  bool await_ready() const noexcept { return ctx_->remaining == 0; }

  /// Stores the parent continuation. The last completing child will tail-resume it.

  /// Stores the parent continuation. The last completing child will tail-resume it.
  void await_suspend(coro_handle<> h) { ctx_->continuation = h; }

  /// Returns results in original task order. Inspect individual elements to detect per-task failures.

  /// Returns results in original task order. Inspect individual elements to detect per-task failures.
  std::vector<R> await_resume() { return std::move(ctx_->results); }


private:
  std::unique_ptr<detail::when_all_context<R>> ctx_;
  std::vector<async_task<R>>                   child_tasks_;
  std::vector<eager_async_task<void>>          wrappers_;
};

/// \brief Awaitable that suspends the caller until all void tasks in the input list complete.
///
/// Behaves identically to the non-void specialization except there is no result vector. Tasks are
/// started eagerly; the last to finish tail-resumes the parent from final_suspend. An empty task list
/// completes immediately without suspension.
///
/// \note Designed for single-threaded cooperative schedulers - no atomics or locks used.

/// \brief Awaitable that suspends the caller until all void tasks in the input list complete.
///
/// Behaves identically to the non-void specialization except there is no result vector. Tasks are
/// started eagerly; the last to finish tail-resumes the parent from final_suspend. An empty task list
/// completes immediately without suspension.
///
/// \note Designed for single-threaded cooperative schedulers - no atomics or locks used.
template <>
class when_all_awaitable<void>
{
public:
  explicit when_all_awaitable(std::vector<async_task<void>> tasks) :
    ctx_(std::make_unique<detail::when_all_context<void>>(tasks.size())), child_tasks_(std::move(tasks))
  {
    wrappers_.reserve(child_tasks_.size());
    for (size_t i = 0; i < child_tasks_.size(); ++i) {
      // Eager launch: wrapper runs immediately up to its first CORO_AWAIT (child task's first I/O suspension).
      // Eager launch: wrapper runs immediately up to its first CORO_AWAIT (child task's first I/O suspension).
      wrappers_.push_back(launch_async<detail::when_all_child_wrapper<void>>(child_tasks_[i], *ctx_));
    }
  }


  when_all_awaitable(const when_all_awaitable&)            = delete;
  when_all_awaitable& operator=(const when_all_awaitable&) = delete;
  when_all_awaitable(when_all_awaitable&&)                 = default;
  when_all_awaitable& operator=(when_all_awaitable&&)      = default;


  when_all_awaitable& get_awaiter() { return *this; }

  /// Returns true if all tasks already completed synchronously during construction.

  /// Returns true if all tasks already completed synchronously during construction.
  bool await_ready() const noexcept { return ctx_->remaining == 0; }

  /// Stores the parent continuation. The last completing child will tail-resume it.

  /// Stores the parent continuation. The last completing child will tail-resume it.
  void await_suspend(coro_handle<> h) { ctx_->continuation = h; }


  void await_resume() {}


private:
  std::unique_ptr<detail::when_all_context<void>> ctx_;
  std::vector<async_task<void>>                   child_tasks_;
  std::vector<eager_async_task<void>>             wrappers_;
};

/// \brief Run all tasks concurrently and collect results in the original input order.
///
/// Tasks are started eagerly and the caller suspends until the last one finishes. Results are returned
/// as std::vector<R> indexed by original task order. An empty task list completes immediately without
/// suspension. Failure is communicated through return values; inspect each element to determine
/// per-task success or failure. When R is void, no result vector is produced.
///
/// \param tasks Tasks to run in parallel. Ownership is transferred.
/// \return      Awaitable that yields std::vector<R> (or void when R is void).

/// \brief Run all tasks concurrently and collect results in the original input order.
///
/// Tasks are started eagerly and the caller suspends until the last one finishes. Results are returned
/// as std::vector<R> indexed by original task order. An empty task list completes immediately without
/// suspension. Failure is communicated through return values; inspect each element to determine
/// per-task success or failure. When R is void, no result vector is produced.
///
/// \param tasks Tasks to run in parallel. Ownership is transferred.
/// \return      Awaitable that yields std::vector<R> (or void when R is void).
template <typename R>
when_all_awaitable<R> when_all(std::vector<async_task<R>> tasks)
{
  return when_all_awaitable<R>{std::move(tasks)};
}


} // namespace ocudu
