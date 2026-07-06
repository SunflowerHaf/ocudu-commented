// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/support/memory_buffer.h  (39 lines)
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

/// This class wraps a read-only and non owning memory block, providing simple
/// methods to access its contents.

/// This class wraps a read-only and non owning memory block, providing simple
/// methods to access its contents.
class memory_buffer
{
  const char* const buffer;
  const size_t      length;


public:
  memory_buffer(const char* buffer_, size_t length_) : buffer(buffer_), length(length_) {}


  explicit memory_buffer(const std::string& s) : buffer(s.data()), length(s.size()) {}

  /// Returns a pointer to the start of the memory block.

  /// Returns a pointer to the start of the memory block.
  const char* data() const { return buffer; }

  /// Returns an iterator to the beginning of the buffer.

  /// Returns an iterator to the beginning of the buffer.
  const char* begin() const { return buffer; }

  /// Returns an iterator to the end of the buffer.

  /// Returns an iterator to the end of the buffer.
  const char* end() const { return buffer + length; }

  /// Returns the size of the memory block.

  /// Returns the size of the memory block.
  size_t size() const { return length; }
};


} // namespace detail


} // namespace ocudulog
