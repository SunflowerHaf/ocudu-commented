// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/adt/mpmc_queue.h  (96 lines)
//
// INTERFACE HEADER — include/ocudu/adt
// Abstract Data Types: the codebase's custom container and utility types. Includes bounded_integer (integer with compile-time min/max), expected<T,E> (Result type — either a value or an error, like std::expected), optional, span, static_vector, bit_buffer, circular_map, byte_buffer and byte_buffer_chain (zero-copy scatter-gather buffers), ring_buffer, tiny_optional, type_list, strong_type, and more. Used pervasively throughout all layers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "rigtorp/MPMCQueue.h"
#include "ocudu/adt/detail/concurrent_queue_helper.h"
#include "ocudu/adt/detail/concurrent_queue_params.h"
#include <chrono>


namespace ocudu {

/// Specialization for lockfree MPMC without a blocking mechanism.

/// Specialization for lockfree MPMC without a blocking mechanism.
template <typename T>
class concurrent_queue<T, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>
{
public:
  using value_type                                           = T;
  static constexpr concurrent_queue_policy      queue_policy = concurrent_queue_policy::lockfree_mpmc;
  static constexpr concurrent_queue_wait_policy wait_policy  = concurrent_queue_wait_policy::non_blocking;
  using consumer_type                                        = detail::basic_queue_consumer<concurrent_queue, T>;


  explicit concurrent_queue(size_t qsize) : queue(qsize) {}


  [[nodiscard]] bool try_push(const T& elem) { return queue.try_push(elem); }
  [[nodiscard]] bool try_push(T&& elem) { return queue.try_push(std::move(elem)); }
  template <typename U>
  [[nodiscard]] size_t try_push_bulk(span<U> batch)
  {
    return detail::queue_helper::try_push_bulk_generic(*this, batch);
  }
  template <typename U>
  void push_blocking(U&& elem)
  {
    queue.push(std::forward<U>(elem));
  }


  [[nodiscard]] bool try_pop(T& elem) { return queue.try_pop(elem); }


  [[nodiscard]] size_t try_pop_bulk(span<T> batch) { return detail::queue_helper::try_pop_bulk_generic(*this, batch); }


  [[nodiscard]] size_t size() const
  {
    // Note: MPMCqueue size can be negative.
    // Note: MPMCqueue size can be negative.
    ptrdiff_t ret = queue.size();
    return static_cast<size_t>(std::max(ret, static_cast<ptrdiff_t>(0)));
  }


  [[nodiscard]] bool empty() const { return queue.empty(); }


  [[nodiscard]] size_t capacity() const { return queue.capacity(); }

  /// Creates a consumer for this queue.

  /// Creates a consumer for this queue.
  consumer_type create_consumer() { return consumer_type(*this); }


protected:
  ::rigtorp::MPMCQueue<T> queue;
};

/// Specialization for lockfree MPMC using a sleep as the blocking mechanism.

/// Specialization for lockfree MPMC using a sleep as the blocking mechanism.
template <typename T>
class concurrent_queue<T, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::sleep>
  : private concurrent_queue<T, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>,
    public detail::queue_sleep_crtp<
        concurrent_queue<T, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::sleep>>
{
  using nonblocking_base_type =
      concurrent_queue<T, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;
  using sleep_base_type = detail::queue_sleep_crtp<concurrent_queue>;


public:
  using value_type                                           = T;
  static constexpr concurrent_queue_policy      queue_policy = concurrent_queue_policy::lockfree_mpmc;
  static constexpr concurrent_queue_wait_policy wait_policy  = concurrent_queue_wait_policy::sleep;
  using consumer_type                                        = detail::basic_queue_consumer<concurrent_queue, T>;


  explicit concurrent_queue(size_t qsize, std::chrono::microseconds sleep_time_ = std::chrono::microseconds{0}) :
    nonblocking_base_type(qsize), sleep_base_type(sleep_time_)
  {
  }


  using nonblocking_base_type::capacity;
  using nonblocking_base_type::empty;
  using nonblocking_base_type::size;
  using nonblocking_base_type::try_pop;
  using nonblocking_base_type::try_push;
  using sleep_base_type::call_on_pop_blocking;
  using sleep_base_type::pop_blocking;
  using sleep_base_type::push_blocking;
  using sleep_base_type::request_stop;

  /// Creates a consumer for this queue.

  /// Creates a consumer for this queue.
  consumer_type create_consumer() { return consumer_type(*this); }
};


} // namespace ocudu
