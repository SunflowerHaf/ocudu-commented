// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_controller_sdr_impl.h
 * @brief Control interfaces for the SDR Radio Unit: gain, CFO, frequency, timing, start/stop.
 *
 * This file defines five small controller classes plus the main RU controller
 * that aggregates them. Each controller class wraps one specific type of
 * runtime control command and forwards it either to the radio session (UHD)
 * or to the lower PHY sectors:
 *
 *   ru_gain_controller_sdr_impl:             Tx/Rx gain — forwarded to UHD.
 *   ru_cfo_controller_sdr_impl:               Carrier Frequency Offset compensation
 *                                             (used for NTN Doppler correction) —
 *                                             forwarded to the lower PHY sectors.
 *   ru_center_frequency_controller_sdr_impl:  Centre frequency changes — forwarded
 *                                             to both UHD and the lower PHY.
 *   ru_tx_time_offset_controller_sdr_impl:    Tx timing offset — forwarded to the
 *                                             lower PHY sectors.
 *   ru_controller_sdr_impl:                   The top-level controller. Implements
 *                                             start()/stop() for the whole radio
 *                                             stack and exposes the four sub-controllers.
 *
 * These commands can be issued via the CLI ("tx_gain", "rx_gain", "cfo",
 * "tx_time_offset") or programmatically by the NTN Doppler compensation
 * handler for satellite deployments.
 */

#pragma once


#include "ocudu/adt/span.h"
#include "ocudu/ru/ru_controller.h" ///< Base interfaces: ru_controller, ru_gain_controller, etc.
#include <vector>


namespace ocudu {


class lower_phy_sector;
class lower_phy_cfo_controller;
class lower_phy_controller;
class lower_phy_metrics_notifier;
class radio_session;

/// SDR Radio Unit gain controller implementation.

/**
 * @brief Controls Tx/Rx gain on the USRP hardware.
 *
 * Gain changes go directly to the radio session's management plane, which
 * issues the appropriate UHD calls (set_tx_gain / set_rx_gain on the USRP).
 */
class ru_gain_controller_sdr_impl : public ru_gain_controller
{
  /// Pointer-to-pointer: indirection through the RU's radio member, which
  /// may not be set yet at the time this controller is constructed.
  radio_session** radio = nullptr;


public:
  ru_gain_controller_sdr_impl() = default;


  /**
   * @param radio_  Pointer to the RU's radio session pointer. Stored as a
   *                pointer-to-pointer so the controller always sees the
   *                current radio even if it's set after construction.
   */
  explicit ru_gain_controller_sdr_impl(radio_session** radio_) : radio(radio_) {}

  // See interface for documentation.

  /**
   * @brief Sets the transmit gain for a given antenna port.
   * @param port_id  The antenna port index.
   * @param gain_dB  The desired gain in dB.
   * @return true if the UHD driver accepted the gain change.
   */
  bool set_tx_gain(unsigned port_id, double gain_dB) override;

  // See interface for documentation.

  /**
   * @brief Sets the receive gain for a given antenna port.
   * @param port_id  The antenna port index.
   * @param gain_dB  The desired gain in dB.
   * @return true if the UHD driver accepted the gain change.
   */
  bool set_rx_gain(unsigned port_id, double gain_dB) override;
};

/// SDR Radio Unit carrier frequency offset controller implementation.

/**
 * @brief Controls Carrier Frequency Offset (CFO) compensation per sector.
 *
 * CFO compensation applies a frequency shift and optional drift rate to the
 * Tx or Rx signal path. Primarily used in NTN (satellite) deployments to
 * compensate for Doppler shift caused by satellite motion. The actual
 * compensation is applied by the lower PHY (a software frequency shift),
 * not by the radio hardware itself.
 */
class ru_cfo_controller_sdr_impl : public ru_cfo_controller
{
  /// One lower PHY sector pointer per cell, indexed by sector_id.
  std::vector<lower_phy_sector*> phy_sectors;


public:
  ru_cfo_controller_sdr_impl() = default;


