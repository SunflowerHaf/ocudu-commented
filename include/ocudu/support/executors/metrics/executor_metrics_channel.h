// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/metrics/executor_metrics_channel.h  (79 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/lockfree_triple_buffer.h"
#include "ocudu/support/executors/metrics/executor_metrics.h"
#include "ocudu/support/executors/unique_thread.h"
#include "ocudu/support/tracing/resource_usage.h"
#include <chrono>
#include <vector>


namespace ocudu {

/// \brief Executor metrics channel allows a task executor to pass its metrics to the backend.
///
/// On a request from the metrics backend the saved metrics are aggregated among different threads and forwarded to the
/// backend.

/// \brief Executor metrics channel allows a task executor to pass its metrics to the backend.
///
/// On a request from the metrics backend the saved metrics are aggregated among different threads and forwarded to the
/// backend.
class executor_metrics_channel
{
  /// Metrics aggregated over a reporting period.
  /// Metrics aggregated over a reporting period.
  struct aggregated_metrics {
    uint64_t                 count             = 0;
    uint64_t                 total_exec_count  = 0;
    uint64_t                 total_defer_count = 0;
    std::chrono::nanoseconds total_enqueue_latency{0};
    std::chrono::nanoseconds total_task_latency{0};
    std::chrono::nanoseconds max_enqueue_latency{0};
    std::chrono::nanoseconds max_task_latency{0};
    resource_usage::diff     accumulated_rusg = {};
  };

  /// Per thread executor metrics.

  /// Per thread executor metrics.
  struct executor_thread_metrics {
    /// Aggregated metrics available for the backend to read.
    /// Aggregated metrics available for the backend to read.
    lockfree_triple_buffer<aggregated_metrics> metrics;
    /// Local copy of aggregated metrics.
    /// Local copy of aggregated metrics.
    aggregated_metrics temp_aggr_metrics;
    /// Atomic flag set by the backend when aggregated metrics must be reset.
    /// Atomic flag set by the backend when aggregated metrics must be reset.
    std::atomic<bool> reset_flag{false};
  };


public:
  /// Metrics of an executed task.
  /// Metrics of an executed task.
  struct executed_task_metrics {
    uint64_t                 exec_count  = 0;
    uint64_t                 defer_count = 0;
    std::chrono::nanoseconds enqueue_latency{0};
    std::chrono::nanoseconds task_latency{0};
    resource_usage::diff     rusg = {};
  };

  /// Constructor initializes internal storage for the maximum supported number of threads.

  /// Constructor initializes internal storage for the maximum supported number of threads.
  explicit executor_metrics_channel(const std::string& name_) :
    name(name_),
    threads_metrics(unique_thread::get_max_nof_supported_threads()),
    last_tp(std::chrono::steady_clock::now())
  {
  }

  /// Update metrics associated with the calling thread.

  /// Update metrics associated with the calling thread.
  void update(const executed_task_metrics& new_metrics);

  /// Reads aggregated metrics.

  /// Reads aggregated metrics.
  executor_metrics read();


private:
  /// Helper method for updating provided aggregated metrics with the new metrics.
  /// Helper method for updating provided aggregated metrics with the new metrics.
  void update_metrics(aggregated_metrics& stored, const executed_task_metrics& new_metrics);

  /// Executor name.

  /// Executor name.
  std::string name;
  /// Vector of executor metrics associated with each thread.
  /// Vector of executor metrics associated with each thread.
  std::vector<executor_thread_metrics> threads_metrics;
  /// Last read timestamp.
  /// Last read timestamp.
  std::chrono::time_point<std::chrono::steady_clock> last_tp;
};


} // namespace ocudu
