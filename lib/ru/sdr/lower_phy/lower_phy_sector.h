// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file lower_phy/lower_phy_sector.h
 * @brief One cell's complete lower PHY: OFDM modulation/demodulation and timing/control.
 *
 * lower_phy_sector wraps the underlying lower_phy implementation (the actual
 * OFDM processing engine, built by the lower PHY factory using DFT/FFT
 * libraries) and adds two sector-specific support objects:
 *
 *   - lower_phy_sector_metrics_collector: gathers Tx/Rx power statistics for this cell.
 *   - lower_phy_sector_timing_handler:    wraps the timing notifier so that
 *                                         sectors with no notifier configured
 *                                         (i.e. all sectors except the first)
 *                                         safely receive a dummy no-op notifier
 *                                         instead of needing a null check
 *                                         everywhere timing events are fired.
 *
 * One lower_phy_sector exists per configured cell in the Split-8 deployment.
 * Each owns its own OFDM modulator/demodulator chain but shares the same
 * USRP hardware connection (different RF channel/antenna per sector).
 */

#pragma once


#include "lower_phy_sector_metrics_collector.h"
#include "lower_phy_sector_timing_handler.h"
#include "ocudu/phy/lower/lower_phy.h" ///< lower_phy — the base interface this class implements
#include <memory>


namespace ocudu {


class lower_phy_cfo_controller;
class lower_phy_center_freq_controller;

/// Lower PHY sector implementation.

/**
 * @brief One cell's lower PHY: OFDM processing, timing, and control, with
 *        sector-specific metrics and timing notification wrapping.
 */
class lower_phy_sector : public lower_phy
{
public:
  /**
   * @param timing_notifier  The RU-level timing notifier for this sector, or
   *                         nullptr if this sector should not fire timing events
   *                         (in multi-cell deployments only the first sector
   *                         typically drives the shared DU timer).
   */
  explicit lower_phy_sector(lower_phy_timing_notifier* timing_notifier) : timing_handler(timing_notifier) {}

  // See interface for documentation.

  /// Returns the handler that processes uplink slot/PRACH requests for this cell.
  lower_phy_uplink_request_handler& get_uplink_request_handler() override;

  // See interface for documentation.

  /// Returns the handler that processes downlink resource grid data for this cell.
  lower_phy_downlink_handler& get_downlink_handler() override;

  // See interface for documentation.

  /// Returns the start/stop controller for this cell's lower PHY.
  lower_phy_controller& get_controller() override;

  // See interface for documentation.

  /// Returns the Tx CFO (Carrier Frequency Offset) controller for this cell.
  lower_phy_cfo_controller& get_tx_cfo_control() override;

  // See interface for documentation.

  /// Returns the Rx CFO controller for this cell.
  lower_phy_cfo_controller& get_rx_cfo_control() override;

  // See interface for documentation.

  /// Returns the Tx centre frequency controller for this cell.
  lower_phy_center_freq_controller& get_tx_center_freq_control() override;

  // See interface for documentation.

  /// Returns the Rx centre frequency controller for this cell.
  lower_phy_center_freq_controller& get_rx_center_freq_control() override;

  // See interface for documentation.

  /// Returns the Tx timing offset controller for this cell.
  lower_phy_tx_time_offset_controller& get_tx_time_offset_control() override;

  /// Sets the lower PHY of this sector to the given one.

  /**
   * @brief Sets the underlying lower PHY implementation for this sector.
   *
   * Called once during construction by create_lower_phy_sector(), after the
   * actual OFDM processing engine has been built by the lower PHY factory.
   *
   * @param phy  The constructed lower PHY implementation (owns the OFDM
   *             modulator/demodulator, downlink/uplink processors, etc.).
   */
  void set_lower_phy(std::unique_ptr<lower_phy> phy)
  {
    ocudu_assert(phy, "Invalid lower PHY");
    lower_phy = std::move(phy);
  }

  /// Returns the metrics collector of this lower PHY sector.

  /// Returns this sector's metrics collector (Tx/Rx power statistics).
  lower_phy_sector_metrics_collector& get_metrics_collector() { return metric_collector; }

  /// Returns the timing notifier of this lower PHY sector.

  /// Returns the timing notifier wrapper for this sector (safe even if no
  /// real notifier was configured — falls back to a dummy no-op notifier).
  lower_phy_timing_notifier& get_timing_notifier() { return timing_handler; }


private:
  /// Gathers Tx/Rx power and clipping statistics for this cell.
  lower_phy_sector_metrics_collector metric_collector;
  /// Wraps the timing notifier, providing a safe no-op fallback if none was configured.
  lower_phy_sector_timing_handler    timing_handler;
  /// The actual OFDM processing engine for this cell (modulator, demodulator,
  /// PRACH detector, controllers — all built by the lower PHY factory).
  std::unique_ptr<lower_phy>         lower_phy;
};


} // namespace ocudu
