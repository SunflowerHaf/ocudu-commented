// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/async/detail/function_signature.h  (60 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/detail/type_list.h"


namespace ocudu {
namespace detail {

/// Type to store arguments and return of callable type Sig.

/// Type to store arguments and return of callable type Sig.
template <typename Sig>
struct function_signature;

/// Specialization for free functions.

/// Specialization for free functions.
template <typename Ret, typename... Args>
struct function_signature<Ret(Args...)> {
  using return_type = Ret;
  using arg_types   = type_list<Args...>;
};

/// Specialization for mutable class methods.

/// Specialization for mutable class methods.
template <typename Ret, typename Obj, typename... Args>
struct function_signature<Ret (Obj::*)(Args...)> {
  using return_type = Ret;
  using arg_types   = type_list<Args...>;
};

/// Specialization for mutable and noexcept class methods.

/// Specialization for mutable and noexcept class methods.
template <typename Ret, typename Obj, typename... Args>
struct function_signature<Ret (Obj::*)(Args...) noexcept> {
  using return_type = Ret;
  using arg_types   = type_list<Args...>;
};

/// Specialization for const class methods.

/// Specialization for const class methods.
template <typename Ret, typename Obj, typename... Args>
struct function_signature<Ret (Obj::*)(Args...) const> {
  using return_type = Ret;
  using arg_types   = type_list<Args...>;
};

/// Specialization for const and noexcept class methods.

/// Specialization for const and noexcept class methods.
template <typename Ret, typename Obj, typename... Args>
struct function_signature<Ret (Obj::*)(Args...) const noexcept> {
  using return_type = Ret;
  using arg_types   = type_list<Args...>;
};


template <typename Sig>
using function_args_t = typename function_signature<Sig>::arg_types;


template <typename Sig>
using function_return_t = typename function_signature<Sig>::return_type;


template <typename T>
auto callable_arguments() -> typename function_signature<decltype(&std::decay_t<T>::operator())>::arg_types;


} // namespace detail
} // namespace ocudu
