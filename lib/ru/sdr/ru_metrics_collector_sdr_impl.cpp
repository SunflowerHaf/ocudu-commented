// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_metrics_collector_sdr_impl.cpp
 * @brief Implementation of combined radio + lower PHY metrics collection.
 */

#include "ru_metrics_collector_sdr_impl.h"
#include "ru_radio_metrics_collector.h"
#include "ocudu/ru/ru_metrics.h"


using namespace ocudu;


/**
 * @brief Collects radio and per-cell lower PHY metrics into the given report.
 *
 * Builds an ru_sdr_metrics variant inside the passed-in metrics struct
 * (this is what tells downstream consumers "this is an SDR-type RU report,
 * not OFH or dummy"). Fills it with:
 *
 *   1. Radio hardware metrics (late/underflow/overflow event counts, reset
 *      to zero in the underlying collector after being read — see
 *      ru_radio_metrics_collector::collect_metrics()).
 *
 *   2. Per-cell metrics: one entry per configured cell, each labelled with
 *      its sector_id and populated by that cell's lower PHY metrics
 *      collector (Tx/Rx power, PAPR, clipping probability).
 *
 * @param metrics  The output ru_metrics struct to populate (modified in place).
 */
void ru_metrics_collector_sdr_impl::collect_metrics(ru_metrics& metrics)
{
  // Tell the variant this is SDR-type metrics, and get a reference to the
  // newly-constructed ru_sdr_metrics struct to fill in.
  auto& ru_metrics = metrics.metrics.emplace<ru_sdr_metrics>();

  // Radio metrics.

  // Gather radio hardware event counters since the last poll.
  radio.collect_metrics(ru_metrics.radio);

  // Lower PHY metrics.

  // Allocate one cell metrics entry per configured cell.
  ru_metrics.cells.resize(sector_metrics_collectors.size());


  // Poll each cell's lower PHY metrics collector in turn.
  unsigned sector_id = 0;
  for (auto* collector : sector_metrics_collectors) {
    ru_sdr_sector_metrics& cell_metric = ru_metrics.cells[sector_id];
    cell_metric.sector_id              = sector_id++;
    collector->collect_metrics(cell_metric);
  }
}
