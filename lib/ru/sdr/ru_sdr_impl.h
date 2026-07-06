// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_sdr_impl.h
 * @brief The SDR Radio Unit — the central object joining the upper PHY to the radio hardware.
 *
 * ru_sdr_impl is the most important object in the Split-8 radio stack. It is
 * the concrete implementation of the radio_unit interface for SDR (UHD/USRP)
 * deployments. It owns:
 *
 *   - The radio_session (in Split-8: radio_session_uhd_impl) — the open
 *     connection to the USRP hardware.
 *   - One lower_phy_sector per cell — each containing an OFDM modulator and
 *     demodulator for that cell.
 *   - The five small adapter objects that translate between the lower PHY's
 *     callback interfaces and the RU's interfaces (used by flexible_o_du_impl
 *     on the other side of the RU boundary).
 *   - A metrics collector that polls radio and lower PHY metrics on demand.
 *
 * Construction happens in two phases (see ru_factory_sdr_impl.cpp):
 *   1. The ru_sdr_impl object itself is constructed first (constructor below).
 *   2. set_radio() and set_lower_phy_sectors() are called afterward, because
 *      the radio session and lower PHY sectors need callback references that
 *      only exist once ru_sdr_impl itself has been constructed (e.g. the
 *      get_rx_symbol_notifier() that the lower PHY needs to report decoded symbols).
 */

#pragma once


#include "lower_phy/lower_phy_sector.h" ///< lower_phy_sector — per-cell OFDM processing
#include "ru_controller_sdr_impl.h" ///< ru_controller_sdr_impl — start/stop/gain/CFO control
#include "ru_lower_phy_downlink_handler_impl.h" ///< Forwards DL resource grids to the lower PHY
#include "ru_lower_phy_error_adapter.h" ///< Forwards lower PHY errors to the RU error notifier
#include "ru_lower_phy_timing_adapter.h" ///< Forwards lower PHY timing ticks to the RU timing notifier
#include "ru_lower_phy_uplink_request_handler_impl.h" ///< Forwards UL slot requests to the lower PHY
#include "ru_metrics_collector_sdr_impl.h" ///< Polls combined radio + lower PHY metrics
#include "ru_radio_metrics_collector.h" ///< Counts radio events (late/underflow/overflow)
#include "rx_symbol_adapter.h" ///< Forwards decoded UL symbols to the RU uplink notifier
#include "ocudu/radio/radio_session.h" ///< radio_session — interface to the open USRP connection
#include "ocudu/ru/ru.h" ///< radio_unit — the base interface this class implements
#include <memory>


namespace ocudu {

/// SDR based Radio Unit implementation configuration.

/**
 * @brief Configuration for constructing ru_sdr_impl.
 */
struct ru_sdr_impl_config {
  /// Sample rate in MHz. Used to compute slot/subframe boundaries for start timing.
  double                                               srate_MHz;
  /// Optional absolute start time for synchronised multi-node operation.
  /// If set, the radio waits until this time before starting to stream.
  std::optional<std::chrono::system_clock::time_point> start_time;
  /// Whether the RU should report metrics (USRP timing errors, signal power).
  bool                                                 are_metrics_enabled;
};

/// SDR based Radio Unit implementation dependencies.

/**
 * @brief External callback dependencies for constructing ru_sdr_impl.
 *
 * These are the notifier interfaces from flexible_o_du_impl's adapters
 * (ru_ul_adapt, ru_timing_adapt, ru_error_adapt). The RU forwards events
 * to them as they occur.
 */
struct ru_sdr_impl_dependencies {
  /// Called when the lower PHY has decoded uplink IQ symbols.
  ru_uplink_plane_rx_symbol_notifier& rx_symbol_handler;
  /// Called at each 5G slot boundary.
  ru_timing_notifier&                 timing_handler;
  /// Logger for general RU-level messages.
  ocudulog::basic_logger&             logger;
  /// Logger for RF/radio-driver-level messages.
  ocudulog::basic_logger&             radio_logger;
  /// Called when a radio error occurs (e.g. late Tx packet, Rx overflow).
  ru_error_notifier&                  error_notifier;
};

/// SDR Radio Unit implementation.

/**
 * @brief The SDR (UHD/USRP) Radio Unit implementation.
 *
 * Implements the radio_unit interface. One instance manages all cells
 * (sectors) for the entire DU — each sector has its own lower_phy_sector,
 * but they all share a single radio_session and a single ru_sdr_impl object.
 */
class ru_sdr_impl : public radio_unit
{
public:
  /**
   * @brief Constructor. Initialises adapters, controller, and metrics objects.
   *
   * Note: at this point the radio session and lower PHY sectors do not yet
   * exist — they are added afterward by set_radio() and set_lower_phy_sectors().
   * This two-phase construction is required because the radio session and
   * lower PHY both need callback references (e.g. get_rx_symbol_notifier())
   * that only become valid once this object itself exists.
   *
   * @param config        Sample rate, start time, and metrics enable flag.
   * @param dependencies  Callback references and loggers from the DU side.
   */
  ru_sdr_impl(const ru_sdr_impl_config& config, const ru_sdr_impl_dependencies& dependencies);

  // See interface for documentation.

  /// Returns the RU controller (start/stop, gain, CFO, center frequency, tx time offset).
  ru_controller& get_controller() override { return radio_unit_controller; }

