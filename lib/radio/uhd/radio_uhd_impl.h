// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_impl.h
 * @brief The top-level UHD radio session — opens and manages the USRP connection.
 *
 * radio_session_uhd_impl is what gets created and stored inside ru_sdr_impl
 * (via ru_sdr_impl::set_radio()). It implements two interfaces:
 *
 *   radio_session:           The generic interface the rest of the codebase
 *                            uses to control the radio (start/stop, read time,
 *                            get baseband gateways).
 *
 *   radio_management_plane:  Runtime control commands (gain, frequency
 *                            changes) issued by ru_controller_sdr_impl on
 *                            behalf of the CLI "tx_gain"/"rx_gain" commands
 *                            or the NTN Doppler compensation handler.
 *
 * Internally, it owns:
 *   - One radio_uhd_device (the actual USB/network connection to the USRP).
 *   - A port-to-stream/channel mapping (since the external interface uses
 *     flat "port" indices, while UHD organises channels by stream).
 *   - One radio_uhd_baseband_gateway per sector (each containing a Tx and Rx
 *     stream pair).
 *
 * radio_factory_uhd_impl is the corresponding factory, instantiated by name
 * ("uhd") via create_radio_factory() in the shared lib/radio/radio_factory.cpp.
 */

#pragma once


#include "radio_config_uhd_validator.h"
#include "radio_uhd_baseband_gateway.h"
#include "radio_uhd_device.h"
#include "radio_uhd_device_type.h"
#include "radio_uhd_multi_usrp.h"
#include "ocudu/radio/radio_factory.h"
#include "ocudu/radio/radio_management_plane.h"


namespace ocudu {

/// Describes a radio session based on UHD that also implements the management and data plane functions.

/**
 * @brief UHD-backed radio session — manages the USRP connection, streams, and runtime control.
 *
 * Implements both radio_session (the data-plane interface used by the rest
 * of the radio stack) and radio_management_plane (the control-plane
 * interface used for runtime gain/frequency changes).
 */
class radio_session_uhd_impl : public radio_session, private radio_management_plane
{
  /// Maps ports to stream and channel indexes.
  /// Maps a flat port index to the (stream_index, channel_index) pair UHD uses internally.
  using port_to_stream_channel = std::pair<unsigned, unsigned>;

  /// Indicates if the initialization of the session was successful.

  /// Whether construction completed successfully (no UHD errors during setup).
  bool is_init_successful = false;
  /// Wraps the UHD device functions.
  /// Wraps the low-level UHD device functions.
  radio_uhd_device device;
  /// Indexes the transmitter port indexes into stream and channel index as first and second.
  /// Maps each Tx port index to its (stream, channel) location.
  static_vector<port_to_stream_channel, RADIO_MAX_NOF_PORTS> tx_port_map;
  /// Indexes the receiver port indexes into stream and channel index as first and second.
  /// Maps each Rx port index to its (stream, channel) location.
  static_vector<port_to_stream_channel, RADIO_MAX_NOF_PORTS> rx_port_map;
  /// Baseband gateways.
  /// One baseband gateway (Tx + Rx stream pair) per configured sector/stream.
  std::vector<std::unique_ptr<radio_uhd_baseband_gateway>> bb_gateways;
  /// The sample rate UHD actually configured (may differ slightly from the
  /// requested rate due to clock divider granularity).
  double                                                   actual_sampling_rate_Hz = 0.0;

  /// \brief Set the synchronization time to GPS mode.
  /// \return True if no exception is caught. Otherwise false.

  /**
   * @brief Sets the USRP's absolute time using the GPS sensor's reported time.
   * @return true if no exception was caught.
   */
  bool set_time_to_gps_time();

  /// \brief Waits for a sensor to be locked.
  /// \param[in] sensor_name Indicates the sensor name.
  /// \param[in] is_mboard Indicates if the sensor is from the motherboard or daughterboard.
  /// \param[in] timeout Indicates the amount of time to wait.
  /// \return True if sensor is found and locked. Otherwise false.

  /**
   * @brief Polls a sensor until it reports "locked" or a timeout expires.
   *
   * Used to wait for the GPS or external reference clock to achieve lock
   * before proceeding — attempting to use an unlocked reference would result
   * in unreliable timing.
   *
   * @param sensor_name  The sensor to poll (e.g. "gps_locked", "ref_locked").
   * @param is_mboard    Whether this is a motherboard sensor (vs daughterboard).
   * @param timeout      Maximum time to wait for lock.
   * @return true if the sensor reports locked within the timeout.
   */
  bool wait_sensor_locked(const std::string& sensor_name, bool is_mboard, std::chrono::milliseconds timeout);

  /// \brief Set transmission gain from the class itself.
  /// \param[in] port_idx Indicates the port index.
  /// \param[in] gain_dB Indicates the gain value.
  /// \return True if the port index and gain value are valid, and no exception is caught. Otherwise false.

  /// Sets transmit gain for a port, with bounds checking. Returns true on success.
  bool set_tx_gain_unprotected(unsigned port_idx, double gain_dB);

  /// \brief Set reception gain from the class itself.
  /// \param[in] port_idx Indicates the port index.
  /// \param[in] gain_dB Indicates the gain value.
  /// \return True if the port index and gain value are valid, and no exception is caught. Otherwise false.

  /// Sets receive gain for a port, with bounds checking. Returns true on success.
  bool set_rx_gain_unprotected(unsigned port_idx, double gain_dB);

