// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/synchronization/futex_util.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <atomic>
#include <cstdint>


namespace ocudu {
namespace futex_util {

/// \brief Suspends running thread if state == expected. Otherwise, it returns immediately.
/// \return 0 on success (state != expected or spurious wake-up), -1 on error (errno is set accordingly).
/// \remark Spurious wakeups or EINTR can happen. So callers need to re-check the condition in a loop.

/// \brief Suspends running thread if state == expected. Otherwise, it returns immediately.
/// \return 0 on success (state != expected or spurious wake-up), -1 on error (errno is set accordingly).
/// \remark Spurious wakeups or EINTR can happen. So callers need to re-check the condition in a loop.
long wait(std::atomic<uint32_t>& state, uint32_t expected);

/// \brief Wakes all threads waiting on the state variable.
/// \return number of awoken threads or -1 on error (errno is set accordingly).

/// \brief Wakes all threads waiting on the state variable.
/// \return number of awoken threads or -1 on error (errno is set accordingly).
long wake_all(std::atomic<uint32_t>& state);


} // namespace futex_util
} // namespace ocudu
