// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_lower_phy_downlink_handler_impl.h
 * @brief Routes downlink resource grids from the upper PHY to the correct lower PHY sector.
 *
 * The RU's downlink plane handler is the entry point for downlink data flowing
 * from the upper PHY into the radio stack. This class implements that interface
 * and simply routes each incoming resource grid to the correct cell's lower
 * PHY downlink handler, based on the sector index in the resource_grid_context.
 */

#pragma once


#include "ocudu/phy/support/shared_resource_grid.h" ///< shared_resource_grid — reference-counted grid handle
#include "ocudu/ru/ru_downlink_plane.h" ///< ru_downlink_plane_handler — the base interface


namespace ocudu {


class lower_phy_downlink_handler;

/// Radio Unit to lower physical layer downlink handler implementation.

/**
 * @brief Routes downlink resource grids to the correct cell's lower PHY.
 *
 * One instance handles all configured cells, using a per-sector handler
 * lookup table built from the lower PHY sectors.
 */
class ru_lower_phy_downlink_handler_impl : public ru_downlink_plane_handler
{
public:
  /**
   * @param handlers_  One lower_phy_downlink_handler pointer per cell sector,
   *                   indexed by sector ID.
   */
  explicit ru_lower_phy_downlink_handler_impl(std::vector<lower_phy_downlink_handler*> handlers_) :
    handlers(std::move(handlers_))
  {
  }

  // See interface for documentation.

  /**
   * @brief Forwards a downlink resource grid to the correct sector's lower PHY.
   *
   * Called by the upper PHY once per slot with the resource grid containing
   * the data to transmit. The grid is passed by shared_resource_grid (a
   * reference-counted handle) to avoid copying the (potentially large)
   * resource grid data.
   *
   * @param context  Identifies which sector and slot this grid is for.
   * @param grid     The resource grid containing the modulated symbols to transmit.
   */
  void handle_dl_data(const resource_grid_context& context, const shared_resource_grid& grid) override;


private:
  /// Lookup table: sector index → that sector's lower PHY downlink handler.
  std::vector<lower_phy_downlink_handler*> handlers;
};


} // namespace ocudu
