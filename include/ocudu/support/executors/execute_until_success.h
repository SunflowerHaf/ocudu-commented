// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/execute_until_success.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/timers.h"


namespace ocudu {

/// Execute task in the given task executor. If dispatch fails, postpone execution via timers.
///
/// This function is useful for tasks whose dispatch can never fail.

/// Execute task in the given task executor. If dispatch fails, postpone execution via timers.
///
/// This function is useful for tasks whose dispatch can never fail.
template <typename TaskExecutor, typename CopyableTask>
void execute_until_success(TaskExecutor& exec, timer_manager& timers, CopyableTask&& task)
{
  static_assert(std::is_copy_constructible_v<CopyableTask>, "CopyableTask must be copyable");

  // Try to dispatch right away.

  // Try to dispatch right away.
  if (not exec.execute(task)) {
    // If it fails, resort to timers.
    // If it fails, resort to timers.
    auto timer = timers.create_unique_timer(exec);
    timer.set(timer_duration{0}, [task](timer_id_t tid) mutable { task(); });
    timer.run();
  }
}

/// Defer task in the given task executor. If dispatch fails, postpone defer.
///
/// This function is useful for tasks whose dispatch can never fail.

/// Defer task in the given task executor. If dispatch fails, postpone defer.
///
/// This function is useful for tasks whose dispatch can never fail.
template <typename TaskExecutor, typename CopyableTask>
void defer_until_success(TaskExecutor& exec, timer_manager& timers, CopyableTask&& task)
{
  static_assert(std::is_copy_constructible_v<CopyableTask>, "CopyableTask must be copyable");

  // Try to dispatch right away.

  // Try to dispatch right away.
  if (not exec.defer(task)) {
    // If it fails, resort to timers.
    // If it fails, resort to timers.
    auto timer = timers.create_unique_timer(exec);
    timer.set(timer_duration{0}, [task](timer_id_t tid) mutable { task(); });
    timer.run();
  }
}


} // namespace ocudu
