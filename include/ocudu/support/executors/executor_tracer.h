// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/executors/executor_tracer.h  (117 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/tracing/event_tracing.h"


namespace ocudu {

/// \brief A task executor that traces the latencies of the task enqueuing/dequeuing and task invocation.

/// \brief A task executor that traces the latencies of the task enqueuing/dequeuing and task invocation.
template <typename Exec, typename Tracer>
class executor_tracer final : public task_executor
{
public:
  template <typename ExecType>
  executor_tracer(ExecType&& exec_, Tracer& tracer_, const std::string& name_) :
    exec(std::forward<ExecType>(exec_)),
    tracer(tracer_),
    enqueue_event_name(fmt::format("{}_enqueue", name_)),
    run_event_name(fmt::format("{}_run", name_))
  {
  }


  [[nodiscard]] bool execute(unique_task task) override
  {
    auto enqueue_tp = trace_clock::now();
    return get(exec).execute([this, task = std::move(task), enqueue_tp]() mutable {
      tracer << trace_event(enqueue_event_name.c_str(), enqueue_tp);
      auto process_tp = trace_clock::now();
      task();
      tracer << trace_event(run_event_name.c_str(), process_tp);
    });
  }


  [[nodiscard]] bool defer(unique_task task) override
  {
    auto enqueue_tp = trace_clock::now();
    return get(exec).defer([this, task = std::move(task), enqueue_tp]() mutable {
      tracer << trace_event(enqueue_event_name.c_str(), enqueue_tp);
      auto process_tp = trace_clock::now();
      task();
      tracer << trace_event(run_event_name.c_str(), process_tp);
    });
  }


private:
  template <typename U>
  U& get(U* u)
  {
    return *u;
  }


  template <typename U>
  U& get(std::unique_ptr<U>& u)
  {
    return *u;
  }


  template <typename U>
  U& get(U& u)
  {
    return u;
  }


  Exec        exec;
  Tracer&     tracer;
  std::string enqueue_event_name;
  std::string run_event_name;
};

/// \brief Specialization for null event tracer. It should not add any overhead compared to the original executor.

/// \brief Specialization for null event tracer. It should not add any overhead compared to the original executor.
template <typename Exec>
class executor_tracer<Exec, detail::null_event_tracer> final : public task_executor
{
public:
  executor_tracer(Exec exec_, detail::null_event_tracer& /**/, const std::string& /**/) : exec(std::move(exec_)) {}


  [[nodiscard]] bool execute(unique_task task) override { return get(exec).execute(std::move(task)); }


  [[nodiscard]] bool defer(unique_task task) override { return get(exec).defer(std::move(task)); }


private:
  template <typename U>
  U& get(U* u)
  {
    return *u;
  }


  template <typename U>
  U& get(std::unique_ptr<U> u)
  {
    return *u;
  }


  template <typename U>
  U& get(U& u)
  {
    return u;
  }


  Exec exec;
};


template <typename Exec, typename Tracer>
executor_tracer<Exec, Tracer> make_trace_executor(const std::string& name, Exec&& exec, Tracer& tracer)
{
  return executor_tracer<Exec, Tracer>(std::forward<Exec>(exec), tracer, name);
}


template <typename Exec, typename Tracer>
std::unique_ptr<task_executor> make_trace_executor_ptr(const std::string& name, Exec&& exec, Tracer& tracer)
{
  return std::make_unique<executor_tracer<Exec, Tracer>>(std::forward<Exec>(exec), tracer, name);
}


} // namespace ocudu
