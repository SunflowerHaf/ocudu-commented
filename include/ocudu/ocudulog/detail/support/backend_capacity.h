// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocudulog/detail/support/backend_capacity.h  (9 lines)
//
// INTERFACE HEADER — include/ocudu/ocudulog
// Logging framework public interfaces: basic_logger (the main per-channel logger type with set_level() and log-level check methods), log_channel (a single named output channel), the ocudulog global registry (fetch_basic_logger(), fetch_log_channel()), sink interfaces, and the basic_levels enum (none, debug, info, warning, error).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once

/// Take this default value if users did not specify any custom size.

/// Take this default value if users did not specify any custom size.
#ifndef OCUDULOG_QUEUE_CAPACITY
#define OCUDULOG_QUEUE_CAPACITY 8192
#endif
