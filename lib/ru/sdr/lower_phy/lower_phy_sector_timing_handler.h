// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_sector_timing_handler.h
 * @brief Safe wrapper around an optional timing notifier (null-object pattern).
 *
 * In a multi-cell deployment, only the first sector is configured with a real
 * timing notifier — all cells share one slot clock, so only one notification
 * path is needed to drive the DU's shared timer (see ru_factory_sdr_impl.cpp,
 * where `timing_notifier = sector_id ? nullptr : &ru->get_timing_notifier()`).
 *
 * Rather than having the lower PHY's internal code check for a null pointer
 * every time it wants to fire a timing event, this class implements the
 * "null object pattern": if no real notifier was provided, it transparently
 * substitutes a no-op dummy notifier. This means the lower PHY's timing-firing
 * code can always call through this wrapper without any null checks.
 */

#pragma once


#include "ocudu/phy/lower/lower_phy_timing_notifier.h" ///< Base interface this class implements/wraps


namespace ocudu {


/**
 * @brief Forwards timing events to a real notifier if one was configured,
 *        otherwise silently absorbs them via a dummy no-op notifier.
 */
class lower_phy_sector_timing_handler : public lower_phy_timing_notifier
{
  /// Either the real notifier (sector 0) or a pointer to the shared dummy
  /// notifier (all other sectors).
  lower_phy_timing_notifier* notifier = nullptr;


public:
  /**
   * @param notifier_  The real timing notifier, or nullptr if this sector
   *                   should not fire timing events.
   */
  explicit lower_phy_sector_timing_handler(lower_phy_timing_notifier* notifier_);

  // See interface for documentation.

  /// Forwards (or absorbs) the TTI boundary notification.
  void on_tti_boundary(const lower_phy_timing_context& context) override;

  // See interface for documentation.

  /// Forwards (or absorbs) the uplink half-slot boundary notification.
  void on_ul_half_slot_boundary(const lower_phy_timing_context& context) override;

  // See interface for documentation.

  /// Forwards (or absorbs) the uplink full-slot boundary notification.
  void on_ul_full_slot_boundary(const lower_phy_timing_context& context) override;
};


} // namespace ocudu
