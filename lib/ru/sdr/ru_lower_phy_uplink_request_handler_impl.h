// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_lower_phy_uplink_request_handler_impl.h
 * @brief Routes uplink slot/PRACH requests from the upper PHY to the correct lower PHY sector.
 *
 * The RU's uplink plane handler is the entry point for uplink requests issued
 * by the upper PHY. Two types of requests are routed:
 *
 *   - PRACH occasion requests: "please capture the random access window for
 *     this slot, I want to detect any UEs trying to connect."
 *
 *   - Uplink slot requests: "please give me the demodulated uplink data for
 *     this slot, I'm expecting a PUSCH/PUCCH transmission."
 *
 * Both are routed to the correct cell's lower PHY based on the sector index
 * in the request context.
 */

#pragma once


#include "ocudu/ru/ru_uplink_plane.h" ///< ru_uplink_plane_handler — the base interface
#include <vector>


namespace ocudu {


class lower_phy_uplink_request_handler;
class shared_resource_grid;

/// Radio Unit to lower physical layer uplink request handler implementation.

/**
 * @brief Routes uplink requests (PRACH and data slots) to the correct cell's lower PHY.
 */
class ru_lower_phy_uplink_request_handler_impl : public ru_uplink_plane_handler
{
public:
  /**
   * @param handlers_  One lower_phy_uplink_request_handler pointer per cell
   *                   sector, indexed by sector ID.
   */
  explicit ru_lower_phy_uplink_request_handler_impl(std::vector<lower_phy_uplink_request_handler*> handlers_) :
    handlers(std::move(handlers_))
  {
  }

  // See interface for documentation.

  /**
   * @brief Requests capture of a PRACH (Physical Random Access Channel) window.
   *
   * Called by the upper PHY when a PRACH occasion is configured for an
   * upcoming slot. The lower PHY will capture and demodulate the
   * corresponding samples and report any detected preambles.
   *
   * @param context  Identifies the sector, slot, and PRACH occasion timing.
   * @param buffer   Shared buffer the demodulated PRACH samples will be written to.
   */
  void handle_prach_occasion(const prach_buffer_context& context, shared_prach_buffer buffer) override;

  // See interface for documentation.

  /**
   * @brief Requests demodulated uplink data for a slot.
   *
   * Called by the upper PHY when it expects uplink data (PUSCH/PUCCH) in an
   * upcoming slot. The lower PHY will capture, demodulate, and populate the
   * given resource grid with the received symbols.
   *
   * @param context  Identifies the sector and slot.
   * @param grid     The resource grid to be populated with demodulated uplink data.
   */
  void handle_new_uplink_slot(const resource_grid_context& context, const shared_resource_grid& grid) override;


private:
  /// Lookup table: sector index → that sector's lower PHY uplink request handler.
  std::vector<lower_phy_uplink_request_handler*> handlers;
};


} // namespace ocudu
