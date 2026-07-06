// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1u/cu_up/f1u_config.h  (55 lines)
//
// INTERFACE HEADER — include/ocudu/f1u
// F1-U interface headers: the DU-side and CU-UP-side F1-U gateway abstractions, the f1u_du_gateway and f1u_cu_up_gateway interfaces, and the TEID (tunnel endpoint) pool interface used to allocate unique tunnel identifiers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/timers.h"
#include "fmt/format.h"
#include <chrono>


namespace ocudu {
namespace ocuup {


class f1u_metrics_notifier;

/// \brief Configurable parameters of the F1-U bearer in the CU-UP

/// \brief Configurable parameters of the F1-U bearer in the CU-UP
struct f1u_config {
  /// Log a warning instead of an info message whenever a PDU is dropped.
  /// Log a warning instead of an info message whenever a PDU is dropped.
  bool warn_on_drop = true;
  /// Backoff timer for piggy-packing of discard blocks.
  /// Backoff timer for piggy-packing of discard blocks.
  std::chrono::milliseconds dl_t_notif_timer{5};
  uint32_t                  queue_size = 8192;
  uint32_t                  batch_size = 256;


  timer_duration        metrics_period   = std::chrono::milliseconds{0};
  f1u_metrics_notifier* metrics_notifier = nullptr;
};


} // namespace ocuup
} // namespace ocudu


namespace fmt {

// F1-U config formatter

// F1-U config formatter
template <>
struct formatter<ocudu::ocuup::f1u_config> {
  template <typename ParseContext>
  auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }


  template <typename FormatContext>
  auto format(ocudu::ocuup::f1u_config cfg, FormatContext& ctx) const
  {
    return format_to(ctx.out(),
                     "warn_on_drop={} dl_t_notif_timer={}ms queue_size={} batch_size={}",
                     cfg.warn_on_drop,
                     cfg.dl_t_notif_timer.count(),
                     cfg.queue_size,
                     cfg.batch_size);
  }
};


} // namespace fmt
