// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/instrumentation/traces/up_traces.h  (21 lines)
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

/// Set to true for enabling user-plane related traces.

/// Set to true for enabling user-plane related traces.
#ifndef OCUDU_UP_TRACE
constexpr bool UP_TRACE_ENABLED = false;
#else
constexpr bool UP_TRACE_ENABLED = true;
#endif

/// UP event tracing. This tracer is used to analyze latencies in the CU-UP/DU high processing
/// of the user plane traffic.

/// UP event tracing. This tracer is used to analyze latencies in the CU-UP/DU high processing
/// of the user plane traffic.
extern file_event_tracer<UP_TRACE_ENABLED> up_tracer;


} // namespace ocudu
