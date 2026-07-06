// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/task_redispatcher.h  (74 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/unique_function.h"
#include "ocudu/support/compiler.h"


namespace ocudu {

/// Executes a task n times, where "n" increases with the failures to dispatch the task.
/// Dispatches a task to an executor, and if it fails to dispatch (e.g. due to the task queue being full), it reattempts
/// on the next call.

/// Executes a task n times, where "n" increases with the failures to dispatch the task.
/// Dispatches a task to an executor, and if it fails to dispatch (e.g. due to the task queue being full), it reattempts
/// on the next call.
template <typename Executor>
class task_redispatcher
{
public:
  template <typename Exec, typename CallToExec>
  task_redispatcher(Exec&& executor_, CallToExec&& task) :
    executor(std::forward<Exec>(executor_)), dispatch_task(get_dispatch_task(std::forward<CallToExec>(task)))
  {
  }


  [[nodiscard]] bool execute()
  {
    if (not dispatch_task(true)) {
      dispatch_fail_count.fetch_add(1U, std::memory_order_relaxed);
      return false;
    }
    return true;
  }


  [[nodiscard]] bool defer()
  {
    if (not dispatch_task(false)) {
      dispatch_fail_count.fetch_add(1U, std::memory_order_relaxed);
      return false;
    }
    return true;
  }


private:
  template <typename CallToExec>
  void run_task_n_times(CallToExec& task)
  {
    // we invoke the "task" a number of times equal to "1 + failed dispatches"
    // we invoke the "task" a number of times equal to "1 + failed dispatches"
    task();
    uint32_t remaining_calls = dispatch_fail_count.load(std::memory_order_relaxed);
    while (remaining_calls > 0) {
      for (unsigned i = 0; i != remaining_calls; ++i) {
        task();
      }
      remaining_calls = dispatch_fail_count.fetch_sub(remaining_calls, std::memory_order_acq_rel) - remaining_calls;
    }
  }


  template <typename CallToExec>
  unique_function<bool(bool)> get_dispatch_task(CallToExec&& task)
  {
    return [this, t = std::forward<CallToExec>(task)](bool is_execute) {
      if (is_execute) {
        return executor.execute([this, &t]() { run_task_n_times(t); });
      }
      return executor.defer([this, &t]() { run_task_n_times(t); });
    };
  }


  Executor                    executor;
  unique_function<bool(bool)> dispatch_task;


  std::atomic<uint32_t> dispatch_fail_count{0};
};


} // namespace ocudu
