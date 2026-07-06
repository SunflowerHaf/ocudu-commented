// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/async_timer.h  (48 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/coroutine.h"
#include "ocudu/support/timers.h"


namespace ocudu {

/// \brief Returns an awaitable object that is only ready when the passed duration_msec has elapsed.
///
/// \param timer unique_timer object that is used to set the duration and timeout callback.
/// \param duration_msec duration in msec until the timer gets triggered.
/// \return awaitable object which returns true on resume if timer was notify_stop, and false if it expired.

/// \brief Returns an awaitable object that is only ready when the passed duration_msec has elapsed.
///
/// \param timer unique_timer object that is used to set the duration and timeout callback.
/// \param duration_msec duration in msec until the timer gets triggered.
/// \return awaitable object which returns true on resume if timer was notify_stop, and false if it expired.
template <typename UniqueTimer>
[[nodiscard]] auto async_wait_for(UniqueTimer&& timer, std::chrono::milliseconds duration_msec)
{
  class async_timer
  {
  public:
    async_timer(UniqueTimer timer_, std::chrono::milliseconds duration_) :
      timer(std::forward<UniqueTimer>(timer_)), duration(duration_)
    {
      timer.stop();
    }


    bool await_ready() const { return duration.count() == 0; }


    void await_suspend(coro_handle<> suspending_awaitable)
    {
      timer.set(duration, [ch = suspending_awaitable](timer_id_t tid) mutable { ch.resume(); });
      timer.run();
    }


    bool await_resume() { return not timer.has_expired(); }


    async_timer& get_awaiter() { return *this; }


  private:
    UniqueTimer               timer;
    std::chrono::milliseconds duration;
  };


  return async_timer{std::forward<UniqueTimer>(timer), duration_msec};
}


} // namespace ocudu
