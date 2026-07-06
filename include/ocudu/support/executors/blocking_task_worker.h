// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/blocking_task_worker.h  (55 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/blocking_queue.h"
#include "ocudu/support/executors/task_executor.h"


namespace ocudu {

/// \brief Contrarily to other type of workers, this worker runs in the same thread where run() is called.
/// run() is blocking.

/// \brief Contrarily to other type of workers, this worker runs in the same thread where run() is called.
/// run() is blocking.
class blocking_task_worker final : public task_executor
{
public:
  blocking_task_worker(size_t q_size) : pending_tasks(q_size) {}


  [[nodiscard]] bool execute(unique_task task) override
  {
    pending_tasks.push_blocking(std::move(task));
    return true;
  }


  [[nodiscard]] bool defer(unique_task task) override
  {
    (void)execute(std::move(task));
    return true;
  }


  void request_stop()
  {
    (void)execute([this]() {
      if (not pending_tasks.is_stopped()) {
        pending_tasks.stop();
      }
    });
  }


  void run()
  {
    while (true) {
      bool        success;
      unique_task t = pending_tasks.pop_blocking(&success);
      if (not success) {
        break;
      }
      t();
    }
  }


private:
  blocking_queue<unique_task> pending_tasks;
};


} // namespace ocudu
