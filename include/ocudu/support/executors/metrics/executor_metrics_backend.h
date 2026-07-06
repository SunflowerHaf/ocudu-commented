// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/metrics/executor_metrics_backend.h  (64 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/executors/metrics/executor_metrics_channel.h"
#include "ocudu/support/executors/metrics/executor_metrics_channel_registry.h"
#include "ocudu/support/synchronization/stop_event.h"
#include "ocudu/support/timers.h"
#include <chrono>
#include <memory>
#include <mutex>


namespace ocudu {


class executor_metrics_notifier;

/// \brief Executor metrics backend.
///
/// This class is responsible for handling metrics produced by different executors.
/// An executor registers itself in the backend by getting a unique metrics channel.

/// \brief Executor metrics backend.
///
/// This class is responsible for handling metrics produced by different executors.
/// An executor registers itself in the backend by getting a unique metrics channel.
class executor_metrics_backend : public executor_metrics_channel_registry
{
  enum class worker_status { running, stopped };


public:
  executor_metrics_backend() = default;
  ~executor_metrics_backend() override;

  /// Delete copy and move constructors, a single object is used application-wise.

  /// Delete copy and move constructors, a single object is used application-wise.
  executor_metrics_backend(const executor_metrics_backend& other)            = delete;
  executor_metrics_backend(executor_metrics_backend&& other)                 = delete;
  executor_metrics_backend& operator=(const executor_metrics_backend& other) = delete;
  executor_metrics_backend& operator=(executor_metrics_backend&& other)      = delete;

  // See interface for documentation.

  // See interface for documentation.
  executor_metrics_channel& add_channel(const std::string& exec_name) override;

  /// Stops periodic metrics reporting. This method is blocking.

  /// Stops periodic metrics reporting. This method is blocking.
  void stop();

  /// Start the backend worker using the passed timer and periodically report metrics to the given notifier object.

  /// Start the backend worker using the passed timer and periodically report metrics to the given notifier object.
  void start(std::chrono::milliseconds period_, unique_timer timer_, executor_metrics_notifier& notifier_);


private:
  /// Periodic work done by this backend.
  /// Every report period it notifies the new metrics obtained from the channels.
  /// Periodic work done by this backend.
  /// Every report period it notifies the new metrics obtained from the channels.
  void fetch_metrics();

  /// Metrics report period.

  /// Metrics report period.
  std::chrono::milliseconds period;
  /// Periodic timer.
  /// Periodic timer.
  unique_timer timer;
  /// An interface to a metrics handler.
  /// An interface to a metrics handler.
  executor_metrics_notifier* notifier = nullptr;
  /// Stop control.
  /// Stop control.
  stop_event_source stop_control;

  /// List of metrics channels.

  /// List of metrics channels.
  std::mutex                                             mutex;
  std::vector<std::unique_ptr<executor_metrics_channel>> channels;
};


} // namespace ocudu
