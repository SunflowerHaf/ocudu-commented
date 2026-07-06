// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/math/detail/type_utils.h  (51 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <cstdint>
#include <limits>
#include <type_traits>


namespace ocudu {
namespace detail {

/// Checks if a value V fits in the integer type T.

/// Checks if a value V fits in the integer type T.
template <typename T, auto V>
constexpr bool fits_in_integer_type()
{
  static_assert(std::is_integral_v<T>, "T must be an integer type");
  using VType = decltype(V);
  static_assert(std::is_integral_v<VType>, "V must be of an integer type");

  // Compare in a common type to avoid issues with signed/unsigned promotions.

  // Compare in a common type to avoid issues with signed/unsigned promotions.
  using CommonT = std::common_type_t<T, VType>;
  return static_cast<CommonT>(V) >= static_cast<CommonT>(std::numeric_limits<T>::min()) and
         static_cast<CommonT>(V) <= static_cast<CommonT>(std::numeric_limits<T>::max());
}


template <auto V>
struct smallest_signed_fit {
  // clang-format off
  // clang-format off
  using type = std::conditional_t<fits_in_integer_type<int8_t, V>(), int8_t,
        std::conditional_t<fits_in_integer_type<int16_t, V>(), int16_t,
          std::conditional_t<fits_in_integer_type<int32_t, V>(), int32_t,
            std::conditional_t<fits_in_integer_type<int64_t, V>(), int64_t,
              void>>>>;
  // clang-format on
  // clang-format on
};


} // namespace detail

/// \brief Determines the smallest signed integer type that can fit the value V.

/// \brief Determines the smallest signed integer type that can fit the value V.
template <auto V>
using smallest_signed_fit_t = typename detail::smallest_signed_fit<V>::type;

/// \brief Determines a signed integer type that can fit the value V, preferring the type of V if it is large enough.

/// \brief Determines a signed integer type that can fit the value V, preferring the type of V if it is large enough.
template <auto V>
using expand_signed_if_not_fit_t =
    std::conditional_t<(sizeof(std::make_signed_t<decltype(V)>) >= sizeof(smallest_signed_fit_t<V>)),
                       std::make_signed_t<decltype(V)>,
                       smallest_signed_fit_t<V>>;


} // namespace ocudu
