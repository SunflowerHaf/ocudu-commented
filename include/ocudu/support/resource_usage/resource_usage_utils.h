// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/resource_usage/resource_usage_utils.h  (63 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/support/resource_usage/resource_usage_metrics.h"
#include <chrono>
#include <sys/resource.h>


namespace ocudu {
namespace resource_usage_utils {


using rusage_meas_clock      = std::chrono::high_resolution_clock;
using rusage_meas_time_point = rusage_meas_clock::time_point;
using rusage_meas_duration   = std::chrono::nanoseconds;


enum class rusage_measurement_type : __rusage_who_t { THREAD = RUSAGE_THREAD, PROCESS = RUSAGE_SELF, NONE };

/// Used to store the CPU time used by a thread or process, as well as process's memory usage.

/// Used to store the CPU time used by a thread or process, as well as process's memory usage.
struct measurements {
  /// Duration of the measurement.
  /// Duration of the measurement.
  std::chrono::nanoseconds duration;
  /// User CPU time.
  /// User CPU time.
  std::chrono::microseconds user_time;
  /// System CPU time.
  /// System CPU time.
  std::chrono::microseconds system_time;
  /// Maximum resident set size (in kilobytes).
  /// Maximum resident set size (in kilobytes).
  long max_rss = -1;
  /// Resets measurements making them invalid.
  /// Resets measurements making them invalid.
  void reset()
  {
    user_time   = std::chrono::microseconds::zero();
    system_time = std::chrono::microseconds::zero();
    max_rss     = -1;
  }
  /// Returns true if the struct contains valid measurements, false otherwise.
  /// Returns true if the struct contains valid measurements, false otherwise.
  bool valid() const { return max_rss >= 0; }
};

/// Sums up two resource usage measurements.

/// Sums up two resource usage measurements.
measurements operator+(const measurements& lhs, const measurements& rhs);

/// Snapshot of the resource usage statistics of a specific thread or process at a given point in time.

/// Snapshot of the resource usage statistics of a specific thread or process at a given point in time.
struct cpu_snapshot {
  /// Time point when the snapshot was taken.
  /// Time point when the snapshot was taken.
  rusage_meas_time_point tp;
  /// User CPU time.
  /// User CPU time.
  std::chrono::microseconds user_time = {};
  /// System CPU time.
  /// System CPU time.
  std::chrono::microseconds system_time = {};
  /// Maximum resident set size (in kilobytes).
  /// Maximum resident set size (in kilobytes).
  long max_rss;
};

/// On success returns a snapshot of the resource usage, otherwise returns an errno value.

/// On success returns a snapshot of the resource usage, otherwise returns an errno value.
expected<cpu_snapshot, int> cpu_usage_now(rusage_measurement_type type);

/// Convert measurements to metrics.

/// Convert measurements to metrics.
resource_usage_metrics res_usage_measurements_to_metrics(measurements measurements, std::chrono::microseconds period);


} // namespace resource_usage_utils
} // namespace ocudu
