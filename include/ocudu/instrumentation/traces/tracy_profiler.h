// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/instrumentation/traces/tracy_profiler.h  (14 lines)
//
// INTERFACE HEADER — include/ocudu/instrumentation
// Instrumentation hook interfaces: binary event tracing types and the tracer_context. Used to mark code events with timestamps for off-line performance analysis. Empty/no-op in production builds without instrumentation enabled.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"


#define OCUDU_ZONE_SCOPED_NC ZoneScopedNC
#else
#define OCUDU_ZONE_SCOPED_NC(name, color)                                                                              \
  do {                                                                                                                 \
  } while (0)
#endif
