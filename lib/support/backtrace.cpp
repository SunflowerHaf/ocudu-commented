// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/support/backtrace.cpp  (21 lines)
//
// LIBRARY: lib/support
// General-purpose C++ utilities: async task executors, thread pools, timer manager, memory pools, span/expected/bounded_integer types, signal dispatcher, config parsers, format helpers, synchronisation primitives (stop_event, sync_event), and versioning. Not 5G-specific — these could be a standalone C++ utility library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/support/backtrace.h"


#ifdef HAVE_BACKWARD
#include "Backward/backward.hpp"


void ocudu::enable_backtrace()
{
  static backward::SignalHandling sh;
}


#else // HAVE_BACKWARD


void ocudu::enable_backtrace()
{
  // Ignore.
  // Ignore.
}


#endif // HAVE_BACKWARD
