// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_lower_phy_uplink_request_handler_impl.cpp
 * @brief Implementation of uplink request routing to lower PHY sectors.
 */

#include "ru_lower_phy_uplink_request_handler_impl.h"
#include "ocudu/phy/lower/lower_phy_uplink_request_handler.h"
#include "ocudu/phy/support/prach_buffer_context.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/phy/support/shared_resource_grid.h"


using namespace ocudu;


/**
 * @brief Forwards a PRACH capture request to the correct sector's lower PHY.
 *
 * @param context  Identifies the sector, slot, and PRACH timing.
 * @param buffer   Buffer to receive the demodulated PRACH samples (moved, not copied).
 */
void ru_lower_phy_uplink_request_handler_impl::handle_prach_occasion(const prach_buffer_context& context,
                                                                     shared_prach_buffer         buffer)
{
  ocudu_assert(context.sector < handlers.size(), "Invalid sector {}", context.sector);


  // Forward the PRACH window request to the lower PHY, which will capture
  // and demodulate the random access samples for this occasion.
  handlers[context.sector]->request_prach_window(context, std::move(buffer));
}


/**
 * @brief Forwards an uplink slot data request to the correct sector's lower PHY.
 *
 * @param context  Identifies the sector and slot.
 * @param grid     Resource grid to be populated with demodulated uplink data.
 */
void ru_lower_phy_uplink_request_handler_impl::handle_new_uplink_slot(const resource_grid_context& context,
                                                                      const shared_resource_grid&  grid)
{
  ocudu_assert(context.sector < handlers.size(), "Invalid sector {}", context.sector);


  // Forward the uplink slot request to the lower PHY, which will demodulate
  // received samples into this resource grid as they arrive.
  handlers[context.sector]->request_uplink_slot(context, grid);
}
