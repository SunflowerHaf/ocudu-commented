// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/error_handling.h  (80 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/rtsan.h"
#include "fmt/base.h"
#include <atomic>
#include <cstdio>
#include <cstdlib>


namespace ocudu {

/// Callback type for the error handler.

/// Callback type for the error handler.
using ocudu_error_handler = void (*)();
/// Error handler instance.
/// Error handler instance.
inline std::atomic<ocudu_error_handler> error_report_handler = nullptr;

/// Sets a new error handler to be used whenever a serious (non-recoverable) error is encountered.

/// Sets a new error handler to be used whenever a serious (non-recoverable) error is encountered.
inline void set_error_handler(ocudu_error_handler handler)
{
  error_report_handler = handler;
}

/// \brief Command to terminate application with an error message.
///
/// Attribute noinline is used to signal to the compiler that this path should rarely occur and therefore doesn't need
/// to get optimized.

/// \brief Command to terminate application with an error message.
///
/// Attribute noinline is used to signal to the compiler that this path should rarely occur and therefore doesn't need
/// to get optimized.
template <typename... Args>
[[gnu::noinline, noreturn]] inline bool ocudu_terminate(const char* reason_fmt, Args&&... args) noexcept
{
  OCUDU_RTSAN_SCOPED_DISABLER(d);


  if (auto handler = error_report_handler.exchange(nullptr)) {
    handler();
  }
  ::fflush(stdout);
  fmt::print(stderr, "OCUDU FATAL ERROR: ");
  fmt::println(stderr, reason_fmt, std::forward<Args>(args)...);


  std::abort();
}

/// \brief Reports an error and closes the application gracefully.
///
/// This function is intended to be used for error conditions that may be triggered by the user or through invalid
/// configurations.

/// \brief Reports an error and closes the application gracefully.
///
/// This function is intended to be used for error conditions that may be triggered by the user or through invalid
/// configurations.
template <typename... Args>
[[gnu::noinline, noreturn]] inline void report_error(const char* reason_fmt, Args&&... args) noexcept
{
  OCUDU_RTSAN_SCOPED_DISABLER(d);


  if (auto handler = error_report_handler.exchange(nullptr)) {
    handler();
  }
  ::fflush(stdout);
  fmt::print(stderr, "OCUDU ERROR: ");
  fmt::println(stderr, reason_fmt, std::forward<Args>(args)...);


  std::quick_exit(1);
}

/// \brief Reports a fatal error and handles the application shutdown.
///
/// This function is intended to be used for error conditions that are neither caught by the compiler nor possible to
/// be handled by the application at runtime.

/// \brief Reports a fatal error and handles the application shutdown.
///
/// This function is intended to be used for error conditions that are neither caught by the compiler nor possible to
/// be handled by the application at runtime.
template <typename... Args>
[[gnu::noinline, noreturn]] inline void report_fatal_error(const char* reason_fmt, Args&&... args) noexcept
{
  ocudu_terminate(reason_fmt, std::forward<Args>(args)...);
}

/// \brief Verifies if condition is true. If not, report a fatal error and closes the application.

/// \brief Verifies if condition is true. If not, report a fatal error and closes the application.
#define report_fatal_error_if_not(condition, fmtstr, ...)                                                              \
  (void)((condition) || (report_fatal_error(fmtstr, ##__VA_ARGS__), 0))

/// \brief Verifies if condition is true. If not, report an error and close the application.

/// \brief Verifies if condition is true. If not, report an error and close the application.
#define report_error_if_not(condition, fmtstr, ...) (void)((condition) || (report_error(fmtstr, ##__VA_ARGS__), 0))


} // namespace ocudu
