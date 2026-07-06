// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/instrumentation/traces/du_traces.cpp  (12 lines)
//
// LIBRARY: lib/instrumentation
// Lightweight diagnostics hook — provides macros/functions to mark events in the binary with timestamps for performance investigation. Not a dependency at runtime unless instrumentation is enabled.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/instrumentation/traces/du_traces.h"


ocudu::file_event_tracer<ocudu::L1_DL_TRACE_ENABLED> ocudu::l1_common_tracer;


ocudu::file_event_tracer<ocudu::L1_DL_TRACE_ENABLED> ocudu::l1_dl_tracer;


ocudu::file_event_tracer<ocudu::L1_UL_TRACE_ENABLED> ocudu::l1_ul_tracer;


ocudu::file_event_tracer<ocudu::L2_TRACE_ENABLED> ocudu::l2_tracer;