  /**
   * @param phy_sectors_  Lower PHY sectors, one per cell.
   */
  explicit ru_cfo_controller_sdr_impl(std::vector<lower_phy_sector*> phy_sectors_) :
    phy_sectors(std::move(phy_sectors_))
  {
  }

  // See interface for documentation.

  /**
   * @brief Schedules a downlink CFO compensation command for a sector.
   * @param sector_id    The cell sector index.
   * @param cfo_request  CFO value, drift rate, and optional start time.
   * @return true if the command was scheduled; false if sector_id is invalid.
   */
  bool set_tx_cfo(unsigned sector_id, const cfo_compensation_request& cfo_request) override;

  // See interface for documentation.

  /**
   * @brief Schedules an uplink CFO compensation command for a sector.
   * @param sector_id    The cell sector index.
   * @param cfo_request  CFO value, drift rate, and optional start time.
   * @return true if the command was scheduled; false if sector_id is invalid.
   */
  bool set_rx_cfo(unsigned sector_id, const cfo_compensation_request& cfo_request) override;
};

/// SDR Radio Unit center frequency controller implementation.

/**
 * @brief Controls the centre (carrier) frequency for Tx and Rx, per sector.
 *
 * Frequency changes are applied to both the radio hardware (UHD tunes the
 * local oscillator) and the lower PHY sector (which needs to know the
 * current frequency for CFO and Doppler calculations).
 */
class ru_center_frequency_controller_sdr_impl : public ru_center_frequency_controller
{
  std::vector<lower_phy_sector*> phy_sectors;
  radio_session**                radio = nullptr;


public:
  ru_center_frequency_controller_sdr_impl() = default;


  /**
   * @param phy_sectors_  Lower PHY sectors, one per cell.
   * @param radio_        Pointer to the RU's radio session pointer.
   */
  ru_center_frequency_controller_sdr_impl(std::vector<lower_phy_sector*> phy_sectors_, radio_session** radio_) :
    phy_sectors(std::move(phy_sectors_)), radio(radio_)
  {
  }

  // See interface for documentation.

  /**
   * @brief Sets the downlink centre frequency for a sector.
   * @param sector_id        The cell sector index.
   * @param center_freq_Hz   The new centre frequency in Hz.
   * @return true if the change was applied to the lower PHY; the radio
   *         hardware call is always attempted regardless of sector validity.
   */
  bool set_tx_center_frequency(unsigned sector_id, double center_freq_Hz) override;

  // See interface for documentation.

  /**
   * @brief Sets the uplink centre frequency for a sector.
   * @param sector_id        The cell sector index.
   * @param center_freq_Hz   The new centre frequency in Hz.
   * @return true if the change was applied to the lower PHY.
   */
  bool set_rx_center_frequency(unsigned sector_id, double center_freq_Hz) override;
};

/// SDR Radio Unit transmit time offset controller implementation.

/**
 * @brief Controls the Tx timing offset for a sector.
 *
 * Tx time offset adjusts when, relative to the nominal slot boundary, the
 * downlink IQ samples are actually transmitted. Used for fine timing
 * calibration of the Tx/Rx alignment, or for NTN propagation delay compensation.
 */
class ru_tx_time_offset_controller_sdr_impl : public ru_tx_time_offset_controller
{
  std::vector<lower_phy_sector*> phy_sectors;


public:
  ru_tx_time_offset_controller_sdr_impl() = default;


  /**
   * @param phy_sectors_  Lower PHY sectors, one per cell.
   */
  explicit ru_tx_time_offset_controller_sdr_impl(std::vector<lower_phy_sector*> phy_sectors_) :
    phy_sectors(std::move(phy_sectors_))
  {
  }

  // See interface for documentation.

