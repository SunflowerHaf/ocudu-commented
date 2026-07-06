// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ocudulog/log_backend_impl.h  (52 lines)
//
// LIBRARY: lib/ocudulog
// The custom logging framework for the entire codebase. Provides basic_logger, log_channel, and the ocudulog global registry. Every subsystem fetches a named logger from here. Supports per-channel log levels, hex dumps, and pluggable sinks (stdout, file, test sink).
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "backend_worker.h"
#include "ocudu/ocudulog/detail/log_backend.h"


namespace ocudulog {


class sink_repository;

/// This class implements the log backend interface. It internally manages a
/// worker thread to process incoming log entries.
/// NOTE: Thread safe class.

/// This class implements the log backend interface. It internally manages a
/// worker thread to process incoming log entries.
/// NOTE: Thread safe class.
class log_backend_impl : public detail::log_backend
{
public:
  explicit log_backend_impl(sink_repository& sink_repo) : worker(sink_repo, queue, arg_pool) {}


  log_backend_impl(const log_backend_impl& other)            = delete;
  log_backend_impl& operator=(const log_backend_impl& other) = delete;


  void start(backend_priority priority = backend_priority::normal) override { worker.start(priority); }


  bool push(detail::log_entry&& entry) override
  {
    auto* arg_store = entry.metadata.store;
    if (!queue.push(std::move(entry))) {
      arg_pool.dealloc(arg_store);
      return false;
    }
    return true;
  }


  fmt::dynamic_format_arg_store<fmt::format_context>* alloc_arg_store() override { return arg_pool.alloc(); }


  bool is_running() const override { return worker.is_running(); }

  /// Installs the specified error handler into the backend worker.

  /// Installs the specified error handler into the backend worker.
  void set_error_handler(error_handler err_handler) { worker.set_error_handler(std::move(err_handler)); }

  /// Stops the backend worker thread.

  /// Stops the backend worker thread.
  void stop() { worker.stop(); }


private:
  detail::work_queue<detail::log_entry> queue;
  detail::dyn_arg_store_pool            arg_pool;
  backend_worker                        worker;
};


} // namespace ocudulog
