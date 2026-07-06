// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_sdr_impl.cpp
 * @brief Implementation of ru_sdr_impl construction and sector wiring.
 */

#include "ru_sdr_impl.h"


using namespace ocudu;


/**
 * @brief Constructor. Initialises all adapters, the radio event dispatcher,
 *        the metrics collector, and the controller.
 *
 * Note the construction order matters here due to member initialisation lists:
 *   - radio_event_dispatcher takes pointers to radio_metrics_collector and
 *     radio_event_logger, so those two must be constructed first (they are,
 *     since they're declared earlier in the class).
 *   - metrics_collector takes a reference to radio_metrics_collector.
 *   - ru_downlink_hdlr and ru_uplink_request_hdlr are initialised with empty
 *     handler lists ({}) — they will be replaced with real handler lists
 *     once set_lower_phy_sectors() is called.
 *
 * @param config        Sample rate, start time, metrics enable flag.
 * @param dependencies  Callback references for symbols, timing, errors, loggers.
 */
ru_sdr_impl::ru_sdr_impl(const ru_sdr_impl_config& config, const ru_sdr_impl_dependencies& dependencies) :
  are_metrics_enabled(config.are_metrics_enabled),
  radio_metrics_collector(),
  // Logs radio events using the provided RF logger.
  radio_event_logger(dependencies.radio_logger),
  // Dispatches every radio event to both the metrics collector and the logger.
  radio_event_dispatcher({&radio_metrics_collector, &radio_event_logger}),
  // Forwards lower PHY errors to the RU's error notifier, with logging.
  error_adapter(dependencies.logger, dependencies.error_notifier),
  // Forwards lower PHY received symbols to the upper PHY's symbol handler.
  rx_adapter(dependencies.rx_symbol_handler),
  // Forwards lower PHY slot ticks to the upper PHY's timing handler.
  timing_adapter(dependencies.timing_handler),
  // Reads radio metrics from radio_metrics_collector when polled.
  metrics_collector(radio_metrics_collector),
  // Controller needs the sample rate and optional start time for radio start().
  radio_unit_controller(config.srate_MHz, config.start_time),
  // Empty handler lists initially — populated by set_lower_phy_sectors().
  ru_downlink_hdlr({}),
  ru_uplink_request_hdlr({})
{
}


/**
 * @brief Wires the lower PHY sectors into the RU's handler and metrics objects.
 *
 * Called once, after all lower_phy_sector objects have been constructed
 * (one per configured cell). For each of the four downstream objects that
 * need per-sector handler lists, this function builds the appropriate list
 * by extracting the relevant handler/collector from each sector:
 *
 *   radio_unit_controller: needs raw lower_phy_sector* pointers (for CFO,
 *                          center frequency, and tx time offset control).
 *
 *   metrics_collector: needs each sector's metrics collector, to gather
 *                      Tx/Rx power and clipping statistics.
 *
 *   ru_downlink_hdlr: needs each sector's downlink_handler, so when the
 *                     upper PHY sends a resource grid for sector N, it
 *                     reaches that sector's OFDM modulator.
 *
 *   ru_uplink_request_hdlr: needs each sector's uplink_request_handler,
 *                           so uplink slot requests reach the correct
 *                           sector's demodulator.
 *
 * Each lambda below captures `this` and builds a std::vector by iterating
 * over phy_sectors, extracting the relevant pointer/reference from each.
 *
 * @param lower_phy_sectors  One lower_phy_sector per configured cell, in
 *                           sector-index order.
 */
void ru_sdr_impl::set_lower_phy_sectors(std::vector<std::unique_ptr<lower_phy_sector>> lower_phy_sectors)
{
  phy_sectors = std::move(lower_phy_sectors);


  ocudu_assert(!phy_sectors.empty(), "SDR Radio Unit received an empty list of sectors");


  // Build the list of raw sector pointers for the controller (CFO, center
  // frequency, and tx time offset control act directly on each sector).
  radio_unit_controller.set_lower_phy_sectors([this]() -> std::vector<lower_phy_sector*> {
    std::vector<lower_phy_sector*> sectors;
    sectors.reserve(phy_sectors.size());
    for (auto& sector : phy_sectors) {
      sectors.push_back(sector.get());
    }
    return sectors;
  }());


  // Build the list of per-sector metrics collectors.
  metrics_collector.set_lower_phy_sectors([this]() -> std::vector<lower_phy_sector_metrics_collector*> {
    std::vector<lower_phy_sector_metrics_collector*> collectors;
    collectors.reserve(phy_sectors.size());
    for (auto& sector : phy_sectors) {
      collectors.push_back(&sector->get_metrics_collector());
    }
    return collectors;
  }());


  // Build the downlink handler list — replaces the empty handler set from
  // the constructor with one entry per sector, pointing to each sector's
  // OFDM modulator entry point.
  ru_downlink_hdlr = ru_lower_phy_downlink_handler_impl([this]() -> std::vector<lower_phy_downlink_handler*> {
    std::vector<lower_phy_downlink_handler*> handlers;
    handlers.reserve(phy_sectors.size());
    for (auto& sector : phy_sectors) {
      handlers.push_back(&sector->get_downlink_handler());
    }
    return handlers;
  }());


  // Build the uplink request handler list — one entry per sector, pointing
  // to each sector's OFDM demodulator request entry point.
  ru_uplink_request_hdlr =
      ru_lower_phy_uplink_request_handler_impl([this]() -> std::vector<lower_phy_uplink_request_handler*> {
        std::vector<lower_phy_uplink_request_handler*> handlers;
        handlers.reserve(phy_sectors.size());
        for (auto& sector : phy_sectors) {
          handlers.push_back(&sector->get_uplink_request_handler());
        }
        return handlers;
      }());
}
