// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/synchronization/baton.h  (58 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <condition_variable>
#include <mutex>


namespace ocudu {

/// \brief Baton synchronization primitive.
///
/// It is used to synchronize two threads, where one waits for the other to finish.

/// \brief Baton synchronization primitive.
///
/// It is used to synchronize two threads, where one waits for the other to finish.
class baton
{
public:
  void post()
  {
    std::lock_guard<std::mutex> lock(mutex);
    is_set = true;
    cvar.notify_one();
  }


  void wait()
  {
    std::unique_lock<std::mutex> lock(mutex);
    cvar.wait(lock, [this] { return is_set; });
  }


private:
  std::mutex              mutex;
  std::condition_variable cvar;
  bool                    is_set = false;
};

/// RAII helper for baton synchronization primitive.

/// RAII helper for baton synchronization primitive.
class scoped_baton_sender
{
  struct deleter {
    void operator()(baton* p)
    {
      if (p != nullptr) {
        p->post();
      }
    }
  };


public:
  explicit scoped_baton_sender(baton& parent_) : parent(&parent_) {}


  void post() { parent = nullptr; }


private:
  /// Use of unique_ptr for RAII
  /// Use of unique_ptr for RAII
  std::unique_ptr<baton, deleter> parent;
};


} // namespace ocudu
