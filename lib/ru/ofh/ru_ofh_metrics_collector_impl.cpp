// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ru/ofh/ru_ofh_metrics_collector_impl.cpp  (27 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ru/ofh
// Radio Unit Open Fronthaul adapter. CONDITIONAL — compiled in but not called at runtime in split-8 (linked via a temporary worker_manager dependency). This adapts the OFH library (lib/ofh) into the RU interface (include/ocudu/ru) so it can be used as a drop-in replacement for the SDR/UHD RU in split-7.2 deployments. Contains: the OFH-based RU factory, the sector controller, the DL/UL data flow adaptors between upper PHY resource grids and OFH IQ streams, and the timing bridge that converts OFH slot indications into the slot_point events the upper PHY expects.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ru_ofh_metrics_collector_impl.h"
#include "ocudu/ru/ru_metrics.h"


using namespace ocudu;


void ru_ofh_metrics_collector_impl::collect_metrics(ru_metrics& metrics)
{
  auto& ofh_metrics = metrics.metrics.emplace<ofh::metrics>();

  // Add timestamp to the metric.

  // Add timestamp to the metric.
  ofh_metrics.timestamp = std::chrono::system_clock::now();

  // Timing metrics.

  // Timing metrics.
  timing_collector->collect_metrics(ofh_metrics.timing);

  // Resize with the number of sectors.

  // Resize with the number of sectors.
  ofh_metrics.sectors.resize(sector_metrics_collectors.size());

  // Collect the metrics from each sector.

  // Collect the metrics from each sector.
  for (unsigned i = 0, e = sector_metrics_collectors.size(); i != e; ++i) {
    sector_metrics_collectors[i]->collect_metrics(ofh_metrics.sectors[i]);
  }
}
