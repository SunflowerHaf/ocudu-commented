// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/ocudu_test.h  (47 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/ocudu_assert.h"
#include "fmt/format.h"


namespace ocudu {


namespace detail {

/// Helper function to format TESTASSERT_EQ.

/// Helper function to format TESTASSERT_EQ.
template <typename T, typename U>
[[gnu::noinline]] inline std::string
assert_eq_format_helper(T expected_val, U actual_val, bool eq_cmp, const std::string& msg) noexcept
{
  fmt::memory_buffer fmtbuf;
  if (eq_cmp) {
    fmt::format_to(
        std::back_inserter(fmtbuf), "Actual value '{}' differs from expected '{}'", actual_val, expected_val);
  } else {
    fmt::format_to(std::back_inserter(fmtbuf), "Value '{}' should not be equal to '{}'", actual_val, expected_val);
  }
  if (not msg.empty()) {
    fmt::format_to(std::back_inserter(fmtbuf), ". {}", msg);
  }
  return fmt::to_string(fmtbuf);
}


} // namespace detail


#define TESTASSERT_EQ(EXPECTED, ACTUAL, ...)                                                                           \
  OCUDU_ALWAYS_ASSERT__(((EXPECTED) == (ACTUAL)),                                                                      \
                        "{}",                                                                                          \
                        ocudu::detail::assert_eq_format_helper(EXPECTED, ACTUAL, true, fmt::format("" __VA_ARGS__)))


#define TESTASSERT_NEQ(EXPECTED, ACTUAL, ...)                                                                          \
  OCUDU_ALWAYS_ASSERT__(((EXPECTED) != (ACTUAL)),                                                                      \
                        "{}",                                                                                          \
                        ocudu::detail::assert_eq_format_helper(EXPECTED, ACTUAL, false, fmt::format("" __VA_ARGS__)))


#define TESTASSERT(cond, ...)                                                                                          \
  OCUDU_ALWAYS_ASSERT__(                                                                                               \
      cond, "{}", ocudu::detail::assert_eq_format_helper(true, false, true, fmt::format("" __VA_ARGS__)))


} // namespace ocudu
