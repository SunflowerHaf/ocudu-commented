// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Defines helper macros to use RTSAN, if supported.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/rtsan.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Defines helper macros to use RTSAN, if supported.

#pragma once


#ifdef __has_feature
#if __has_feature(realtime_sanitizer)
#define OCUDU_RTSAN_ENABLED
#endif
#endif


#ifdef OCUDU_RTSAN_ENABLED
#include <sanitizer/rtsan_interface.h>


#define OCUDU_RTSAN_NONBLOCKING [[clang::nonblocking]]
#define OCUDU_RTSAN_SCOPED_DISABLER(VAR) __rtsan::ScopedDisabler(VAR);


namespace ocudu {
namespace detail {
class scoped_enabler
{
public:
  scoped_enabler() { __rtsan_enable(); }
  ~scoped_enabler() { __rtsan_disable(); }
  scoped_enabler(const scoped_enabler&)            = delete;
  scoped_enabler& operator=(const scoped_enabler&) = delete;
  scoped_enabler(scoped_enabler&&)                 = delete;
  scoped_enabler& operator=(scoped_enabler&&)      = delete;
};
} // namespace detail
} // namespace ocudu


#define OCUDU_RTSAN_SCOPED_ENABLER ::ocudu::detail::scoped_enabler rtsan_enabler##__LINE__


#else
#define OCUDU_RTSAN_NONBLOCKING
#define OCUDU_RTSAN_SCOPED_DISABLER(VAR)
#define OCUDU_RTSAN_SCOPED_ENABLER
#endif
