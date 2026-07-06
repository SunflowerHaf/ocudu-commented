// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_lower_phy_timing_adapter.h
 * @brief Translates lower PHY timing events into RU timing notifications.
 *
 * The lower PHY fires three distinct timing events as it processes the
 * incoming sample stream, each marking a different point in the slot:
 *
 *   on_tti_boundary:           A new slot (TTI — Transmission Time Interval)
 *                              has begun. This is the main "tick" that drives
 *                              the DU's MAC scheduler.
 *
 *   on_ul_half_slot_boundary:  The uplink samples for the first half of a
 *                              slot are ready. Used for early processing
 *                              (e.g. starting PUCCH decoding before the full
 *                              slot has arrived, reducing latency).
 *
 *   on_ul_full_slot_boundary:  The uplink samples for the entire slot are
 *                              ready — full PUSCH/PUCCH data is available.
 *
 * This adapter exists mainly to translate between the lower PHY's internal
 * timing context type and the simpler types the RU's external timing
 * notifier interface expects.
 */

#pragma once


#include "ru_radio_event_handler.h"
#include "ocudu/phy/lower/lower_phy_timing_notifier.h" ///< Base interface this class implements
#include "ocudu/ru/ru_timing_notifier.h" ///< RU-level timing notifier (forwarded to)


namespace ocudu {

/// Implements a lower physical layer to Radio Unit timing adapter.

/**
 * @brief Adapts lower PHY timing notifications into RU timing notifications.
 */
class ru_lower_phy_timing_adapter : public lower_phy_timing_notifier
{
public:
  /**
   * @param timing_handler_  The RU-level timing notifier to forward events to.
   *                         Ultimately drives the DU High's MAC scheduler.
   */
  explicit ru_lower_phy_timing_adapter(ru_timing_notifier& timing_handler_) : timing_handler(timing_handler_) {}

  // See interface for documentation.

  /**
   * @brief Called by the lower PHY when a new slot (TTI) boundary occurs.
   *
   * This is the main timing tick — forwarded with the slot number and
   * the wall-clock time point at which the boundary occurred. The DU High
   * uses this to drive the MAC scheduler for the new slot.
   *
   * @param context  Contains the new slot number and the timestamp.
   */
  void on_tti_boundary(const lower_phy_timing_context& context) override
  {
    timing_handler.on_tti_boundary(tti_boundary_context{.slot = context.slot, .time_point = context.time_point});
  }

  // See interface for documentation.

  /**
   * @brief Called when the first half-slot of uplink samples is ready.
   *
   * The slot number is stripped of its "hyper-SFN" component (a wraparound
   * counter used internally by the lower PHY for very long-running counts)
   * before being forwarded, since the RU-level interface only needs the
   * slot identity within the current hyper-frame cycle.
   *
   * @param context  Contains the slot number for the half-slot boundary.
   */
  void on_ul_half_slot_boundary(const lower_phy_timing_context& context) override
  {
    timing_handler.on_ul_half_slot_boundary(context.slot.without_hyper_sfn());
  }

  // See interface for documentation.

  /**
   * @brief Called when the full slot of uplink samples is ready.
   *
   * @param context  Contains the slot number for the full-slot boundary.
   */
  void on_ul_full_slot_boundary(const lower_phy_timing_context& context) override
  {
    timing_handler.on_ul_full_slot_boundary(context.slot.without_hyper_sfn());
  }


private:
  /// The RU-level timing notifier — events are forwarded here.
  ru_timing_notifier& timing_handler;
};


} // namespace ocudu
