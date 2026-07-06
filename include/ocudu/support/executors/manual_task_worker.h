// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/manual_task_worker.h  (118 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/blocking_queue.h"
#include "ocudu/support/executors/task_executor.h"


namespace ocudu {

/// \brief Task worker that implements the executor interface and requires manual calls to run pending deferred tasks.
/// Useful for unit testing.

/// \brief Task worker that implements the executor interface and requires manual calls to run pending deferred tasks.
/// Useful for unit testing.
class manual_task_worker : public task_executor
{
public:
  manual_task_worker(size_t q_size, bool blocking_mode_ = true, bool explicit_mode_ = false) :
    t_id(std::this_thread::get_id()),
    pending_tasks(q_size),
    blocking_mode(blocking_mode_),
    explicit_mode(explicit_mode_)
  {
  }


  std::thread::id get_thread_id() const { return t_id; }


  [[nodiscard]] bool execute(unique_task task) override
  {
    if (std::this_thread::get_id() == t_id and not explicit_mode) {
      task();
      return true;
    }
    return defer(std::move(task));
  }


  [[nodiscard]] bool defer(unique_task task) override
  {
    if (blocking_mode) {
      pending_tasks.push_blocking(std::move(task));
      return true;
    }
    return pending_tasks.try_push(std::move(task)).has_value();
  }


  size_t max_pending_tasks() const { return pending_tasks.max_size(); }


  bool has_pending_tasks() const { return not pending_tasks.empty(); }


  bool is_stopped() const { return pending_tasks.is_stopped(); }


  void stop()
  {
    if (not is_stopped()) {
      pending_tasks.stop();
    }
  }


  void request_stop()
  {
    (void)defer([this]() { stop(); });
  }

  /// Run all pending tasks until queue is emptied.

  /// Run all pending tasks until queue is emptied.
  bool run_pending_tasks()
  {
    assert_thread_id();
    bool ret = false, success = false;
    do {
      unique_task t;
      success = pending_tasks.try_pop(t);
      if (success) {
        t();
        ret = true;
      }
    } while (success);
    return ret;
  }

  /// Run next pending task if it is enqueued.

  /// Run next pending task if it is enqueued.
  bool try_run_next()
  {
    assert_thread_id();
    unique_task t;
    bool        success = pending_tasks.try_pop(t);
    if (not success) {
      return false;
    }
    t();
    return true;
  }

  /// Run next pending task once it is enqueued.

  /// Run next pending task once it is enqueued.
  bool run_next_blocking()
  {
    assert_thread_id();
    bool        success = false;
    unique_task t       = pending_tasks.pop_blocking(&success);
    if (not success) {
      return false;
    }
    t();
    return true;
  }


private:
  bool has_thread_id() const { return t_id != std::thread::id{}; }


  void assert_thread_id()
  {
    ocudu_assert(t_id == std::this_thread::get_id(), "run() caller thread should not change.");
  }


  std::thread::id             t_id;
  blocking_queue<unique_task> pending_tasks;
  bool                        blocking_mode;
  bool                        explicit_mode;
};


} // namespace ocudu
