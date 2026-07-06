// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/sysinfo.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocudulog/logger.h"
#include <optional>


namespace ocudu {


struct os_sched_affinity_bitmask;

/// \brief Check whether the CPU scaling governor is set to performance.
///
/// \param[in] logger to print warnings.
/// \return True if we were able to read the sysfs scaling governor information.

/// \brief Check whether the CPU scaling governor is set to performance.
///
/// \param[in] logger to print warnings.
/// \return True if we were able to read the sysfs scaling governor information.
bool check_cpu_governor(ocudulog::basic_logger& logger);

/// \brief Check whether the DRM KMS polling is set.
///
/// \param[in] logger to print warnings.
/// \return True if we were able to read the sysfs for the DRM KMS polling information.

/// \brief Check whether the DRM KMS polling is set.
///
/// \param[in] logger to print warnings.
/// \return True if we were able to read the sysfs for the DRM KMS polling information.
bool check_drm_kms_polling(ocudulog::basic_logger& logger);


} // namespace ocudu
