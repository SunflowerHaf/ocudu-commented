// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_lower_phy_downlink_handler_impl.cpp
 * @brief Implementation of downlink resource grid routing to lower PHY sectors.
 */

#include "ru_lower_phy_downlink_handler_impl.h"
#include "ocudu/phy/lower/lower_phy_downlink_handler.h"
#include "ocudu/phy/support/shared_resource_grid.h"


using namespace ocudu;


/**
 * @brief Forwards the resource grid to the lower PHY handler for the indicated sector.
 *
 * Validates the sector index before dereferencing the handler — an invalid
 * sector index here would indicate a serious bug elsewhere in the stack
 * (e.g. the upper PHY using the wrong cell count), so it triggers an assertion
 * failure rather than silently doing nothing.
 *
 * @param context  Identifies the target sector and slot.
 * @param grid     The resource grid to transmit.
 */
void ru_lower_phy_downlink_handler_impl::handle_dl_data(const resource_grid_context& context,
                                                        const shared_resource_grid&  grid)
{
  ocudu_assert(context.sector < handlers.size(), "Invalid sector {}", context.sector);


  // Forward to the lower PHY's resource grid handler for this sector, which
  // queues the grid for OFDM modulation at the correct slot timing.
  handlers[context.sector]->handle_resource_grid(context, grid);
}
