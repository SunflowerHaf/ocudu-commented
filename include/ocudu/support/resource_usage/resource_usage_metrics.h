// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/resource_usage/resource_usage_metrics.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/units.h"


namespace ocudu {

/// CPU usage of a measured block, e.g. some processing chain executed in a UNIX thread, or the CPU usage of the entire
/// UNIX process.

/// CPU usage of a measured block, e.g. some processing chain executed in a UNIX thread, or the CPU usage of the entire
/// UNIX process.
struct cpu_metrics {
  float cpu_usage_percentage;
  float cpu_utilization_nof_cpus;
};

/// Memory consumption of a UNIX process.

/// Memory consumption of a UNIX process.
struct memory_metrics {
  units::bytes memory_usage;
};

/// Aggregates CPU usage of a measured block and memory consumption of the UNIX process.

/// Aggregates CPU usage of a measured block and memory consumption of the UNIX process.
struct resource_usage_metrics {
  cpu_metrics    cpu_stats;
  memory_metrics memory_stats;
  double         power_usage_watts;
};


} // namespace ocudu
