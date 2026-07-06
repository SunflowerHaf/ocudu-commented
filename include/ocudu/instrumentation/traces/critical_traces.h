// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/instrumentation/traces/critical_traces.h  (14 lines)
//
// INTERFACE HEADER — include/ocudu/instrumentation
// Instrumentation hook interfaces: binary event tracing types and the tracer_context. Used to mark code events with timestamps for off-line performance analysis. Empty/no-op in production builds without instrumentation enabled.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ran/du_types.h"
#include "ocudu/support/tracing/rusage_trace_recorder.h"


namespace ocudu {

/// General event tracing for critical events such as real-time errors.

/// General event tracing for critical events such as real-time errors.
extern file_event_tracer<true> general_critical_tracer;


} // namespace ocudu
