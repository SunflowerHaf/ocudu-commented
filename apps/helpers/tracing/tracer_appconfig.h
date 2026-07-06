// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/tracing/tracer_appconfig.h
//
// Purpose (plain English):
//   Configuration for the Tracy-style executor tracing feature. When enabled,
//   every time a task is pushed onto or dequeued from a thread-pool executor,
//   a timing record is written to a binary trace file. The resulting file can
//   be opened in a trace viewer to see exactly which executor ran which task,
//   when, and for how long — essential for diagnosing real-time scheduling
//   jitter.
//
//   filename — empty string means tracing is disabled (no file, no overhead).
//   max_tracing_events_per_file — rolls over to a new file after this many
//     events (0 = no rollover).
//   nof_tracing_events_after_severe — if non-zero, only write the last N
//     events *after* a "severe" (real-time overrun) event, discarding
//     history before it. Keeps trace files small while capturing the context
//     around overruns.
// =============================================================================
#pragma once

#include <string>


namespace ocudu {

/// Configuration of the tracing service.
struct tracer_appconfig {
  /// Set to a valid file path to enable tracing and write the trace to the file.
  std::string filename; ///< Trace output file (empty = disabled).
  /// Maximum number of events per file. Set to zero for no limit.
  unsigned max_tracing_events_per_file = 1e6; ///< Rollover threshold (0 = unlimited).
  /// Number of events to write prior to a severe event. Set to zero for writing all events.
  unsigned nof_tracing_events_after_severe = 0; ///< Post-severe capture window (0 = all).
};

} // namespace ocudu
