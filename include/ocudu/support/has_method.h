// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/has_method.h  (49 lines)
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

/// Helper metafunction to determine if a type T can be dereferenced (i.e., have an operator* defined).

/// Helper metafunction to determine if a type T can be dereferenced (i.e., have an operator* defined).
template <typename T, typename = void>
struct is_dereferenceable_impl : std::false_type {};

/// Specialization for types that can be dereferenced.

/// Specialization for types that can be dereferenced.
template <typename T>
struct is_dereferenceable_impl<T, std::void_t<decltype(*std::declval<T>())>> : std::true_type {};


template <typename T, typename F>
constexpr auto has_member_impl(F&& f) -> decltype(f(std::declval<T>()), true)
{
  return true;
}


template <typename>
constexpr bool has_member_impl(...)
{
  return false;
}


} // namespace detail

/// Determines whether the type T can be dereferenced (i.e., has an operator* defined).

/// Determines whether the type T can be dereferenced (i.e., has an operator* defined).
template <typename T>
using is_dereferenceable = detail::is_dereferenceable_impl<T>;

/// Creates a trait that checks if a provided type T has a method with the specified name and signature.

/// Creates a trait that checks if a provided type T has a method with the specified name and signature.
#define CREATE_TRAIT_HAS_METHOD(trait_name, method_name)                                                               \
  template <typename, typename T, typename = void>                                                                     \
  struct trait_name : std::false_type {};                                                                              \
                                                                                                                       \
  template <typename T, typename Ret, typename... Args>                                                                \
  struct trait_name<T, Ret(Args...), std::void_t<decltype(std::declval<T>().method_name(std::declval<Args>()...))>>    \
    : std::is_same<decltype(std::declval<T>().method_name(std::declval<Args>()...)), Ret> {}

/// Check if type T has the method/member EXPR.

/// Check if type T has the method/member EXPR.
#define has_member(T, EXPR) detail::has_member_impl<T>([](auto&& obj) -> decltype(obj.EXPR) {})


} // namespace ocudu
