// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/support/error_string.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <string>


namespace ocudulog {


namespace detail {

/// This is a lightweight error class that encapsulates a string for error
/// reporting.

/// This is a lightweight error class that encapsulates a string for error
/// reporting.
class error_string
{
  std::string error;


public:
  error_string() = default;


  /*implicit*/ error_string(std::string error_) : error(std::move(error_)) {}
  /*implicit*/ error_string(const char* error_) : error(error_) {}

  /// Returns the error string.

  /// Returns the error string.
  const std::string& get_error() const { return error; }


  explicit operator bool() const { return !error.empty(); }
};


} // namespace detail


} // namespace ocudulog
