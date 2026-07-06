// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_sector_metrics_collector.cpp
 * @brief Implementation of Tx/Rx power statistic accumulation and reporting.
 */

#include "lower_phy_sector_metrics_collector.h"
#include "ocudu/ru/sdr/ru_sdr_metrics.h"
#include "ocudu/support/math/math_utils.h" ///< convert_power_to_dB()


using namespace ocudu;


/**
 * @brief Accumulates a new Tx power measurement.
 *
 * Updates the running mean and max trackers, and accumulates clipping
 * counters across calls (clipping counts are cumulative, not instantaneous,
 * so they're added rather than overwritten).
 *
 * @param metrics  The most recent Tx power/clipping measurement.
 */
void lower_phy_sector_metrics_collector::on_new_transmit_metrics(const lower_phy_baseband_metrics& metrics)
{
  std::lock_guard<std::mutex> lock(tx_mutex);
  tx_avg_power.update(metrics.avg_power);
  tx_peak_power.update(metrics.peak_power);
  if (!tx_clipping.has_value()) {
    // First clipping report this interval — initialise directly.
    tx_clipping = metrics.clipping;
  } else {
    // Subsequent reports — accumulate onto the existing counters.
    tx_clipping->nof_clipped_samples += metrics.clipping->nof_clipped_samples;
    tx_clipping->nof_processed_samples += metrics.clipping->nof_processed_samples;
  }
}


/**
 * @brief Accumulates a new Rx power measurement.
 *
 * Same pattern as on_new_transmit_metrics(), but clipping data is optional
 * for the Rx path (clipping detection on receive is less commonly enabled),
 * so the metrics.clipping.has_value() check guards the accumulation.
 *
 * @param metrics  The most recent Rx power/clipping measurement.
 */
void lower_phy_sector_metrics_collector::on_new_receive_metrics(const lower_phy_baseband_metrics& metrics)
{
  std::lock_guard<std::mutex> lock(rx_mutex);
  rx_avg_power.update(metrics.avg_power);
  rx_peak_power.update(metrics.peak_power);
  if (metrics.clipping.has_value()) {
    if (!rx_clipping.has_value()) {
      rx_clipping = metrics.clipping;
    } else {
      rx_clipping->nof_clipped_samples += metrics.clipping->nof_clipped_samples;
      rx_clipping->nof_processed_samples += metrics.clipping->nof_processed_samples;
    }
  }
}


/**
 * @brief Computes summary statistics for the reporting interval and resets the accumulators.
 *
 * For both Tx and Rx:
 *   - Converts the linear average and peak power to dB.
 *   - Computes PAPR (Peak-to-Average Power Ratio) in dB as the ratio of peak
 *     to average power, converted to dB.
 *   - If clipping data is present, computes the clipping probability as
 *     clipped_samples / processed_samples.
 *   - Resets all accumulators so the next interval starts with a clean slate.
 *
 * @param metrics  The output struct to populate.
 */
void lower_phy_sector_metrics_collector::collect_metrics(ru_sdr_sector_metrics& metrics)
{
  {
    std::lock_guard<std::mutex> lock(tx_mutex);
    metrics.tx_avg_power_dB  = convert_power_to_dB(tx_avg_power.get_mean());
    metrics.tx_peak_power_dB = convert_power_to_dB(tx_peak_power.get_max());
    // PAPR: ratio of peak to average power, expressed in dB.
    metrics.tx_papr_dB       = convert_power_to_dB(tx_peak_power.get_max() / tx_avg_power.get_mean());
    if (tx_clipping.has_value()) {
      double num               = tx_clipping->nof_clipped_samples;
      double den               = tx_clipping->nof_processed_samples;
      metrics.tx_clipping_prob = num / den;
    }
    // Reset for the next reporting interval.
    tx_avg_power.reset();
    tx_peak_power.reset();
    tx_clipping.reset();
  }


  {
    std::lock_guard<std::mutex> lock(rx_mutex);
    metrics.rx_avg_power_dB  = convert_power_to_dB(rx_avg_power.get_mean());
    metrics.rx_peak_power_dB = convert_power_to_dB(rx_peak_power.get_max());
    metrics.rx_papr_dB       = convert_power_to_dB(rx_peak_power.get_max() / rx_avg_power.get_mean());
    if (rx_clipping.has_value()) {
      double num               = rx_clipping->nof_clipped_samples;
      double den               = rx_clipping->nof_processed_samples;
      metrics.rx_clipping_prob = num / den;
    }
    rx_avg_power.reset();
    rx_peak_power.reset();
    rx_clipping.reset();
  }
}
