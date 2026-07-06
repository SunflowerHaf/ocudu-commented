// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/log_backend.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/shared_types.h"
#include "fmt/args.h"
#include "fmt/core.h"


namespace ocudulog {


namespace detail {


struct log_entry;

/// The log backend receives generated log entries from the application. Each
/// entry gets distributed to the corresponding sinks.
/// NOTE: Thread safe class.

/// The log backend receives generated log entries from the application. Each
/// entry gets distributed to the corresponding sinks.
/// NOTE: Thread safe class.
class log_backend
{
public:
  virtual ~log_backend() = default;

  /// Starts the processing of incoming log entries.
  /// NOTE: Calling this function more than once has no side effects.

  /// Starts the processing of incoming log entries.
  /// NOTE: Calling this function more than once has no side effects.
  virtual void start(backend_priority priority = backend_priority::normal) = 0;

  /// Allocates a dyn_arg_store and returns a pointer to it on success, otherwise returns nullptr.

  /// Allocates a dyn_arg_store and returns a pointer to it on success, otherwise returns nullptr.
  virtual fmt::dynamic_format_arg_store<fmt::format_context>* alloc_arg_store() = 0;

  /// Pushes a log entry into the backend. Returns true on success, otherwise
  /// false.

  /// Pushes a log entry into the backend. Returns true on success, otherwise
  /// false.
  virtual bool push(log_entry&& entry) = 0;

  /// Returns true when the backend has been started, otherwise false.

  /// Returns true when the backend has been started, otherwise false.
  virtual bool is_running() const = 0;
};


} // namespace detail


} // namespace ocudulog
