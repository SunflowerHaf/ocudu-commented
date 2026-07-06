// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/support/dyn_arg_store_pool.h  (62 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "rigtorp/MPMCQueue.h"
#include "ocudu/ocudulog/detail/support/backend_capacity.h"


namespace ocudulog {


namespace detail {

/// Keeps a pool of dynamic_format_arg_store objects. The main reason for this class is that the arg store objects are
/// implemented with std::vectors, so we want to avoid allocating memory each time we create a new object. Instead,
/// reserve memory for each vector during initialization and recycle the objects.

/// Keeps a pool of dynamic_format_arg_store objects. The main reason for this class is that the arg store objects are
/// implemented with std::vectors, so we want to avoid allocating memory each time we create a new object. Instead,
/// reserve memory for each vector during initialization and recycle the objects.
class dyn_arg_store_pool
{
public:
  dyn_arg_store_pool() : free_list(OCUDULOG_QUEUE_CAPACITY)
  {
    pool.resize(OCUDULOG_QUEUE_CAPACITY);
    for (auto& elem : pool) {
      // Reserve for 10 normal and 2 named arguments.
      // Reserve for 10 normal and 2 named arguments.
      elem.reserve(10, 2);
    }
    for (auto& elem : pool) {
      free_list.push(&elem);
    }
  }

  /// Returns a pointer to a free dyn arg store object, otherwise returns nullptr.

  /// Returns a pointer to a free dyn arg store object, otherwise returns nullptr.
  fmt::dynamic_format_arg_store<fmt::format_context>* alloc()
  {
    if (free_list.empty()) {
      return nullptr;
    }


    fmt::dynamic_format_arg_store<fmt::format_context>* p = nullptr;
    free_list.try_pop(p);


    return p;
  }

  /// Deallocate the given dyn arg store object returning it to the pool.

  /// Deallocate the given dyn arg store object returning it to the pool.
  void dealloc(fmt::dynamic_format_arg_store<fmt::format_context>* p)
  {
    if (!p) {
      return;
    }


    p->clear();
    free_list.push(p);
  }


private:
  std::vector<fmt::dynamic_format_arg_store<fmt::format_context>>         pool;
  rigtorp::MPMCQueue<fmt::dynamic_format_arg_store<fmt::format_context>*> free_list;
};


} // namespace detail


} // namespace ocudulog