  /// \brief Set transmission frequency.
  /// \param[in] port_idx Indicates the port index.
  /// \param[in] frequency Provides the frequency tuning parameters
  /// \return True if the port index and frequency value are valid, and no exception is caught. Otherwise false.

  /// Sets transmit centre frequency for a port. Returns true on success.
  bool set_tx_freq(unsigned port_idx, radio_configuration::lo_frequency frequency);

  /// \brief Set reception frequency.
  /// \param[in] port_idx Indicates the port index.
  /// \param[in] frequency Provides the frequency tuning parameters
  /// \return True if the port index and frequency value are valid, and no exception is caught. Otherwise false.

  /// Sets receive centre frequency for a port. Returns true on success.
  bool set_rx_freq(unsigned port_idx, radio_configuration::lo_frequency frequency);

  /// \brief Start receive streams.
  /// \param[in] init_time Time in which the stream shall start.
  /// \return True if no exception is caught. Otherwise false.

  /**
   * @brief Issues the start command to all receive streams at the given timestamp.
   * @param init_time  The radio sample-clock timestamp at which streaming should begin.
   * @return true if all streams started successfully.
   */
  bool start_rx_stream(baseband_gateway_timestamp init_time);


public:
  /// Constructs a radio session based on UHD.
  /**
   * @brief Constructs and opens a UHD radio session.
   *
   * Performs the entire device bring-up sequence: opens the USRP, validates
   * the connection, sets master clock rate, configures sync/clock sources,
   * waits for clock lock if external/GPSDO, sets Tx/Rx sample rates, sets
   * absolute time, and creates one baseband gateway per configured stream
   * (applying gain and frequency to each channel along the way).
   *
   * If any step fails, construction returns early with is_init_successful
   * left false; the caller (radio_factory_uhd_impl::create()) checks this
   * and returns nullptr rather than a partially-constructed session.
   *
   * @param radio_config    The complete radio configuration (streams, channels, clock, etc.).
   * @param async_executor  Thread executor for asynchronous (non-real-time) UHD calls.
   * @param notifier_       Receives radio event notifications.
   */
  radio_session_uhd_impl(const radio_configuration::radio& radio_config,
                         task_executor&                    async_executor,
                         radio_event_notifier&             notifier_);

  /// \brief Indicates that the radio session was initialized succesfully.
  /// \return True if no exception is caught during initialization. Otherwise false.

  /// Returns true if the session was successfully constructed and is ready to use.
  bool is_successful() const { return is_init_successful; }

  // See interface for documentation.

  /// Returns this object as the management plane interface (for gain/frequency control).
  radio_management_plane& get_management_plane() override { return *this; }

  // See interface for documentation.

  /**
   * @brief Returns the baseband gateway for a given stream (cell sector).
   *
   * @param stream_id  The sector index.
   * @return Reference to that sector's baseband gateway (Tx + Rx stream pair).
   */
  baseband_gateway& get_baseband_gateway(unsigned stream_id) override
  {
    ocudu_assert(stream_id < bb_gateways.size(),
                 "Stream identifier (i.e., {}) exceeds the number of baseband gateways (i.e., {})",
                 stream_id,
                 bb_gateways.size());
    return *bb_gateways[stream_id];
  }

  // See interface for documentation.

  /// Starts all Tx and Rx streams, synchronised to begin at init_time.
  void start(baseband_gateway_timestamp init_time) override;

  // See interface for documentation.

  /// Stops all Tx and Rx streams.
  void stop() override;

  // See interface for documentation.

  /// Sets transmit gain for a port (CLI/runtime control entry point).
  bool set_tx_gain(unsigned port_idx, double gain_dB) override { return set_tx_gain_unprotected(port_idx, gain_dB); }

  // See interface for documentation.

  /// Sets receive gain for a port (CLI/runtime control entry point).
  bool set_rx_gain(unsigned port_idx, double gain_dB) override { return set_rx_gain_unprotected(port_idx, gain_dB); }

  // See interface for documentation.

  /// Sets transmit centre frequency for an entire stream (all its channels), by stream ID.
  bool set_tx_freq(unsigned stream_id, double center_freq_Hz) override;

  // See interface for documentation.

  /// Sets receive centre frequency for an entire stream (all its channels), by stream ID.
  bool set_rx_freq(unsigned stream_id, double center_freq_Hz) override;

  // See interface for documentation.

  /// Reads the USRP's current absolute time, expressed in samples since epoch.
  baseband_gateway_timestamp read_current_time() override;
};

/// Factory for UHD radio session.

/**
 * @brief Factory for creating UHD-backed radio sessions.
 *
 * Registered under the name "uhd" in the shared radio factory list
 * (lib/radio/radio_factory.cpp), selected by the device_driver = "uhd"
 * config value in this deployment.
 */
class radio_factory_uhd_impl : public radio_factory
{
public:
  // See interface for documentation.
  /// Returns the structural configuration validator for UHD radios.
  const radio_configuration::validator& get_configuration_validator() const override
  {
    static radio_config_uhd_config_validator config_validator;
    return config_validator;
  }

  // See interface for documentation.

  /**
   * @brief Creates a UHD radio session.
   *
   * @param config              The radio configuration.
   * @param async_task_executor Thread executor for asynchronous UHD calls.
   * @param notifier            Receives radio event notifications.
   * @return The constructed session, or nullptr if construction failed.
   */
  std::unique_ptr<radio_session> create(const radio_configuration::radio& config,
                                        task_executor&                    async_task_executor,
                                        radio_event_notifier&             notifier) override;
};


} // namespace ocudu
