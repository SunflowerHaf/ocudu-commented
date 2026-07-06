// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_downlink_plane_handler_proxy.h  (40 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ru/ru_downlink_plane.h"
#include "ocudu/support/ocudu_assert.h"
#include <algorithm>
#include <vector>


namespace ocudu {


class task_executor;
class shared_resource_grid;


namespace ofh {
class downlink_handler;
} // namespace ofh

/// This proxy implementation dispatches the requests to the corresponding OFH sector.

/// This proxy implementation dispatches the requests to the corresponding OFH sector.
class ru_downlink_plane_handler_proxy : public ru_downlink_plane_handler
{
public:
  ru_downlink_plane_handler_proxy() = default;


  explicit ru_downlink_plane_handler_proxy(std::vector<ofh::downlink_handler*> sectors_) : sectors(std::move(sectors_))
  {
    ocudu_assert(std::all_of(sectors.begin(), sectors.end(), [](const auto& elem) { return elem != nullptr; }),
                 "Invalid sector");
  }

  // See interface for documentation.

  // See interface for documentation.
  void handle_dl_data(const resource_grid_context& context, const shared_resource_grid& grid) override;


private:
  std::vector<ofh::downlink_handler*> sectors;
};


} // namespace ocudu
