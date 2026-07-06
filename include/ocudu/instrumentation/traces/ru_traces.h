// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/instrumentation/traces/ru_traces.h  (20 lines)
//
// INTERFACE HEADER — include/ocudu/instrumentation
// Instrumentation hook interfaces: binary event tracing types and the tracer_context. Used to mark code events with timestamps for off-line performance analysis. Empty/no-op in production builds without instrumentation enabled.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/tracing/event_tracing.h"


namespace ocudu {

/// Set to true for enabling radio unit trace.

/// Set to true for enabling radio unit trace.
#ifndef OCUDU_RU_TRACE
constexpr bool RU_TRACE_ENABLED = false;
#else
constexpr bool RU_TRACE_ENABLED = true;
#endif

/// RU event tracing. This tracer is used to analyze latencies in the RU processing.

/// RU event tracing. This tracer is used to analyze latencies in the RU processing.
extern file_event_tracer<RU_TRACE_ENABLED> ru_tracer;


} // namespace ocudu
