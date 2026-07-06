// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_controller_impl.cpp  (38 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ru_ofh_controller_impl.h"
#include "ocudu/support/ocudu_assert.h"


using namespace ocudu;


void ru_ofh_controller_impl::start()
{
  logger.info("Starting the operation of the Open Fronthaul interface");
  for (auto* sector : sector_controllers) {
    sector->start();
  }
  logger.info("Started the operation of the Open Fronthaul interface");
}


void ru_ofh_controller_impl::stop()
{
  logger.info("Stopping the operation of the Open Fronthaul interface");
  for (auto* sector : sector_controllers) {
    sector->stop();
  }
  logger.info("Stopped the operation of the Open Fronthaul interface");
}


void ru_ofh_controller_impl::set_sector_controllers(std::vector<ofh::operation_controller*> controllers)
{
  ocudu_assert(!controllers.empty(), "Invalid sector controllers");


  sector_controllers = std::move(controllers);


  ocudu_assert(std::all_of(sector_controllers.begin(),
                           sector_controllers.end(),
                           [](const auto& elem) { return elem != nullptr; }),
               "Invalid sector controller");
}
