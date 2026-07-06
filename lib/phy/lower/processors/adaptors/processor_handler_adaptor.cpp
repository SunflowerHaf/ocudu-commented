// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/phy/lower/processors/adaptors/processor_handler_adaptor.cpp  (28 lines)
//
// DIRECTORY: lib/phy/lower
// Lower physical layer: real-time baseband processing. Converts the frequency-domain resource grid (output of the upper PHY) into time-domain IQ samples for transmission, and the reverse on uplink. Contains: OFDM modulator and demodulator (including CP insertion/removal and phase rotation), the PRACH demodulator, the real-time processing loop (receives slot indications from the RU and drives the entire baseband pipeline), the amplitude controller, CFO compensator, and PDSCH/PUSCH/PUCCH/PRACH processor pipelines.
//
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "processor_handler_adaptor.h"
#include "ocudu/phy/support/shared_resource_grid.h"


using namespace ocudu;


void processor_handler_adaptor::downlink_handler_adaptor ::handle_resource_grid(const resource_grid_context& context,
                                                                                const shared_resource_grid&  grid)
{
  pdxch_handler.handle_request(grid, context);
}


void processor_handler_adaptor::uplink_request_handler_adaptor::request_prach_window(
    const prach_buffer_context& context,
    shared_prach_buffer         buffer)
{
  prach_handler.handle_request(std::move(buffer), context);
}


void processor_handler_adaptor::uplink_request_handler_adaptor::request_uplink_slot(
    const resource_grid_context& context,
    const shared_resource_grid&  grid)
{
  puxch_handler.handle_request(grid, context);
}
