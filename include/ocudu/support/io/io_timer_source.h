// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/io/io_timer_source.h  (53 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/io/io_broker.h"
#include "ocudu/support/synchronization/sync_event.h"


namespace ocudu {


class timer_manager;

/// \brief Interface for a timer source.

/// \brief Interface for a timer source.
class io_timer_source
{
public:
  io_timer_source(timer_manager&            tick_sink_,
                  io_broker&                broker_,
                  task_executor&            executor,
                  std::chrono::milliseconds tick_period,
                  bool                      auto_start = true);
  ~io_timer_source();

  /// Resume ticking in case it was previously halted.

  /// Resume ticking in case it was previously halted.
  void resume();

  /// \brief Request the timer source to stop ticking.
  /// Note: This call does not block, so a tick might take place after this call.

  /// \brief Request the timer source to stop ticking.
  /// Note: This call does not block, so a tick might take place after this call.
  void request_stop();


private:
  void create_subscriber(scoped_sync_token token);
  void destroy_subscriber(scoped_sync_token& token);


  void read_time(int raw_fd, scoped_sync_token& token);


  const std::chrono::milliseconds tick_period;
  timer_manager&                  tick_sink;
  io_broker&                      broker;
  task_executor&                  tick_exec;
  ocudulog::basic_logger&         logger;
  io_broker::subscriber           io_sub;

  // Current state of the timer source.

  // Current state of the timer source.
  std::atomic<bool> running{false};

  // Synchronization primitive to stop the timer source.
  // Note: shutdown_flag.reset() is only called during io_timer_source destruction. Do not confuse it with stop/resume
  // of the timer.

  // Synchronization primitive to stop the timer source.
  // Note: shutdown_flag.reset() is only called during io_timer_source destruction. Do not confuse it with stop/resume
  // of the timer.
  sync_event shutdown_flag;
};


} // namespace ocudu
