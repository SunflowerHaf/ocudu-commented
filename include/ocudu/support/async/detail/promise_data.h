// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/detail/promise_data.h  (65 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/compiler.h"
#include "ocudu/support/ocudu_assert.h"
#include <memory>


namespace ocudu {
namespace detail {

/// Class that holds promise result value.

/// Class that holds promise result value.
template <typename R, typename Base>
struct promise_data : public Base {
  promise_data() = default;


  promise_data(const promise_data& other)            = delete;
  promise_data(promise_data&& other)                 = delete;
  promise_data& operator=(const promise_data& other) = delete;
  promise_data& operator=(promise_data&& other)      = delete;


  ~promise_data()
  {
    if (Base::has_value) {
      std::launder(reinterpret_cast<R*>(&mem))->~R();
    }
  }

  /// Set Return value.

  /// Set Return value.
  template <typename U>
  void return_value(U&& u)
  {
    ocudu_sanity_check(not Base::has_value, "Return called more than once.");
    new (&mem) R(std::forward<U>(u));
    Base::has_value = true;
  }

  /// Get Return value.

  /// Get Return value.
  const R& get() const&
  {
    ocudu_assert(Base::has_value, "Trying to extract result from unset Promise");
    return *std::launder(reinterpret_cast<const R*>(&mem));
  }

  /// Get Return value.

  /// Get Return value.
  R get() &&
  {
    ocudu_assert(Base::has_value, "Trying to extract result from unset Promise");
    return std::move(*std::launder(reinterpret_cast<R*>(&mem)));
  }


private:
  /// Result storage.
  /// Result storage.
  std::aligned_storage_t<sizeof(R), alignof(R)> mem;
};

/// Specialization for when Return type is void.

/// Specialization for when Return type is void.
template <typename Base>
struct promise_data<void, Base> : public Base {
  void return_value() { Base::has_value = true; }
};


} // namespace detail
} // namespace ocudu
