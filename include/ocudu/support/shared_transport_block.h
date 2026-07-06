// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/shared_transport_block.h  (69 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/span.h"
#include <atomic>
#include <utility>


namespace ocudu {

/// Manages the shared ownership of a Transport Block buffer giving access to a view of it.

/// Manages the shared ownership of a Transport Block buffer giving access to a view of it.
class shared_transport_block
{
  span<const uint8_t>    buffer;
  std::atomic<unsigned>* ref_cnt = nullptr;


public:
  shared_transport_block() = default;


  explicit shared_transport_block(span<const uint8_t>    buffer_,
                                  std::atomic<unsigned>* ref_cnt_     = nullptr,
                                  bool                   do_increment = true) :
    buffer(buffer_), ref_cnt(ref_cnt_)
  {
    if (ref_cnt && do_increment) {
      ref_cnt->fetch_add(1, std::memory_order::memory_order_relaxed);
    }
  }


  ~shared_transport_block() { release(); }


  shared_transport_block(const shared_transport_block& other) : buffer(other.buffer), ref_cnt(other.ref_cnt)
  {
    if (ref_cnt) {
      ref_cnt->fetch_add(1, std::memory_order::memory_order_relaxed);
    }
  }


  shared_transport_block& operator=(const shared_transport_block& other) = delete;


  shared_transport_block(shared_transport_block&& other) noexcept :
    buffer(std::exchange(other.buffer, {})), ref_cnt(std::exchange(other.ref_cnt, nullptr))
  {
  }


  shared_transport_block& operator=(shared_transport_block&& other) noexcept
  {
    buffer = std::exchange(other.buffer, {});


    release();
    ref_cnt = std::exchange(other.ref_cnt, nullptr);
    return *this;
  }

  /// Releases the ownership of this buffer.

  /// Releases the ownership of this buffer.
  void release()
  {
    if (ref_cnt) {
      ref_cnt->fetch_sub(1, std::memory_order::memory_order_acq_rel);
      ref_cnt = nullptr;
    }
  }

  /// Returns a view of the underlying buffer.

  /// Returns a view of the underlying buffer.
  span<const uint8_t> get_buffer() const { return buffer; }
};


} // namespace ocudu
