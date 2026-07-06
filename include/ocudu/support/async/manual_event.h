// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/manual_event.h  (76 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/async/coroutine.h"
#include "ocudu/support/async/detail/event_impl.h"
#include <utility>


namespace ocudu {

/// Awaitable type that can be manually set to one of the states:
/// - "unset" state - Coroutines that await on an "unset" manual_event get suspended. They are only resumed when the
///   manual_event transitions to "set" state via the manual_event::set method.
/// - "set" state - Coroutines that await on a "set" manual_event do not get suspended and get automatically resumed.
///
/// Once "set", the awaiting coroutines have to option to extract the \c Data that was stored in the manual_event.
/// Multiple coroutines can simultaneously await this awaitable when in "unset" state. All the awaiting coroutines will
/// be resumed once the awaitable is set.
/// \tparam Data type of data passed to awaiting coroutine.

/// Awaitable type that can be manually set to one of the states:
/// - "unset" state - Coroutines that await on an "unset" manual_event get suspended. They are only resumed when the
///   manual_event transitions to "set" state via the manual_event::set method.
/// - "set" state - Coroutines that await on a "set" manual_event do not get suspended and get automatically resumed.
///
/// Once "set", the awaiting coroutines have to option to extract the \c Data that was stored in the manual_event.
/// Multiple coroutines can simultaneously await this awaitable when in "unset" state. All the awaiting coroutines will
/// be resumed once the awaitable is set.
/// \tparam Data type of data passed to awaiting coroutine.
template <typename Data>
class manual_event : public detail::manual_event_common
{
public:
  /// Stored value type.
  /// Stored value type.
  using result_type = Data;

  /// Awaiter object type.

  /// Awaiter object type.
  struct awaiter_type : public awaiter_common {
    using awaiter_common::awaiter_common;
    Data await_resume() const { return static_cast<manual_event*>(event)->data; }
  };

  /// Called to set event value, and trigger all awaiting coroutines.

  /// Called to set event value, and trigger all awaiting coroutines.
  template <typename U>
  void set(U&& u)
  {
    data = std::forward<U>(u);
    flush();
  }

  /// Called to object stored value when event is set.

  /// Called to object stored value when event is set.
  const Data& get() const
  {
    ocudu_sanity_check(is_set(), "trying to get manual_event<Data> data for non-set event");
    return data;
  }

  /// Awaiter interface.

  /// Awaiter interface.
  awaiter_type get_awaiter() { return awaiter_type{*this}; }


private:
  /// Value set.
  /// Value set.
  Data data;
};

/// Specialization of manual_event<Data> for the case that the Data is void.

/// Specialization of manual_event<Data> for the case that the Data is void.
template <>
class manual_event<void> : public detail::manual_event_common
{
public:
  using result_type = void;
  struct awaiter_type : public awaiter_common {
    using awaiter_common::awaiter_common;
    void await_resume() {}
  };


  void set() { flush(); }

  /// Awaiter interface.

  /// Awaiter interface.
  awaiter_type get_awaiter() { return awaiter_type{*this}; }
};


using manual_event_flag = manual_event<void>;


} // namespace ocudu
