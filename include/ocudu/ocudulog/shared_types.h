// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/shared_types.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <functional>
#include <string>


namespace ocudulog {

/// Generic error handler callback.

/// Generic error handler callback.
using error_handler = std::function<void(const std::string&)>;

/// Backend priority levels.

/// Backend priority levels.
enum class backend_priority {
  /// Default priority of the operating system.
  /// Default priority of the operating system.
  normal,
  /// Thread will be given a high priority.
  /// Thread will be given a high priority.
  high,
  /// Thread will be given a very high priority.
  /// Thread will be given a very high priority.
  very_high
};

/// syslog log local types

/// syslog log local types
enum class syslog_local_type {
  local0,
  local1,
  local2,
  local3,
  local4,
  local5,
  local6,
  local7,
};


} // namespace ocudulog
