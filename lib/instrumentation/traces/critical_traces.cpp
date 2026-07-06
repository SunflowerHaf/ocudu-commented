// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/instrumentation/traces/critical_traces.cpp  (6 lines)
//
// LIBRARY: lib/instrumentation
// Lightweight diagnostics hook — provides macros/functions to mark events in the binary with timestamps for performance investigation. Not a dependency at runtime unless instrumentation is enabled.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/instrumentation/traces/critical_traces.h"


ocudu::file_event_tracer<true> ocudu::general_critical_tracer;
