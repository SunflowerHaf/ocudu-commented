// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/ue_manager/ue_task_scheduler_impl.h  (110 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/ue_task_scheduler.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/support/async/fifo_async_task_scheduler.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/timers.h"
#include <unordered_map>


namespace ocudu::ocucp {


class ue_task_scheduler_manager;

/// \brief Async FIFO task scheduler for a single UE managed by the CU-CP.

/// \brief Async FIFO task scheduler for a single UE managed by the CU-CP.
class ue_task_scheduler_impl : public ue_task_scheduler
{
  using ue_element = std::pair<const cu_cp_ue_index_t, std::unique_ptr<fifo_async_task_scheduler>>;


public:
  ue_task_scheduler_impl() = default;
  ue_task_scheduler_impl(ue_task_scheduler_manager& parent_, ue_element& ue_sched_) :
    parent(&parent_), ue_sched(&ue_sched_)
  {
  }
  ue_task_scheduler_impl(ue_task_scheduler_impl&& other) noexcept :
    parent(std::exchange(other.parent, nullptr)), ue_sched(std::exchange(other.ue_sched, nullptr))
  {
  }
  ue_task_scheduler_impl& operator=(ue_task_scheduler_impl&& other) noexcept
  {
    stop();
    parent   = std::exchange(other.parent, nullptr);
    ue_sched = std::exchange(other.ue_sched, nullptr);
    return *this;
  }
  ~ue_task_scheduler_impl() { stop(); }

  /// \brief Schedules an async task for the given UE. The task will run after the remaining tasks in the queue are
  /// completed.
  ///
  /// \param task Task to schedule
  /// \return true if the task was successfully enqueued. False, otherwise.

  /// \brief Schedules an async task for the given UE. The task will run after the remaining tasks in the queue are
  /// completed.
  ///
  /// \param task Task to schedule
  /// \return true if the task was successfully enqueued. False, otherwise.
  bool schedule_async_task(async_task<void> task) override
  {
    ocudu_assert(parent != nullptr, "UE task scheduler not set");
    return ue_sched->second->schedule(std::move(task));
  }

  /// Create a timer for the UE.

  /// Create a timer for the UE.
  unique_timer create_timer() override;


  timer_factory get_timer_factory() override;


  task_executor& get_executor() override;

  /// \brief Stops the UE task scheduler and discards all the pending tasks that haven't started running yet.

  /// \brief Stops the UE task scheduler and discards all the pending tasks that haven't started running yet.
  void stop();


private:
  ue_task_scheduler_manager* parent   = nullptr;
  ue_element*                ue_sched = nullptr;
};

/// \brief Service provided by CU-CP to schedule async tasks for a given UE.

/// \brief Service provided by CU-CP to schedule async tasks for a given UE.
class ue_task_scheduler_manager
{
public:
  explicit ue_task_scheduler_manager(timer_manager& timers_, task_executor& exec_, ocudulog::basic_logger& logger_);


  void stop();


  ue_task_scheduler_impl create_ue_task_sched(cu_cp_ue_index_t ue_idx);

  // UE task scheduler

  // UE task scheduler
  void handle_ue_async_task(cu_cp_ue_index_t ue_index, async_task<void>&& task);


  void clear_pending_tasks(cu_cp_ue_index_t ue_index);


  async_task<bool> dispatch_and_await_task_completion(cu_cp_ue_index_t ue_index, unique_task task);


  template <typename T>
  auto dispatch_and_await_task_completion(cu_cp_ue_index_t ue_index, async_task<T> task)
  {
    return when_coroutine_completed_on_task_sched(*ue_ctrl_loop.at(ue_index), std::move(task));
  }


  unique_timer   make_unique_timer();
  timer_manager& get_timer_manager();


private:
  friend class ue_task_scheduler_impl;


  void rem_ue_task_loop(cu_cp_ue_index_t ue_idx);


  timer_manager&          timers;
  task_executor&          exec;
  ocudulog::basic_logger& logger;

  // task event loops indexed by ue_index

  // task event loops indexed by ue_index
  std::unordered_map<cu_cp_ue_index_t, std::unique_ptr<fifo_async_task_scheduler>> ue_ctrl_loop;


  fifo_async_task_scheduler ues_to_rem;
};


} // namespace ocudu::ocucp
