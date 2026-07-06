// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/support/executors/priority_task_worker.cpp  (40 lines)
//
// LIBRARY: lib/support
// General-purpose C++ utilities: async task executors, thread pools, timer manager, memory pools, span/expected/bounded_integer types, signal dispatcher, config parsers, format helpers, synchronisation primitives (stop_event, sync_event), and versioning. Not 5G-specific — these could be a standalone C++ utility library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/support/executors/priority_task_worker.h"
#include "ocudu/ocudulog/ocudulog.h"


using namespace ocudu;


priority_task_worker::priority_task_worker(std::string                         thread_name,
                                           span<const concurrent_queue_params> task_queue_params,
                                           std::chrono::microseconds           wait_interval,
                                           os_thread_realtime_priority         prio,
                                           const os_sched_affinity_bitmask&    mask) :
  task_queue(task_queue_params, wait_interval), t_handle(thread_name, prio, mask, [this]() { run_pop_task_loop(); })
{
}


void priority_task_worker::stop()
{
  if (t_handle.running()) {
    task_queue.request_stop();
    t_handle.join();
  }
}


void priority_task_worker::run_pop_task_loop()
{
  auto consumer = task_queue.create_consumer();


  unique_task t;
  while (consumer.pop_blocking(t)) {
    // Run popped task
    // Run popped task
    t();

    // Note: Important to clear the task in case it has any RAII object.

    // Note: Important to clear the task in case it has any RAII object.
    t = {};
  }


  ocudulog::fetch_basic_logger("ALL").info("Task worker \"{}\" finished.", this_thread_name());
}
