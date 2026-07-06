// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/enum_utils.h  (24 lines)
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

/// Convert an enum type to its respective underlying integer type.

/// Convert an enum type to its respective underlying integer type.
template <typename Enum>
auto to_value(Enum e) -> std::underlying_type_t<Enum>
{
  return static_cast<std::underlying_type_t<Enum>>(e);
}

/// Convert an underlying integer type to an enum type.

/// Convert an underlying integer type to an enum type.
template <typename Enum>
Enum to_enum(std::underlying_type_t<Enum> e)
{
  return static_cast<std::underlying_type_t<Enum>>(e);
}


} // namespace ocudu