  // See interface for documentation

  /// Returns the downlink plane handler — the upper PHY pushes resource grids here.
  ru_downlink_plane_handler& get_downlink_plane_handler() override { return ru_downlink_hdlr; }

  // See interface for documentation.

  /// Returns the uplink plane handler — the upper PHY requests uplink slots here.
  ru_uplink_plane_handler& get_uplink_plane_handler() override { return ru_uplink_request_hdlr; }

  // See interface for documentation.

  /// Returns the metrics collector if metrics are enabled, otherwise nullptr.
  ru_metrics_collector* get_metrics_collector() override { return are_metrics_enabled ? &metrics_collector : nullptr; }

  /// Returns the lower PHY rx symbol notifier of this RU.

  /// Returns the adapter the lower PHY uses to report decoded uplink symbols.
  /// Used during construction to wire the lower PHY's rx_symbol_notifier dependency.
  lower_phy_rx_symbol_notifier& get_rx_symbol_notifier() { return rx_adapter; }

  /// Returns the lower PHY timing notifier of this RU.

  /// Returns the adapter the lower PHY uses to report slot timing boundaries.
  lower_phy_timing_notifier& get_timing_notifier() { return timing_adapter; }

  /// Returns the lower PHY error notifier of this RU.

  /// Returns the adapter the lower PHY uses to report processing errors.
  lower_phy_error_notifier& get_error_notifier() { return error_adapter; }

  /// Returns the radio event notifier of this RU.

  /// Returns the dispatcher the radio session uses to report hardware events
  /// (late packets, underflow, overflow). Dispatches to both the metrics
  /// collector and the event logger.
  radio_event_notifier& get_radio_event_notifier() { return radio_event_dispatcher; }

  /// Sets the radio to the given one for this RU.

  /**
   * @brief Sets the radio session (the open connection to the USRP).
   *
   * Called once during construction after the UHD radio session has been
   * created. Also passes the radio reference to the controller so it can
   * issue start/stop/gain commands.
   *
   * @param radio_ptr  The constructed radio session (radio_session_uhd_impl).
   */
  void set_radio(std::unique_ptr<radio_session> radio_ptr)
  {
    radio = std::move(radio_ptr);
    ocudu_assert(radio, "Invalid radio");
    radio_unit_controller.set_radio(*radio);
  }

  /// Sets the RU lower PHY sectors.

  /**
   * @brief Sets the lower PHY sectors (one per cell).
   *
   * Called once during construction after each cell's lower_phy_sector has
   * been built. Wires the controller, metrics collector, downlink handler,
   * and uplink request handler to the new sectors. See ru_sdr_impl.cpp for
   * the implementation.
   *
   * @param lower_phy_sectors  One lower_phy_sector per cell.
   */
  void set_lower_phy_sectors(std::vector<std::unique_ptr<lower_phy_sector>> lower_phy_sectors);

  /// Returns the baseband gateway for the given sector.

  /**
   * @brief Returns the baseband gateway for the given sector.
   *
   * The baseband gateway is the interface the lower PHY uses to read/write
   * IQ samples to/from the radio. In Split-8 with UHD, this is implemented
   * by radio_uhd_baseband_gateway.
   *
   * @param sector_id  The cell sector index.
   * @return Reference to the baseband gateway for that sector.
   */
  baseband_gateway& get_baseband_gateway(unsigned sector_id)
  {
    ocudu_assert(radio, "Invalid radio");
    return radio->get_baseband_gateway(sector_id);
  }


private:
  /// Whether metrics reporting is active.
  const bool                                     are_metrics_enabled;
  /// Counts radio events (late/underflow/overflow) for the metrics collector.
  ru_radio_metrics_collector                     radio_metrics_collector;
  /// Logs radio events as warnings/debug messages.
  ru_radio_logger_event_handler                  radio_event_logger;
  /// Dispatches each radio event to both the metrics collector and the logger.
  ru_radio_event_dispatcher                      radio_event_dispatcher;
  /// Forwards lower PHY error events to the RU error notifier (DU side).
  ru_lower_phy_error_adapter                     error_adapter;
  /// Forwards decoded uplink IQ symbols from the lower PHY to the RU uplink notifier.
  ru_lower_phy_rx_symbol_adapter                 rx_adapter;
  /// Forwards slot timing boundaries from the lower PHY to the RU timing notifier.
  ru_lower_phy_timing_adapter                    timing_adapter;
  /// The open connection to the USRP hardware (set via set_radio()).
  std::unique_ptr<radio_session>                 radio;
  /// One lower_phy_sector per cell (set via set_lower_phy_sectors()).
  std::vector<std::unique_ptr<lower_phy_sector>> phy_sectors;
  /// Polls radio and lower PHY metrics when requested.
  ru_metrics_collector_sdr_impl                  metrics_collector;
  /// Handles start/stop, gain, CFO, center frequency, and tx time offset control.
  ru_controller_sdr_impl                         radio_unit_controller;
  /// Forwards downlink resource grids from the upper PHY to the correct sector's lower PHY.
  ru_lower_phy_downlink_handler_impl             ru_downlink_hdlr;
  /// Forwards uplink slot/PRACH requests from the upper PHY to the correct sector's lower PHY.
  ru_lower_phy_uplink_request_handler_impl       ru_uplink_request_hdlr;
};


} // namespace ocudu
