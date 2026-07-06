// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ocudulog/sinks/stream_sink.h  (44 lines)
//
// LIBRARY: lib/ocudulog
// The custom logging framework for the entire codebase. Provides basic_logger, log_channel, and the ocudulog global registry. Every subsystem fetches a named logger from here. Supports per-channel log levels, hex dumps, and pluggable sinks (stdout, file, test sink).
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/sink.h"


namespace ocudulog {

/// Standard stream types.

/// Standard stream types.
enum class sink_stream_type { stdout, stderr };

/// This sink implementation writes to either stdout or stderr streams.

/// This sink implementation writes to either stdout or stderr streams.
class stream_sink : public sink
{
public:
  stream_sink(sink_stream_type s, std::unique_ptr<log_formatter> f) :
    sink(std::move(f)), handle((s == sink_stream_type::stdout) ? stdout : stderr)
  {
  }


  stream_sink(const stream_sink& other)            = delete;
  stream_sink& operator=(const stream_sink& other) = delete;


  detail::error_string write(detail::memory_buffer buffer) override
  {
    assert(handle && "Invalid stream handle");
    std::fwrite(buffer.data(), sizeof(char), buffer.size(), handle);
    // We want to see the output instantly.
    // We want to see the output instantly.
    std::fflush(handle);
    return {};
  }


  detail::error_string flush() override
  {
    std::fflush(handle);
    return {};
  }


private:
  std::FILE* handle;
};


} // namespace ocudulog
