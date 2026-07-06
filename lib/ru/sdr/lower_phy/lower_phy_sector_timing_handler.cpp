// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_sector_timing_handler.cpp
 * @brief Implementation of the null-object timing notifier wrapper.
 */

#include "lower_phy_sector_timing_handler.h"


using namespace ocudu;


namespace {

/// Lower PHY sector timing notifier dummy implementation.

/**
 * @brief No-op timing notifier — silently discards all timing events.
 *
 * Used for sectors that should not drive the shared DU timer (all sectors
 * except the first in a multi-cell deployment).
 */
class lower_phy_sector_timing_notifier_dummy : public lower_phy_timing_notifier
{
public:
  // See interface for documentation.
  void on_tti_boundary(const lower_phy_timing_context& context) override {}

  // See interface for documentation.
  void on_ul_half_slot_boundary(const lower_phy_timing_context& context) override {}

  // See interface for documentation.
  void on_ul_full_slot_boundary(const lower_phy_timing_context& context) override {}
};


} // namespace


/// Single shared instance of the dummy notifier — reused across all sectors
/// that have no real timing notifier, avoiding per-sector allocation.
static lower_phy_sector_timing_notifier_dummy dummy_notifier;


/**
 * @brief Constructor. Selects the real notifier if provided, otherwise the shared dummy.
 *
 * @param notifier_  The real timing notifier, or nullptr.
 */
lower_phy_sector_timing_handler::lower_phy_sector_timing_handler(lower_phy_timing_notifier* notifier_) :
  notifier(notifier_ ? notifier_ : &dummy_notifier)
{
}


/// Forwards the TTI boundary event to whichever notifier is currently selected.
void lower_phy_sector_timing_handler::on_tti_boundary(const lower_phy_timing_context& context)
{
  notifier->on_tti_boundary(context);
}


/// Forwards the uplink half-slot boundary event.
void lower_phy_sector_timing_handler::on_ul_half_slot_boundary(const lower_phy_timing_context& context)
{
  notifier->on_ul_half_slot_boundary(context);
}


/// Forwards the uplink full-slot boundary event.
void lower_phy_sector_timing_handler::on_ul_full_slot_boundary(const lower_phy_timing_context& context)
{
  notifier->on_ul_full_slot_boundary(context);
}
