// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/log_entry_metadata.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "fmt/args.h"
#include <chrono>


namespace ocudulog {


namespace detail {

/// This structure gives the user a way to log generic information as a context.
//: TODO: legacy struct, will get replaced by the new context framework.

/// This structure gives the user a way to log generic information as a context.
//: TODO: legacy struct, will get replaced by the new context framework.
struct log_context {
  /// Generic context value.
  /// Generic context value.
  uint64_t value64;
  /// When true, the context value will be printed in the log entry.
  /// When true, the context value will be printed in the log entry.
  bool enabled;
};

/// Metadata fields carried for each log entry.

/// Metadata fields carried for each log entry.
struct log_entry_metadata {
  std::chrono::high_resolution_clock::time_point      tp;
  log_context                                         context;
  const char*                                         fmtstring;
  fmt::dynamic_format_arg_store<fmt::format_context>* store;
  std::string                                         log_name;
  char                                                log_tag;
  std::shared_ptr<const std::string>                  log_label;
  std::vector<uint8_t>                                hex_dump;
};


} // namespace detail


} // namespace ocudulog
