// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_sector_metrics_collector.h
 * @brief Accumulates Tx/Rx signal power and clipping statistics for one cell.
 *
 * The lower PHY's baseband processor reports power measurements every time it
 * processes a chunk of samples (on_new_transmit_metrics / on_new_receive_metrics).
 * This class accumulates those measurements between metrics reporting intervals,
 * computing running statistics (mean, max) so that when collect_metrics() is
 * called, it can report a summary over the whole interval rather than just
 * the most recent sample.
 *
 * Tracked statistics:
 *   - Average and peak Tx/Rx power.
 *   - PAPR (Peak-to-Average Power Ratio) — derived from average and peak power.
 *   - Clipping statistics — how many samples exceeded the configured power
 *     ceiling and were clipped (only present if clipping is enabled in the
 *     amplitude controller config).
 *
 * Thread safety: metrics can be reported from the Tx and Rx processing
 * threads concurrently with the metrics polling thread, so separate mutexes
 * protect the Tx and Rx accumulation state.
 */

#pragma once


#include "ocudu/phy/lower/lower_phy_baseband_metrics.h" ///< lower_phy_baseband_metrics — the input struct
#include "ocudu/phy/lower/lower_phy_metrics_notifier.h" ///< Base interface this class implements
#include "ocudu/support/math/stats.h" ///< sample_statistics<> — running mean/max tracking
#include <mutex>
#include <optional>


namespace ocudu {


struct ru_sdr_sector_metrics; ///< Output struct populated by collect_metrics()

/// Lower PHY sector metrics collector.

/**
 * @brief Accumulates and reports per-cell Tx/Rx signal power statistics.
 */
class lower_phy_sector_metrics_collector : public lower_phy_metrics_notifier
{
public:
  // See interface for documentation.
  /**
   * @brief Called by the lower PHY's downlink baseband processor with new Tx power measurements.
   *
   * Updates the running average/peak power statistics and accumulates
   * clipping counters (if the amplitude controller reports clipping events).
   *
   * @param metrics  Power and clipping measurements for the most recently
   *                 processed chunk of transmitted samples.
   */
  void on_new_transmit_metrics(const lower_phy_baseband_metrics& metrics) override;

  // See interface for documentation.

  /**
   * @brief Called by the lower PHY's uplink baseband processor with new Rx power measurements.
   *
   * @param metrics  Power and clipping measurements for the most recently
   *                 processed chunk of received samples.
   */
  void on_new_receive_metrics(const lower_phy_baseband_metrics& metrics) override;

  /// Collects the metrics of the lower PHY sector and fills the given structure.

  /**
   * @brief Computes summary statistics over the accumulated period and resets the accumulators.
   *
   * Converts accumulated linear power measurements to dB, computes PAPR, and
   * (if clipping data is present) computes the clipping probability as a ratio
   * of clipped samples to total processed samples. Resets all accumulators
   * afterwards so the next interval starts fresh.
   *
   * @param metrics  The output struct to populate with this interval's statistics.
   */
  void collect_metrics(ru_sdr_sector_metrics& metrics);


private:
  /// Protects tx_avg_power, tx_peak_power, tx_clipping during concurrent access.
  std::mutex                       tx_mutex;
  /// Running mean and count of Tx power samples (linear scale, converted to dB on report).
  sample_statistics<float>         tx_avg_power;
  /// Running maximum of Tx power samples.
  sample_statistics<float>         tx_peak_power;
  /// Accumulated Tx clipping counters, if clipping is enabled.
  std::optional<clipping_counters> tx_clipping;

  /// Protects rx_avg_power, rx_peak_power, rx_clipping during concurrent access.
  std::mutex                       rx_mutex;
  /// Running mean and count of Rx power samples.
  sample_statistics<float>         rx_avg_power;
  /// Running maximum of Rx power samples.
  sample_statistics<float>         rx_peak_power;
  /// Accumulated Rx clipping counters, if clipping is enabled.
  std::optional<clipping_counters> rx_clipping;
};


} // namespace ocudu
