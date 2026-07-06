// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/support/engineering_notation.h  (111 lines)
//
// INTERFACE HEADER — include/ocudu/support
// Support library interface headers (~131 files): task_executor (the abstract interface every thread pool implements — just a defer() method), timer_manager and unique_timer (the central timer abstraction), io_broker (non-blocking I/O), signal_observer/signal_dispatcher, byte_buffer and byte_buffer_slice interfaces, config_parsers, cli11_utils, engineering_notation formatter, async_task and async_task_runner, stop_event and stop_token, and many more general-purpose C++ utilities.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "fmt/core.h"
#include <array>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <string>


namespace ocudu {

/// \file
/// \brief Helper functions to print numbers in engineering notation, for pretty printing.


/// \file
/// \brief Helper functions to print numbers in engineering notation, for pretty printing.

inline std::string scaled_fmt_integer(uint64_t num, bool right_align)
{
  static constexpr std::array<const char*, 8> suffixes = {"", "k", "M", "G", "T", "P", "E", "Z"};
  static const std::array<uint64_t, 8>        max_nums = []() {
    std::array<uint64_t, 8> nums{0};
    for (unsigned i = 0, e = nums.size(); i != e; ++i) {
      nums[i] = (uint64_t)std::pow(10, i * 3);
    }
    return nums;
  }();


  if (num < max_nums[1]) {
    return right_align ? fmt::format("{:>6}", num) : fmt::format("{}", num);
  }


  for (unsigned i = 1, e = max_nums.size() - 1; i != e; ++i) {
    if (num < max_nums[i + 1]) {
      if (right_align) {
        return fmt::format("{:>5.3g}{}", num / static_cast<double>(max_nums[i]), suffixes[i]);
      }
      return fmt::format("{:.3g}{}", num / static_cast<double>(max_nums[i]), suffixes[i]);
    }
  }


  return "Invalid number";
}


inline std::string float_to_string(float f, int digits, int field_width, bool align_right)
{
  std::ostringstream os;
  int                precision;


  if (std::isnan(f) || std::abs(f) < 0.0001f) {
    f         = 0.f;
    precision = digits - 1;
  } else {
    precision = digits - (int)(std::log10(std::abs(f + 0.0001f)) - 2 * DBL_EPSILON);
  }


  precision = std::max(precision, 0);


  if (align_right) {
    os << std::setw(field_width) << std::fixed << std::setprecision(precision) << f;
  } else {
    os << std::fixed << std::setprecision(precision) << f;
  }
  return os.str();
}


inline std::string float_to_eng_string(float f, int digits, bool align_right)
{
  static constexpr char const* prefixes[2][9] = {
      {
          "",
          "m",
          "u",
          "n",
          "p",
          "f",
          "a",
          "z",
          "y",
      },
      {
          "",
          "k",
          "M",
          "G",
          "T",
          "P",
          "E",
          "Z",
          "Y",
      },
  };


  const int degree = (f == 0.f) ? 0 : std::lrint(std::floor(std::log10(std::abs(f)) / 3));


  std::string factor;


  if (std::abs(degree) < 9) {
    factor = prefixes[(degree < 0) ? 0 : 1][std::abs(degree)];
  } else {
    return "failed";
  }


  const double scaled = f * std::pow(1000.0, -degree);
  if (degree != 0) {
    return float_to_string(scaled, digits, 5, align_right) + factor;
  }
  return " " + float_to_string(scaled, digits, 5 - factor.length(), align_right) + factor;
}
} // namespace ocudu
