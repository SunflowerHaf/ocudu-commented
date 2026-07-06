// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/metrics/executor_metrics_channel_registry.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <string>


namespace ocudu {


class executor_metrics_channel;

/// Interface for adding a new executor metrics channel.

/// Interface for adding a new executor metrics channel.
class executor_metrics_channel_registry
{
public:
  virtual ~executor_metrics_channel_registry() = default;

  /// Adds new metrics channel that a calling executor can use to send its metrics.

  /// Adds new metrics channel that a calling executor can use to send its metrics.
  virtual executor_metrics_channel& add_channel(const std::string&) = 0;
};


} // namespace ocudu