  /**
   * @brief Sets the transmit timing offset for a sector.
   * @param sector_id        The cell sector index.
   * @param tx_time_offset   The timing offset (in PHY time units, i.e. fractions
   *                         of a sample period at the reference clock rate).
   * @return true if applied; false if sector_id is invalid.
   */
  bool set_tx_time_offset(unsigned sector_id, phy_time_unit tx_time_offset) override;
};

/// SDR Radio Unit controller implementation.

/**
 * @brief The top-level SDR Radio Unit controller.
 *
 * Implements both ru_controller (the external interface) and
 * ru_operation_controller (the start/stop lifecycle interface). Owns the
 * four sub-controllers above and exposes them via accessor methods.
 */
class ru_controller_sdr_impl : public ru_controller, public ru_operation_controller
{
public:
  /**
   * @param srate_MHz_   IQ sample rate in MHz, used to compute slot/subframe
   *                     boundary timestamps for the start() command.
   * @param start_time   Optional absolute start time for synchronised operation.
   */
  ru_controller_sdr_impl(double srate_MHz_, std::optional<std::chrono::system_clock::time_point> start_time);

  // See interface for documentation.

  /// Returns the start/stop lifecycle controller (this object itself).
  ru_operation_controller& get_operation_controller() override { return *this; }

  // See interface for documentation.

  /// Returns the gain controller (Tx/Rx gain via UHD).
  ru_gain_controller* get_gain_controller() override { return &gain_controller; }

  // See interface for documentation.

  /// Returns the CFO controller (frequency offset compensation, used for NTN).
  ru_cfo_controller* get_cfo_controller() override { return &cfo_controller; }

  // See interface for documentation.

  /// Returns the centre frequency controller (Tx/Rx carrier frequency).
  ru_center_frequency_controller* get_center_frequency_controller() override { return &center_freq_controller; }

  // See interface for documentation.

  /// Returns the Tx timing offset controller.
  ru_tx_time_offset_controller* get_tx_time_offset_controller() override { return &tx_time_offset_controller; }

  // See interface for documentation.

  /**
   * @brief Starts the radio and all lower PHY sectors at a synchronised timestamp.
   *
   * Computes the correct radio start timestamp (either at the configured
   * start_time, or 100ms from now if not set) and starts the radio and
   * every lower PHY sector at exactly that timestamp, so all components
   * begin in sync.
   */
  void start() override;

  // See interface for documentation.

  /**
   * @brief Stops the radio and all lower PHY sectors.
   */
  void stop() override;

  /// Sets the radio session of this controller.

  /**
   * @brief Sets the radio session this controller controls.
   * @param session  The constructed radio session (UHD).
   */
  void set_radio(radio_session& session) { radio = &session; }

  /// Set lower phy sectors.

  /**
   * @brief Sets the lower PHY sectors and constructs the four sub-controllers.
   *
   * Called once all sectors have been built. Constructs gain_controller,
   * cfo_controller, center_freq_controller, and tx_time_offset_controller
   * with references to the radio and sectors.
   *
   * @param sectors  The lower PHY sectors, one per configured cell.
   */
  void set_lower_phy_sectors(std::vector<lower_phy_sector*> sectors);


private:
  /// Sample rate in MHz, used for timing calculations in start().
  double                                               srate_MHz;
  /// Optional synchronised start time.
  std::optional<std::chrono::system_clock::time_point> start_time;
  /// The radio session this controller manages.
  radio_session*                                       radio = nullptr;
  /// One lower PHY sector pointer per configured cell.
  std::vector<lower_phy_sector*>                       lower_phy_sectors;
  /// Gain control sub-controller.
  ru_gain_controller_sdr_impl                          gain_controller;
  /// CFO control sub-controller.
  ru_cfo_controller_sdr_impl                           cfo_controller;
  /// Centre frequency control sub-controller.
  ru_center_frequency_controller_sdr_impl              center_freq_controller;
  /// Tx timing offset control sub-controller.
  ru_tx_time_offset_controller_sdr_impl                tx_time_offset_controller;
};


} // namespace ocudu
