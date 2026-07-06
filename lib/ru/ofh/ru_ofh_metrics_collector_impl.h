// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_metrics_collector_impl.h  (39 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ofh/ofh_sector_metrics_collector.h"
#include "ocudu/ofh/timing/ofh_timing_metrics_collector.h"
#include "ocudu/ru/ru_metrics_collector.h"
#include <vector>


namespace ocudu {

/// Open Fronthaul Radio Unit metrics collector implementation.

/// Open Fronthaul Radio Unit metrics collector implementation.
class ru_ofh_metrics_collector_impl : public ru_metrics_collector
{
  ofh::timing_metrics_collector*       timing_collector;
  std::vector<ofh::metrics_collector*> sector_metrics_collectors;


public:
  explicit ru_ofh_metrics_collector_impl(ofh::timing_metrics_collector& timing_collector_) :
    timing_collector(&timing_collector_)
  {
  }


  ru_ofh_metrics_collector_impl(ofh::timing_metrics_collector&       timing_collector_,
                                std::vector<ofh::metrics_collector*> sector_metrics_collectors_) :
    timing_collector(&timing_collector_), sector_metrics_collectors(std::move(sector_metrics_collectors_))
  {
  }

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(ru_metrics& metrics) override;

  /// Returns true if the metrics collector is disabled, otherwise true.

  /// Returns true if the metrics collector is disabled, otherwise true.
  bool disabled() const { return sector_metrics_collectors.empty(); }
};


} // namespace ocudu
