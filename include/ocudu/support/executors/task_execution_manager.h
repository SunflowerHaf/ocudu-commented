// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/task_execution_manager.h  (133 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/detail/concurrent_queue_params.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/executors/unique_thread.h"
#include <unordered_map>


namespace ocudu {


template <bool Enabled>
class file_event_tracer;


namespace execution_config_helper {


using task_priority = enqueue_priority;

/// Parameters of a queue of tasks.

/// Parameters of a queue of tasks.
struct task_queue {
  /// Name attributed to this task queue.
  /// Name attributed to this task queue.
  std::string name;
  /// Queueing policy used by this task queue.
  /// Queueing policy used by this task queue.
  concurrent_queue_policy policy;
  /// Size of the queue used.
  /// Size of the queue used.
  unsigned size;
  /// Number of pre-reserved producers in the case of the moodycamel lockfree MPMC queue.
  /// Number of pre-reserved producers in the case of the moodycamel lockfree MPMC queue.
  unsigned nof_prereserved_producers = cpu_architecture_info::get().get_host_total_nof_cpus();
};

/// Arguments for a single task worker creation.

/// Arguments for a single task worker creation.
struct single_worker {
  /// Worker name.
  /// Worker name.
  std::string name;
  /// Queue used by the task worker.
  /// Queue used by the task worker.
  task_queue queue;
  /// \brief Wait time in microseconds, when task queue has no pending tasks. If not set, a condition variable is
  /// used to wake up the worker when a new task is pushed.
  /// \brief Wait time in microseconds, when task queue has no pending tasks. If not set, a condition variable is
  /// used to wake up the worker when a new task is pushed.
  std::optional<std::chrono::microseconds> wait_sleep_time;
  /// OS priority of the worker thread.
  /// OS priority of the worker thread.
  os_thread_realtime_priority prio = os_thread_realtime_priority::no_realtime();
  /// Bit mask to set worker cpu affinity.
  /// Bit mask to set worker cpu affinity.
  os_sched_affinity_bitmask mask = {};
};

/// Arguments for a task worker pool creation.

/// Arguments for a task worker pool creation.
struct worker_pool {
  /// Worker Pool prefix name. Workers will be named as name#0, name#1, etc.
  /// Worker Pool prefix name. Workers will be named as name#0, name#1, etc.
  std::string name;
  /// Number of workers in the pool.
  /// Number of workers in the pool.
  unsigned nof_workers;
  /// Queue(s) used by the task worker. The lower the index, the higher the priority.
  /// Queue(s) used by the task worker. The lower the index, the higher the priority.
  std::vector<task_queue> queues;
  /// \brief Wait time in microseconds, when task queue has no pending tasks.
  /// \brief Wait time in microseconds, when task queue has no pending tasks.
  std::chrono::microseconds sleep_time;
  /// OS priority of the worker thread.
  /// OS priority of the worker thread.
  os_thread_realtime_priority prio = os_thread_realtime_priority::no_realtime();
  /// Array of CPU bitmasks to assign to each worker in the pool.
  /// Array of CPU bitmasks to assign to each worker in the pool.
  std::vector<os_sched_affinity_bitmask> masks;
};

/// Arguments for the creation of a priority multiqueue worker.

/// Arguments for the creation of a priority multiqueue worker.
struct priority_multiqueue_worker {
  /// Worker name.
  /// Worker name.
  std::string name;
  /// \brief Queues of different priorities. The lower the index, the higher the priority.
  /// The size of the vector matches the number of instantiated queues.
  /// \brief Queues of different priorities. The lower the index, the higher the priority.
  /// The size of the vector matches the number of instantiated queues.
  std::vector<task_queue> queues;
  /// \brief Wait time in microseconds, when task queue has no pending tasks.
  /// \brief Wait time in microseconds, when task queue has no pending tasks.
  std::chrono::microseconds spin_sleep_time;
  /// OS priority of the worker thread.
  /// OS priority of the worker thread.
  os_thread_realtime_priority prio = os_thread_realtime_priority::no_realtime();
  /// Bit mask to set worker cpu affinity.
  /// Bit mask to set worker cpu affinity.
  os_sched_affinity_bitmask mask = {};
};


} // namespace execution_config_helper

/// General execution context to which tasks can be dispatched via task executors.

/// General execution context to which tasks can be dispatched via task executors.
class task_execution_context
{
public:
  virtual ~task_execution_context() = default;

  /// Stop the execution context.

  /// Stop the execution context.
  virtual void stop() = 0;

  /// Name of the execution context.

  /// Name of the execution context.
  virtual std::string name() const = 0;

  /// Executors instantiated in this execution context.

  /// Executors instantiated in this execution context.
  virtual std::vector<std::pair<std::string, task_executor*>> executors() const = 0;
};

/// Create a single worker execution context.

/// Create a single worker execution context.
std::unique_ptr<task_execution_context> create_execution_context(const execution_config_helper::single_worker& params);

/// Create a worker pool execution context.

/// Create a worker pool execution context.
std::unique_ptr<task_execution_context> create_execution_context(const execution_config_helper::worker_pool& params);

/// Create a multi-priority worker execution context.

/// Create a multi-priority worker execution context.
std::unique_ptr<task_execution_context>
create_execution_context(const execution_config_helper::priority_multiqueue_worker& params);

/// Repository of execution contexts and task executors.

/// Repository of execution contexts and task executors.
class task_execution_manager
{
public:
  using executor_table = std::unordered_map<std::string, task_executor*>;

  /// Creates an empty task execution manager.

  /// Creates an empty task execution manager.
  task_execution_manager();

  /// Stops all execution contexts.

  /// Stops all execution contexts.
  void stop();

  /// Add new execution context to repository.

  /// Add new execution context to repository.
  [[nodiscard]] bool add_execution_context(std::unique_ptr<task_execution_context> ctxt);

  /// Returns a table of all executors stored in the repository.

  /// Returns a table of all executors stored in the repository.
  [[nodiscard]] const executor_table& executors() const { return executor_list; }


private:
  ocudulog::basic_logger& logger;


  std::unordered_map<std::string, std::unique_ptr<task_execution_context>> contexts;

  /// Container of executors instantiated for all execution contexts within this \c task_execution_manager.

  /// Container of executors instantiated for all execution contexts within this \c task_execution_manager.
  executor_table executor_list;
};


} // namespace ocudu
