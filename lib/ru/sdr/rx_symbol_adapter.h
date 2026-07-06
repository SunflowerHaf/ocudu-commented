// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file rx_symbol_adapter.h
 * @brief Translates lower PHY received symbol notifications into RU uplink symbol notifications.
 *
 * This adapter sits between the lower PHY's OFDM demodulator output and the
 * RU's external uplink symbol notifier interface. It handles two kinds of
 * received data:
 *
 *   on_rx_symbol:        Regular uplink OFDM symbols have been demodulated
 *                        (PUSCH/PUCCH data). The is_valid flag indicates
 *                        whether the data is usable (e.g. false if the
 *                        radio reported a timing/quality issue during capture).
 *
 *   on_rx_prach_window:  A PRACH (random access) capture window has been
 *                        demodulated and is ready for preamble detection.
 *
 * Both are forwarded to the rx_symbol_handler, which is ultimately the
 * upper PHY's receive symbol handler for the corresponding cell.
 */

#pragma once


#include "ocudu/phy/lower/lower_phy_rx_symbol_context.h" ///< lower_phy_rx_symbol_context
#include "ocudu/phy/lower/lower_phy_rx_symbol_notifier.h" ///< Base interface this class implements
#include "ocudu/ru/ru_uplink_plane.h" ///< ru_uplink_plane_rx_symbol_notifier (forwarded to)


namespace ocudu {

/// Implements a lower physical layer to Radio Unit receive symbol adapter.

/**
 * @brief Adapts lower PHY received symbol notifications into RU uplink notifications.
 */
class ru_lower_phy_rx_symbol_adapter : public lower_phy_rx_symbol_notifier
{
public:
  /**
   * @param rx_symbol_handler_  The RU-level uplink symbol notifier — events
   *                            are forwarded here, ultimately reaching the
   *                            upper PHY's decoder for the corresponding cell.
   */
  explicit ru_lower_phy_rx_symbol_adapter(ru_uplink_plane_rx_symbol_notifier& rx_symbol_handler_) :
    rx_symbol_handler(rx_symbol_handler_)
  {
  }

  // See interface for documentation.

  /**
   * @brief Called when the lower PHY has demodulated new uplink symbols.
   *
   * Translates the lower PHY's context type (which tracks the symbol count
   * differently) into the RU-level context type, then forwards the resource
   * grid containing the demodulated symbols and the validity flag.
   *
   * @param context   Identifies the sector, slot, and number of symbols processed.
   * @param grid      Resource grid containing the demodulated uplink symbols.
   * @param is_valid  False if the radio reported a quality/timing issue
   *                  during capture (e.g. an overflow occurred mid-slot),
   *                  meaning the data may be unreliable.
   */
  void
  on_rx_symbol(const lower_phy_rx_symbol_context& context, const shared_resource_grid& grid, bool is_valid) override
  {
    rx_symbol_handler.on_new_uplink_symbol(
        ru_uplink_rx_symbol_context{.slot = context.slot, .sector = context.sector, .symbol_id = context.nof_symbols},
        grid,
        is_valid);
  }

  // See interface for documentation.

  /**
   * @brief Called when the lower PHY has demodulated a PRACH capture window.
   *
   * Forwarded directly to the upper PHY, which will run preamble detection
   * on the captured samples to identify any UEs attempting random access.
   *
   * @param context  Identifies the sector, slot, and PRACH occasion timing.
   * @param buffer   The demodulated PRACH samples, ready for preamble detection.
   */
  void on_rx_prach_window(const prach_buffer_context& context, shared_prach_buffer buffer) override
  {
    rx_symbol_handler.on_new_prach_window_data(context, std::move(buffer));
  }


private:
  /// The RU-level uplink symbol notifier — events are forwarded here.
  ru_uplink_plane_rx_symbol_notifier& rx_symbol_handler;
};


} // namespace ocudu
