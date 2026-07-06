// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/log_entry.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/detail/log_entry_metadata.h"
#include "ocudu/ocudulog/detail/support/thread_utils.h"


namespace ocudulog {


class sink;


namespace detail {

/// This command flushes all the messages pending in the backend.

/// This command flushes all the messages pending in the backend.
struct flush_backend_cmd {
  shared_variable<bool>& completion_flag;
  std::vector<sink*>     sinks;
};

/// This structure packs all the required data required to create a log entry in
/// the backend.
//: TODO: replace this object using a real command pattern when we have a raw
// memory queue for passing entries.

/// This structure packs all the required data required to create a log entry in
/// the backend.
//: TODO: replace this object using a real command pattern when we have a raw
// memory queue for passing entries.
struct log_entry {
  sink*                                                                          s;
  std::function<void(log_entry_metadata&& metadata, fmt::memory_buffer& buffer)> format_func;
  log_entry_metadata                                                             metadata;
  std::unique_ptr<flush_backend_cmd>                                             flush_cmd;
};


} // namespace detail


} // namespace ocudulog
