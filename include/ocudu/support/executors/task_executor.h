// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/task_executor.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/unique_function.h"


namespace ocudu {


class task_executor
{
public:
  virtual ~task_executor() = default;

  /// Dispatches a task to be executed. According to this policy, executor may invoke task inplace if it deemed safe
  /// to do so.

  /// Dispatches a task to be executed. According to this policy, executor may invoke task inplace if it deemed safe
  /// to do so.
  [[nodiscard]] virtual bool execute(unique_task task) = 0;

  /// Dispatches a task to be later executed. The task always gets enqueued for later invocation.

  /// Dispatches a task to be later executed. The task always gets enqueued for later invocation.
  [[nodiscard]] virtual bool defer(unique_task task) = 0;
};


} // namespace ocudu
