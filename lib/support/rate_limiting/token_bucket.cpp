// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/support/rate_limiting/token_bucket.cpp  (64 lines)
//
// LIBRARY: lib/support
// General-purpose C++ utilities: async task executors, thread pools, timer manager, memory pools, span/expected/bounded_integer types, signal dispatcher, config parsers, format helpers, synchronisation primitives (stop_event, sync_event), and versioning. Not 5G-specific — these could be a standalone C++ utility library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/support/rate_limiting/token_bucket.h"
#include "ocudu/support/compiler.h"
#include "ocudu/support/ocudu_assert.h"
#include <cstdint>


using namespace ocudu;


token_bucket::token_bucket(token_bucket_config cfg) : max_tokens(cfg.max_tokens), tokens_in_bucket(cfg.max_tokens)
{
  ocudu_assert(cfg.refill_token != 0, "Incorrectly configured bucket. refill_token=0 ");
  ocudu_assert(cfg.max_tokens != 0, "Incorrectly configured bucket. max_tokens=0 ");
  ocudu_assert(cfg.refill_token <= max_tokens,
               "Incorrectly configured bucket. refill_token={} > max_tokens={}",
               cfg.refill_token,
               cfg.max_tokens);
  refill_timer = cfg.timer_f.create_timer();
  refill_timer.set(cfg.refill_period,
                   [this, refill_token = cfg.refill_token](timer_id_t /*timer_id*/) { refill(refill_token); });
  refill_timer.run();
}


bool token_bucket::consume(uint32_t tokens)
{
  if (OCUDU_UNLIKELY(stopped)) {
    return false;
  }


  int32_t tokens_left = tokens_in_bucket - tokens;
  if (tokens_left < 0) {
    return false;
  }
  tokens_in_bucket = tokens_left;


  if (not refill_timer.is_running()) {
    refill_timer.run(); // restart refill timer
  }


  return true;
}


void token_bucket::refill(uint32_t tokens)
{
  if (stopped) {
    return;
  }
  uint32_t tokens_added = tokens_in_bucket + tokens;
  tokens_in_bucket      = std::min(max_tokens, tokens_added);
  if (tokens_in_bucket == max_tokens) {
    refill_timer.stop(); // stop refill timer. it will be restarted on the next consume.
  } else {
    refill_timer.run(); // restart refill timer
  }
}


void token_bucket::stop()
{
  if (not stopped) {
    refill_timer.stop();
    stopped = true;
  }
}
