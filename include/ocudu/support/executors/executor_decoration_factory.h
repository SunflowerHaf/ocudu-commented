// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/executor_decoration_factory.h  (64 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/executors/detail/task_executor_utils.h"
#include "ocudu/support/tracing/event_tracing.h"
#include <chrono>
#include <memory>
#include <optional>
#include <string>


namespace ocudu {


class executor_metrics_channel_registry;

/// Description of the decorators to be applied to an executor.

/// Description of the decorators to be applied to an executor.
struct execution_decoration_config {
  struct sync_option {};
  struct throttle_option {
    /// Number of tasks pending after which the caller to the executor starts being throttled.
    /// Number of tasks pending after which the caller to the executor starts being throttled.
    unsigned nof_task_threshold;
  };
  struct trace_option {
    /// Name of the executor to be traced.
    /// Name of the executor to be traced.
    std::string name;
  };
  struct metrics_option {
    /// Name of the executor for which metrics are to be reported.
    /// Name of the executor for which metrics are to be reported.
    std::string name;
    /// Executor metrics channel registry.
    /// Executor metrics channel registry.
    executor_metrics_channel_registry& channel_registry;
    /// Whether to use metric captures for tracing.
    /// Whether to use metric captures for tracing.
    bool tracing_enabled = false;
    /// Tracer.
    /// Tracer.
    file_event_tracer<true>* tracer = nullptr;


    metrics_option(std::string                        name_,
                   executor_metrics_channel_registry& channel_registry_,
                   bool                               tracing_enabled_,
                   file_event_tracer<true>*           tracer_ = nullptr) :
      name(std::move(name_)), channel_registry(channel_registry_), tracing_enabled(tracing_enabled_), tracer(tracer_)
    {
    }
  };

  /// If set, the executor will block the caller until the task is executed.

  /// If set, the executor will block the caller until the task is executed.
  std::optional<sync_option> sync;
  /// \brief If set, the executor will throttle the execute/defer caller if the number of pending tasks exceeds the
  /// specified threshold.
  /// \brief If set, the executor will throttle the execute/defer caller if the number of pending tasks exceeds the
  /// specified threshold.
  std::optional<throttle_option> throttle;
  /// \brief If set, the executor will collect metrics on the task execution latencies.
  /// \remark This decorator should be only used with sequential executors (e.g. strands, single threads).
  /// \brief If set, the executor will collect metrics on the task execution latencies.
  /// \remark This decorator should be only used with sequential executors (e.g. strands, single threads).
  std::optional<metrics_option> metrics;
  /// If set, the executor will trace the task execution latencies using the specified tracer.
  /// If set, the executor will trace the task execution latencies using the specified tracer.
  std::optional<trace_option> trace;
};

/// \brief Creates an executor decorator that applies the specified policies to the given executor.

/// \brief Creates an executor decorator that applies the specified policies to the given executor.
std::unique_ptr<task_executor> decorate_executor(std::unique_ptr<task_executor>     exec,
                                                 const execution_decoration_config& config);
std::unique_ptr<task_executor> decorate_executor(task_executor& exec, const execution_decoration_config& config);


} // namespace ocudu
