// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/type_traits.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <type_traits>


namespace ocudu {


namespace detail {

// To allow ADL with custom begin/end.

// To allow ADL with custom begin/end.
using std::begin;
using std::end;


template <typename T>
auto is_iterable_impl(int)
    -> decltype(begin(std::declval<T&>()) != end(std::declval<T&>()),   // begin/end and operator !=
                void(),                                                 // Handle evil operator ,
                ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
                void(*begin(std::declval<T&>())),                       // operator*
                std::true_type{});


template <typename T>
std::false_type is_iterable_impl(...);


} // namespace detail


template <typename T>
constexpr bool is_iterable = decltype(detail::is_iterable_impl<T>(0))::value;


} // namespace ocudu
