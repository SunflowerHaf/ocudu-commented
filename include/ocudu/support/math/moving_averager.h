// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/math/moving_averager.h  (139 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <cstdint>
#include <type_traits>
#include <vector>


namespace ocudu {


namespace detail {


template <typename T>
class base_moving_average
{
public:
  base_moving_average() = default;
  base_moving_average(unsigned sliding_window_size) : sliding_window(sliding_window_size, 0) {}


  size_t size() const { return sliding_window.size(); }


protected:
  void push_sample(T sample)
  {
    sliding_window[write_pos++] = sample;
    if (write_pos >= sliding_window.size()) {
      write_pos = 0;
    }
  }


  void resize_window(unsigned sliding_window_size)
  {
    sliding_window.resize(sliding_window_size);
    clear_samples();
  }


  void clear_samples()
  {
    std::fill(sliding_window.begin(), sliding_window.end(), 0);
    write_pos = 0;
  }


  std::vector<T> sliding_window;


  unsigned write_pos = 0;
};


} // namespace detail

/// Implementation of a moving average using a sliding window.

/// Implementation of a moving average using a sliding window.
template <typename T>
class moving_averager : public detail::base_moving_average<T>
{
  static_assert(std::is_integral_v<T>, "T must be integral to avoid loss of precision");


  using base_type = detail::base_moving_average<T>;


public:
  using base_type::base_type;


  void push(T sample)
  {
    sum_samples -= this->sliding_window[this->write_pos];
    sum_samples += sample;
    this->push_sample(sample);
  }


  double average() const { return sum_samples / static_cast<double>(this->size()); }


  void clear()
  {
    this->clear_samples();
    sum_samples = 0;
  }


  void resize(unsigned sliding_window_size)
  {
    if (sliding_window_size == this->size()) {
      return;
    }
    this->resize_window(sliding_window_size);
    sum_samples = 0;
  }


private:
  using sum_samples_type = std::conditional_t<std::is_unsigned_v<T>, uint64_t, int64_t>;


  sum_samples_type sum_samples = 0;
};

/// Specialization of moving_averager for the double case.
///
/// The main difference is that after N samples, where N is the size of the sliding window, the average is recalculated.

/// Specialization of moving_averager for the double case.
///
/// The main difference is that after N samples, where N is the size of the sliding window, the average is recalculated.
template <>
class moving_averager<double> : public detail::base_moving_average<double>
{
  using base_type = detail::base_moving_average<double>;


public:
  using base_type::base_type;


  void push(double sample)
  {
    sum_samples += sample - sliding_window[write_pos];
    push_sample(sample);
    if (write_pos == 0) {
      // Double operations suffer from loss of precision. So, the precision error can accummulate in \c sum_samples.
      // To avoid this, we recompute the average inside the sliding window every N number of samples, where the N is
      // the size of the sliding window.
      // Double operations suffer from loss of precision. So, the precision error can accummulate in \c sum_samples.
      // To avoid this, we recompute the average inside the sliding window every N number of samples, where the N is
      // the size of the sliding window.
      sum_samples = 0;
      for (double samp : sliding_window) {
        sum_samples += samp;
      }
    }
  }


  double average() const { return sum_samples / static_cast<double>(size()); }


  void clear()
  {
    this->clear_samples();
    sum_samples = 0;
  }


  void resize(unsigned sliding_window_size)
  {
    if (sliding_window_size == this->size()) {
      return;
    }
    this->resize_window(sliding_window_size);
    sum_samples = 0;
  }


private:
  double sum_samples = 0;
};


} // namespace ocudu
