// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/async_no_op_task.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/async_task.h"


namespace ocudu {

/// Launches an async task that finishes immediately with the result set by the caller to this function.

/// Launches an async task that finishes immediately with the result set by the caller to this function.
template <typename Resp>
[[nodiscard]] async_task<std::decay_t<Resp>> launch_no_op_task(Resp&& r)
{
  return launch_async([r = std::forward<Resp>(r)](coro_context<async_task<std::decay_t<Resp>>>& ctx) {
    CORO_BEGIN(ctx);
    CORO_RETURN(r);
  });
}

/// Launches an async task that finishes immediately with the result set by the caller to this function.

/// Launches an async task that finishes immediately with the result set by the caller to this function.
[[nodiscard]] inline async_task<void> launch_no_op_task()
{
  return launch_async([](coro_context<async_task<void>>& ctx) {
    CORO_BEGIN(ctx);
    CORO_RETURN();
  });
}


} // namespace ocudu
