// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_downlink_plane_handler_proxy.cpp  (20 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ru_ofh_downlink_plane_handler_proxy.h"
#include "ocudu/ofh/transmitter/ofh_downlink_handler.h"
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/phy/support/shared_resource_grid.h"
#include <memory>


using namespace ocudu;


void ru_downlink_plane_handler_proxy::handle_dl_data(const resource_grid_context& context,
                                                     const shared_resource_grid&  grid)
{
  ocudu_assert(context.sector < sectors.size(), "Invalid sector id '{}'", context.sector);


  auto& sector = sectors[context.sector];
  sector->handle_dl_data(context, grid);
}
