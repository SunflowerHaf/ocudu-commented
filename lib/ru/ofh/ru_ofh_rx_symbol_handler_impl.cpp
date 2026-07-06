// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_rx_symbol_handler_impl.cpp  (26 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ru_ofh_rx_symbol_handler_impl.h"
#include "ocudu/phy/support/shared_resource_grid.h"


using namespace ocudu;


void ru_ofh_rx_symbol_handler_impl::on_new_uplink_symbol(const ofh::uplane_rx_symbol_context& context,
                                                         shared_resource_grid                 grid,
                                                         bool                                 is_valid)
{
  ru_uplink_rx_symbol_context ru_context;
  ru_context.sector    = context.sector;
  ru_context.slot      = context.slot;
  ru_context.symbol_id = context.symbol;


  notifier.on_new_uplink_symbol(ru_context, grid, is_valid);
}


void ru_ofh_rx_symbol_handler_impl::on_new_prach_window_data(const prach_buffer_context& context,
                                                             shared_prach_buffer         buffer)
{
  notifier.on_new_prach_window_data(context, std::move(buffer));
}
