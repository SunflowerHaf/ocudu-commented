// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_metrics_collector_sdr_impl.h
 * @brief Combines radio hardware metrics and per-cell lower PHY metrics into one RU report.
 *
 * This is the metrics collector returned by ru_sdr_impl::get_metrics_collector().
 * When polled (typically once per metrics reporting interval, e.g. every
 * second), it gathers:
 *
 *   - Radio hardware metrics: late/underflow/overflow event counts since the
 *     last poll (from ru_radio_metrics_collector).
 *
 *   - Per-cell lower PHY metrics: Tx/Rx average and peak power, PAPR, and
 *     clipping statistics for each configured cell.
 *
 * The combined result is written into a ru_sdr_metrics variant inside the
 * overall ru_metrics structure (ru_metrics can hold SDR, OFH, or dummy
 * metrics depending on which radio backend is active — for split-8 it's always SDR).
 */

#pragma once


#include "lower_phy/lower_phy_sector.h"
#include "ocudu/ru/ru_metrics_collector.h" ///< Base interface this class implements
#include <vector>


namespace ocudu {


class ru_radio_metrics_collector;

/// Metrics collector implementation for the SDR RU.

/**
 * @brief Metrics collector for the SDR Radio Unit.
 *
 * Combines radio hardware metrics with per-cell lower PHY metrics into a
 * single ru_metrics report when polled.
 */
class ru_metrics_collector_sdr_impl : public ru_metrics_collector
{
  /// Radio hardware event counters (late, underflow, overflow).
  ru_radio_metrics_collector&                      radio;
  /// One metrics collector per configured cell — gathers Tx/Rx power and clipping stats.
  std::vector<lower_phy_sector_metrics_collector*> sector_metrics_collectors;


public:
  /**
   * @param radio_  Reference to the shared radio hardware metrics collector.
   */
  explicit ru_metrics_collector_sdr_impl(ru_radio_metrics_collector& radio_) : radio(radio_) {}

  /// Sets the list of lower PHY sector collectors.

  /**
   * @brief Sets the list of per-cell lower PHY metrics collectors.
   *
   * Called once at startup after all lower PHY sectors are constructed.
   *
   * @param collectors  One metrics collector pointer per configured cell.
   */
  void set_lower_phy_sectors(std::vector<lower_phy_sector_metrics_collector*> collectors)
  {
    sector_metrics_collectors = std::move(collectors);
  }

  // See interface for documentation.

  /**
   * @brief Gathers radio and per-cell lower PHY metrics into the given report.
   *
   * @param metrics  The output ru_metrics struct to populate (modified in place).
   */
  void collect_metrics(ru_metrics& metrics) override;
};


} // namespace ocudu
