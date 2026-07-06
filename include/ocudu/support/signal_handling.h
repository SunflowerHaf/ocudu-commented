// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/signal_handling.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {


using ocudu_signal_handler = void (*)(int signal);

/// \brief Registers the specified function to be called when the user interrupts the program execution (eg: via
/// Ctrl+C).
///
/// Passing a null function pointer disables the current installed handler.

/// \brief Registers the specified function to be called when the user interrupts the program execution (eg: via
/// Ctrl+C).
///
/// Passing a null function pointer disables the current installed handler.
void register_interrupt_signal_handler(ocudu_signal_handler handler);

/// \brief Registers the specified function to be called when the application is about to be forcefully shutdown by an
/// alarm signal.
///
/// Passing a null function pointer disables the current installed handler.

/// \brief Registers the specified function to be called when the application is about to be forcefully shutdown by an
/// alarm signal.
///
/// Passing a null function pointer disables the current installed handler.
void register_cleanup_signal_handler(ocudu_signal_handler handler);


} // namespace ocudu
