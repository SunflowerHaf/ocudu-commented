// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/rate_limiting/token_bucket.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/support/rate_limiting/token_bucket_config.h"
#include "ocudu/support/timers.h"
#include <cstdint>


namespace ocudu {

/// \brief Rate limiter class that implements a rate limiter
/// based on the token bucket algorithm.
///

/// \brief Rate limiter class that implements a rate limiter
/// based on the token bucket algorithm.
///
class token_bucket
{
public:
  token_bucket(token_bucket_config cfg);

  /// Consume tokens from the bucket.
  /// \return False if there were not enough available tokens, true otherwise.

  /// Consume tokens from the bucket.
  /// \return False if there were not enough available tokens, true otherwise.
  bool consume(uint32_t tokens);


  void stop();


private:
  /// Refill tokens to the bucket.
  /// It will be called internally by the refill timer.
  /// Refill tokens to the bucket.
  /// It will be called internally by the refill timer.
  void refill(uint32_t tokens);


  uint32_t max_tokens;
  uint32_t tokens_in_bucket;


  unique_timer refill_timer;


  bool stopped = false;
};
} // namespace ocudu
