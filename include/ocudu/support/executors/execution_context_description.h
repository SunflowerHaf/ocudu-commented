// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/execution_context_description.h  (20 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {
namespace execution_context {

/// \brief Get number of concurrent workers in the current execution context.
///
/// This function will return 1 if called from within a single task worker and the number of threads of a thread pool
/// if called from within the same thread pool.

/// \brief Get number of concurrent workers in the current execution context.
///
/// This function will return 1 if called from within a single task worker and the number of threads of a thread pool
/// if called from within the same thread pool.
[[nodiscard]] unsigned get_current_nof_concurrent_workers();

/// \brief Get the index of the worker in the current execution context. If the worker is a single task_worker, this
// function will return 0. If the worker belongs to a thread pool, it will return the index of the thread in the pool.

/// \brief Get the index of the worker in the current execution context. If the worker is a single task_worker, this
// function will return 0. If the worker belongs to a thread pool, it will return the index of the thread in the pool.
[[nodiscard]] unsigned get_current_worker_index();


} // namespace execution_context
} // namespace ocudu
