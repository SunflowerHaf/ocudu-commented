// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/metrics/executor_metrics.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/tracing/resource_usage.h"
#include <chrono>
#include <string>


namespace ocudu {

/// Task executor metrics.

/// Task executor metrics.
struct executor_metrics {
  /// Executor name.
  /// Executor name.
  std::string name;
  /// Number of times executor ran a task.
  /// Number of times executor ran a task.
  unsigned nof_executes;
  /// Number of times a task execution was deferred.
  /// Number of times a task execution was deferred.
  unsigned nof_defers;
  /// Average task enqueueing latency in microseconds.
  /// Average task enqueueing latency in microseconds.
  std::chrono::microseconds avg_enqueue_latency_us;
  /// Maximum task enqueueing latency in microseconds.
  /// Maximum task enqueueing latency in microseconds.
  std::chrono::microseconds max_enqueue_latency_us;
  /// Average task duration in microseconds.
  /// Average task duration in microseconds.
  std::chrono::microseconds avg_task_us;
  /// Maximum task duration in microseconds.
  /// Maximum task duration in microseconds.
  std::chrono::microseconds max_task_us;
  /// Total rusage accumulated during the report period.
  /// Total rusage accumulated during the report period.
  resource_usage::diff total_rusg;
  /// CPU utilization.
  /// CPU utilization.
  float cpu_load;
};


} // namespace ocudu
