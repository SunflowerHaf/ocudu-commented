// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/async_test_utils.h  (86 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/async_no_op_task.h"
#include "ocudu/support/async/async_task.h"
#include "ocudu/support/async/eager_async_task.h"
#include "ocudu/support/async/manual_event.h"
#include <optional>


namespace ocudu {

/// Factory of async tasks that await on an external event.

/// Factory of async tasks that await on an external event.
template <typename Result>
class wait_manual_event_tester
{
public:
  wait_manual_event_tester() = default;


  wait_manual_event_tester(const Result& r) : result(r) {}
  wait_manual_event_tester(Result&& r) : result(std::move(r)) {}


  async_task<Result> launch()
  {
    return launch_async([this](coro_context<async_task<Result>>& ctx) {
      CORO_BEGIN(ctx);
      CORO_AWAIT(ready_ev);
      CORO_RETURN(result);
    });
  }


  manual_event_flag ready_ev;
  Result            result;
};

/// Specialization for result of type void.

/// Specialization for result of type void.
template <>
class wait_manual_event_tester<void>
{
public:
  async_task<void> launch()
  {
    return launch_async([this](coro_context<async_task<void>>& ctx) {
      CORO_BEGIN(ctx);
      CORO_AWAIT(ready_ev);
      CORO_RETURN();
    });
  }


  manual_event_flag ready_ev;
};


template <typename R>
struct lazy_task_launcher : public eager_async_task<R> {
  explicit lazy_task_launcher(async_task<R>& t_) : t(t_)
  {
    *static_cast<eager_async_task<R>*>(this) = launch_async([this](coro_context<eager_async_task<R>>& ctx) {
      CORO_BEGIN(ctx);
      CORO_AWAIT_VALUE(result, t);
      CORO_RETURN(result.value());
    });
  }


  std::optional<R> result;


private:
  async_task<R>& t;
};


template <>
struct lazy_task_launcher<void> : public eager_async_task<void> {
  explicit lazy_task_launcher(async_task<void>& t_) : t(t_)
  {
    *static_cast<eager_async_task<void>*>(this) = launch_async([this](coro_context<eager_async_task<void>>& ctx) {
      CORO_BEGIN(ctx);
      CORO_AWAIT(t);
      CORO_RETURN();
    });
  }


private:
  async_task<void>& t;
};


} // namespace ocudu
