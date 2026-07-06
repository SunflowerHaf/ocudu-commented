// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/resource_usage/power_consumption.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/ocudulog.h"


namespace ocudu {
namespace resource_usage_utils {


using energy_probe_time_point = std::chrono::high_resolution_clock::time_point;

/// Energy consumption expressed in micro Joules.

/// Energy consumption expressed in micro Joules.
struct energy_consumption {
  /// Energy consumed by CPU cores.
  /// Energy consumed by CPU cores.
  uint64_t cpu_core_consumed_uj;
  /// Energy consumed by package (it can include CPU core, GPU and other components).
  /// Energy consumed by package (it can include CPU core, GPU and other components).
  uint64_t package_consumed_uj;
};

/// Calculates a diff of micro Joules taking into account possible wrap around.

/// Calculates a diff of micro Joules taking into account possible wrap around.
uint64_t calculate_energy_diff(uint64_t current_uj, uint64_t previous_uj);

/// Helper struct used to store energy consumption at a given point of time.

/// Helper struct used to store energy consumption at a given point of time.
struct energy_snapshot {
  energy_consumption      probe;
  energy_probe_time_point probe_time;
};

/// Interface for reading energy consumption.

/// Interface for reading energy consumption.
class energy_consumption_reader
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~energy_consumption_reader() = default;

  /// Returns consumed energy in micro Joules.

  /// Returns consumed energy in micro Joules.
  virtual energy_consumption read_consumed_energy() const = 0;
};

/// Builds an energy consumption reader available in the system.

/// Builds an energy consumption reader available in the system.
std::unique_ptr<energy_consumption_reader> build_energy_consumption_reader(ocudulog::basic_logger& logger);


} // namespace resource_usage_utils
} // namespace ocudu
