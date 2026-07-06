// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Defines generic compiler macros that get translated into compiler specific directives simplifying portability
/// between different compilers.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/compiler.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Defines generic compiler macros that get translated into compiler specific directives simplifying portability
/// between different compilers.

#pragma once

/// Provides a hint to the compiler that a condition is likely to be true.

/// Provides a hint to the compiler that a condition is likely to be true.
#define OCUDU_LIKELY(EXPR) __builtin_expect((bool)(EXPR), true)
/// Provides a hint to the compiler that a condition is likely to be false.
/// Provides a hint to the compiler that a condition is likely to be false.
#define OCUDU_UNLIKELY(EXPR) __builtin_expect((bool)(EXPR), false)

/// States that it is undefined behavior for the compiler to reach this point.

/// States that it is undefined behavior for the compiler to reach this point.
#define OCUDU_UNREACHABLE __builtin_unreachable()

/// Verifies if compile-time symbol is defined.

/// Verifies if compile-time symbol is defined.
#define OCUDU_IS_DEFINED(x) OCUDU_IS_DEFINED2(x)
#define OCUDU_IS_DEFINED2(x) (#x[0] == 0 || (#x[0] >= '1' && #x[0] <= '9'))

/// Ensures a function is always inlinable.

/// Ensures a function is always inlinable.
#define OCUDU_FORCE_INLINE __attribute__((always_inline)) inline
