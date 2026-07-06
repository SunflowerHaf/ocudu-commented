// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/rate_limiting/token_bucket_config.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/timers.h"
#include <chrono>


namespace ocudu {


struct token_bucket_config {
  uint32_t                  refill_token;
  std::chrono::milliseconds refill_period;
  uint32_t                  max_tokens;
  timer_factory             timer_f;
};


inline token_bucket_config generate_token_bucket_config(uint64_t                  avg_rate_bps,
                                                        uint64_t                  max_rate_bps,
                                                        std::chrono::milliseconds refill_period,
                                                        timer_factory             timer_f)
{
  token_bucket_config cfg = {};
  cfg.refill_period       = refill_period;
  cfg.refill_token        = avg_rate_bps * refill_period.count() / 8 * 1e-3;
  cfg.max_tokens          = max_rate_bps * refill_period.count() / 8 * 1e-3;
  cfg.timer_f             = timer_f;
  return cfg;
}


} // namespace ocudu
