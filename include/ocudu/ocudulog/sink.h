// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/sink.h  (42 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/detail/support/error_string.h"
#include "ocudu/ocudulog/detail/support/memory_buffer.h"
#include "ocudu/ocudulog/formatter.h"
#include <cassert>


namespace ocudulog {

/// This interface provides the way to write incoming memory buffers to any kind
/// of backing store.

/// This interface provides the way to write incoming memory buffers to any kind
/// of backing store.
class sink
{
public:
  explicit sink(std::unique_ptr<log_formatter> f) : formatter(std::move(f))
  {
    assert(formatter && "Invalid formatter");
  }


  virtual ~sink() = default;

  /// Returns the formatter used by this sink.

  /// Returns the formatter used by this sink.
  log_formatter&       get_formatter() { return *formatter; }
  const log_formatter& get_formatter() const { return *formatter; }

  /// Writes the provided memory buffer into the sink.

  /// Writes the provided memory buffer into the sink.
  virtual detail::error_string write(detail::memory_buffer buffer) = 0;

  /// Writes as an error the provided memory buffer into the sink.

  /// Writes as an error the provided memory buffer into the sink.
  virtual detail::error_string write_error(detail::memory_buffer buffer) { return {}; }

  /// Flushes any buffered contents to the backing store.

  /// Flushes any buffered contents to the backing store.
  virtual detail::error_string flush() = 0;


private:
  std::unique_ptr<log_formatter> formatter;
};


} // namespace ocudulog
