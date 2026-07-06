// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_impl.cpp
 * @brief Implementation of the UHD radio session: device bring-up, gain/frequency control, start/stop.
 *
 * The constructor is the most important part of this file — it performs the
 * complete sequence required to bring a USRP from "unopened" to "ready to
 * stream IQ samples": opening the device, configuring clocks, setting sample
 * rates, configuring each antenna channel's gain and frequency, and creating
 * the baseband gateway objects the rest of the stack will use.
 */

#include "radio_uhd_impl.h"
#include <thread>
#include <uhd/utils/thread_priority.h>


using namespace ocudu;

/// Wait at most 1s for external clock locking.

/// Maximum time to wait for an external/GPSDO clock reference to achieve lock.
static constexpr std::chrono::milliseconds CLOCK_TIMEOUT{1000};


/**
 * @brief Sets the USRP's absolute time using its onboard GPS sensor.
 *
 * Reads the "gps_time" sensor (available when a GPSDO module is fitted and
 * has a GPS fix), then sets the device's internal clock to that value. This
 * provides an absolute, globally-synchronised time reference — useful for
 * multi-site deployments where exact wall-clock alignment matters.
 *
 * @return true if the GPS time was successfully read and applied.
 */
bool radio_session_uhd_impl::set_time_to_gps_time()
{
  const std::string sensor_name = "gps_time";


  std::vector<std::string> sensors;
  if (!device.get_mboard_sensor_names(sensors)) {
    fmt::print("Error: failed to read sensors. {}\n", device.get_error_message());
    return false;
  }

  // Find sensor name. Error if it is not available.

  if (std::find(sensors.begin(), sensors.end(), sensor_name) == sensors.end()) {
    fmt::print("Error: sensor {} not found.\n", sensor_name);
    return false;
  }

  // Get actual sensor value.

  double frac_secs = 0.0;
  if (!device.get_sensor(sensor_name, frac_secs)) {
    fmt::print("Error: not possible to read sensor {}. {}\n", sensor_name, device.get_error_message());
    return false;
  }

  // Get time and set.

  fmt::print("Setting USRP time to {}s\n", frac_secs);
  if (!device.set_time_unknown_pps(uhd::time_spec_t(frac_secs))) {
    fmt::print("Error: failed to set time. {}\n", device.get_error_message());
    return false;
  }


  return true;
}


/**
 * @brief Polls a named sensor repeatedly until it reports "locked" or the timeout expires.
 *
 * UHD sensors are queried by name (e.g. "gps_locked" for GPSDO sensor lock,
 * "ref_locked" for external/GPSDO reference clock lock). This function
 * first checks the sensor exists in the device's sensor list, then polls it
 * every 10ms until it reports true or the timeout elapses.
 *
 * @param sensor_name  The sensor name to poll.
 * @param is_mboard    True for motherboard sensors, false for daughterboard sensors.
 * @param timeout      Maximum time to wait.
 * @return true if locked within the timeout; false if not found, an error
 *         occurs, or the timeout elapses without locking.
 */
bool radio_session_uhd_impl::wait_sensor_locked(const std::string&        sensor_name,
                                                bool                      is_mboard,
                                                std::chrono::milliseconds timeout)
{
  auto end_time = std::chrono::steady_clock::now() + timeout;

  // Get sensor list.

  // Fetch the appropriate sensor list to check whether sensor_name exists.
  std::vector<std::string> sensors;
  if (is_mboard) {
    // Motherboard sensor.
    if (!device.get_mboard_sensor_names(sensors)) {
      fmt::print("Error: getting mboard sensor names. {}", device.get_error_message());
      return false;
    }
  } else {
    // Daughterboard sensor.
    if (!device.get_rx_sensor_names(sensors)) {
      fmt::print("Error: getting Rx sensor names. {}", device.get_error_message());
      return false;
    }
  }

  // Find sensor name. Error if it is not available.

  if (std::find(sensors.begin(), sensors.end(), sensor_name) == sensors.end()) {
    fmt::print("Error: sensor {} not found.\n", sensor_name);
    return false;
  }


  // Poll every 10ms until locked or timeout.
  do {
    // Get actual sensor value
    bool is_locked = false;
    if (is_mboard) {
      if (!device.get_sensor(sensor_name, is_locked)) {
        fmt::print("Error: reading mboard sensor {}. {}.\n", sensor_name, device.get_error_message());
        return false;
      }
    } else {
      if (!device.get_rx_sensor(sensor_name, is_locked)) {
        fmt::print("Error: reading rx sensor {}. {}.\n", sensor_name, device.get_error_message());
        return false;
      }
    }

    // Return true if the sensor is locked.

    if (is_locked) {
      return true;
    }

    // Sleep some time before trying it again.

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } while (std::chrono::steady_clock::now() < end_time);


  return false;
}


/**
 * @brief Sets Tx gain for a port, with bounds checking against the port map size.
 */
bool radio_session_uhd_impl::set_tx_gain_unprotected(unsigned port_idx, double gain_dB)
{
  if (port_idx >= tx_port_map.size()) {
    fmt::print(
        "Error: transmit port index ({}) exceeds the number of ports ({}).\n", port_idx, (int)tx_port_map.size());
    return false;
  }

  // Setup gain.

  if (!device.set_tx_gain(port_idx, gain_dB)) {
    fmt::print("Error: setting gain for transmitter {}. {}\n", port_idx, device.get_error_message());
    return false;
  }


  return true;
}


/**
 * @brief Sets Rx gain for a port, with bounds checking against the port map size.
 */
bool radio_session_uhd_impl::set_rx_gain_unprotected(unsigned port_idx, double gain_dB)
{
  if (port_idx >= rx_port_map.size()) {
    fmt::print("Error: receive port index ({}) exceeds the number of ports ({}).\n", port_idx, (int)rx_port_map.size());
    return false;
  }

  // Setup gain.

  if (!device.set_rx_gain(port_idx, gain_dB)) {
    fmt::print("Error: setting gain for receiver {}. {}\n", port_idx, device.get_error_message());
    return false;
  }


  return true;
}


/**
 * @brief Sets Tx centre frequency for a port, with bounds checking.
 */
bool radio_session_uhd_impl::set_tx_freq(unsigned port_idx, radio_configuration::lo_frequency frequency)
{
  if (port_idx >= tx_port_map.size()) {
    fmt::print(
        "Error: transmit port index ({}) exceeds the number of ports ({}).\n", port_idx, (int)tx_port_map.size());
    return false;
  }

  // Setup frequency.

  if (!device.set_tx_freq(port_idx, frequency)) {
    fmt::print("Error: setting frequency for transmitter {}. {}\n", port_idx, device.get_error_message());
    return false;
  }


  return true;
}


/**
 * @brief Sets Rx centre frequency for a port, with bounds checking.
 */
bool radio_session_uhd_impl::set_rx_freq(unsigned port_idx, radio_configuration::lo_frequency frequency)
{
  if (port_idx >= rx_port_map.size()) {
    fmt::print("Error: receive port index ({}) exceeds the number of ports ({}).\n", port_idx, (int)tx_port_map.size());
    return false;
  }

  // Setup frequency.

  if (!device.set_rx_freq(port_idx, frequency)) {
    fmt::print("Error: setting frequency for receiver {}. {}.\n", port_idx, device.get_error_message());
    return false;
  }


  return true;
}


/**
 * @brief Issues the start command to all receive streams, synchronised at init_time.
 *
 * @param init_time  The radio sample-clock timestamp at which Rx streaming should begin.
 * @return true if all streams started successfully.
 */
bool radio_session_uhd_impl::start_rx_stream(baseband_gateway_timestamp init_time)
{
  // Immediate start of the stream.
  uhd::time_spec_t time_spec = uhd::time_spec_t::from_ticks(init_time, actual_sampling_rate_Hz);

  // Issue all streams to start.

  for (auto& bb_gateway : bb_gateways) {
    if (!bb_gateway->get_rx_stream().start(time_spec)) {
      return false;
    }
  }


  return true;
}


/**
 * @brief Constructs and brings up the UHD radio session.
 *
 * This is the full device bring-up sequence. Each major step is annotated
 * below; if any step fails, the function returns early, leaving
 * is_init_successful as false — the caller checks this and discards the
 * partially-constructed session.
 */
radio_session_uhd_impl::radio_session_uhd_impl(const radio_configuration::radio& radio_config,
                                               task_executor&                    async_executor_,
                                               radio_event_notifier&             notifier_)
{
  // Disable fast-path (U/L/O) messages.
  // Disable UHD's "fast-path" console messages (single-character U/L/O codes
  // printed directly to the console on every underflow/late/overflow event)
  // — these bypass the logging system and would otherwise spam the terminal;
  // we handle these events properly via the radio_event_notifier instead.
  ::setenv("UHD_LOG_FASTPATH_DISABLE", "1", 0);

  // Set real time priority to UHD threads. All threads created from this thread inherit the priority.

  // Boost UHD's internal threads to near-real-time scheduling priority. All
  // threads UHD creates from this point inherit this priority, which helps
  // avoid OS scheduling jitter on the critical Tx/Rx sample path. Requires
  // elevated privileges (e.g. CAP_SYS_NICE or running as root) — if not
  // available, a warning is printed but startup continues.
  if (uhd_set_thread_priority(0.90, true) != UHD_ERROR_NONE) {
    fmt::print(stderr, "Warning: Scheduling priority of UHD not changed. Cause: Not enough privileges.\n");
  }

  // Set the logging level.

  // Map the configured OCUDU log level to UHD's own console log verbosity,
  // so UHD's internal logging matches the rest of the application's level.
#ifdef UHD_LOG_INFO
  switch (radio_config.log_level) {
    case ocudulog::basic_levels::warning:
      uhd::log::set_console_level(uhd::log::severity_level::warning);
      break;
    case ocudulog::basic_levels::debug:
      uhd::log::set_console_level(uhd::log::severity_level::debug);
      break;
    case ocudulog::basic_levels::error:
      uhd::log::set_console_level(uhd::log::severity_level::error);
      break;
    default:
      uhd::log::set_console_level(uhd::log::severity_level::info);
      break;
  }
#endif


  // Count total Rx and Tx channels across all configured streams (used
  // later to decide whether multi-channel time synchronisation is needed).
  unsigned total_rx_channel_count = 0;
  for (const radio_configuration::stream& stream_config : radio_config.rx_streams) {
    total_rx_channel_count += stream_config.channels.size();
  }


  unsigned total_tx_channel_count = 0;
  for (const radio_configuration::stream& stream_config : radio_config.tx_streams) {
    total_tx_channel_count += stream_config.channels.size();
  }

  // Open device.

  // ── Step 1: Open the device ──────────────────────────────────────────────────
  if (!device.usrp_make(radio_config.args)) {
    fmt::print("Failed to open device with address '{}': {}\n", radio_config.args, device.get_error_message());
    return;
  }

  // Validate USRP connection.

  // ── Step 2: Validate the physical connection (e.g. USB 3 required for B2xx) ──
  if (!device.is_connection_valid()) {
    return;
  }


  // ── Step 3: Set master clock rate (B2xx: automatic; others: fixed defaults) ──
  if (!device.set_automatic_master_clock_rate(radio_config.sampling_rate_Hz)) {
    fmt::print("Error setting master clock rate. {}\n", device.get_error_message());
    return;
  }

  // Set sync source.

  // ── Step 4: Configure clock and sync sources ─────────────────────────────────
  if (!device.set_sync_source(radio_config.clock)) {
    fmt::print("Error: couldn't set sync source: {}\n", device.get_error_message());
    return;
  }

  // Set GPS time if GPSDO is selected.

  // ── Step 5: If using GPSDO, wait for GPS lock before proceeding ──────────────
  if (radio_config.clock.sync == radio_configuration::clock_sources::source::GPSDO) {
    if (!wait_sensor_locked("gps_locked", true, CLOCK_TIMEOUT)) {
      // It blocks until sync source is locked.
      fmt::print("Could not lock reference GPS time source.\n");
      return;
    }
  }

  // Wait until external reference / GPS is locked.

  // ── Step 6: If using an external or GPSDO clock reference, wait for clock lock ─
  if (radio_config.clock.clock == radio_configuration::clock_sources::source::GPSDO ||
      radio_config.clock.clock == radio_configuration::clock_sources::source::EXTERNAL) {
    // It blocks until clock source is locked.
    if (!wait_sensor_locked("ref_locked", true, CLOCK_TIMEOUT)) {
      fmt::print("Could not lock reference clock source.\n");
      return;
    }
  }

  // Set Tx rate.

  // ── Step 7: Set Tx and Rx sample rates ────────────────────────────────────────
  double actual_tx_rate_Hz = 0.0;
  if (!device.set_tx_rate(actual_tx_rate_Hz, radio_config.sampling_rate_Hz)) {
    fmt::print("Error: setting Tx sampling rate. {}\n", device.get_error_message());
    return;
  }
  ocudu_assert(std::isnormal(actual_tx_rate_Hz), "Actual transmit sampling rate is invalid.");

  // Set Rx rate.

  double actual_rx_rate_Hz = 0.0;
  if (!device.set_rx_rate(actual_rx_rate_Hz, radio_config.sampling_rate_Hz)) {
    fmt::print("Error: setting Rx sampling rate. {}\n", device.get_error_message());
    return;
  }
  ocudu_assert(std::isnormal(actual_rx_rate_Hz), "Actual receive sampling rate is invalid.");

  // Overwrite actual.

  // Use the actual Rx rate as the canonical sample rate for timestamp conversions.
  actual_sampling_rate_Hz = actual_rx_rate_Hz;

  // Setup time.

  // ── Step 8: Set the device's absolute time reference ─────────────────────────
  if (radio_config.clock.sync == radio_configuration::clock_sources::source::GPSDO) {
    // Set GPS time if GPSDO is configured.
    // GPSDO: use the GPS-reported absolute time.
    set_time_to_gps_time();
  } else if ((total_rx_channel_count > 1) || (total_tx_channel_count > 1) ||
             (radio_config.clock.sync == radio_configuration::clock_sources::source::EXTERNAL)) {
    // Set time zero to the next pulse.
    // Multi-channel (needs precise alignment) or external sync: set time to
    // zero at the next unknown PPS edge — this synchronises the device's
    // internal sample counter to a known reference point.
    device.set_time_unknown_pps(uhd::time_spec_t());
  }

  // Lists of stream descriptions.

  std::vector<radio_uhd_tx_stream::stream_description> tx_stream_description_list;
  std::vector<radio_uhd_rx_stream::stream_description> rx_stream_description_list;

  // Force OTW format if it is set to default, the device is a B2xx and the total sampling rate exceeds 30.72MHz.

  // ── Step 9: Auto-select a higher-compression OTW format for high-rate B2xx ───
  // B2xx devices connect over USB, which has limited bandwidth. If the OTW
  // format is left at DEFAULT and the total sample rate would exceed what
  // SC16 (16-bit) samples can fit over USB at this rate, switch to SC12
  // (12-bit) to reduce the data rate while staying within USB bandwidth limits.
  radio_configuration::over_the_wire_format otw_format = radio_config.otw_format;
  if ((otw_format == radio_configuration::over_the_wire_format::DEFAULT) &&
      (device.get_type() == radio_uhd_device_type::types::B2xx) &&
      (radio_config.rx_streams.size() * actual_sampling_rate_Hz > 30.72e6)) {
    otw_format = radio_configuration::over_the_wire_format::SC12;
  }

  // For each transmit stream, create stream and configure RF ports.

  // ── Step 10: Configure each Tx stream's channels (ports), gain, and frequency ─
  tx_stream_description_list.reserve(radio_config.tx_streams.size());
  for (unsigned stream_idx = 0, nof_streams = radio_config.tx_streams.size(); stream_idx != nof_streams; ++stream_idx) {
    // Select stream.
    const radio_configuration::stream& stream = radio_config.tx_streams[stream_idx];

    // Prepare stream description.

    radio_uhd_tx_stream::stream_description stream_description = {
        .id               = stream_idx,
        .otw_format       = otw_format,
        .srate_hz         = actual_tx_rate_Hz,
        .args             = stream.args,
        .ports            = {},
        // Discontinuous Tx is enabled whenever the configured mode is not "continuous".
        .discontiuous_tx  = (radio_config.tx_mode != radio_configuration::transmission_mode::continuous),
        .power_ramping_us = radio_config.power_ramping_us};

    // Setup ports.

    // Assign a flat port index for each channel and record the mapping
    // (port → stream + channel) so later calls by port index can find the
    // right UHD channel.
    for (unsigned channel_idx = 0, nof_channels = stream.channels.size(); channel_idx != nof_channels; ++channel_idx) {
      // Select the port index.
      unsigned port_idx = tx_port_map.size();

      // Set channel port.
      stream_description.ports.emplace_back(port_idx);

      // Save the stream and channel indexes for the port.
      tx_port_map.emplace_back(port_to_stream_channel(stream_idx, channel_idx));
    }

    // Setup port.

    // Apply gain and frequency for each port.
    for (unsigned channel_idx = 0, nof_channels = stream.channels.size(); channel_idx != nof_channels; ++channel_idx) {
      // Get the port index.
      unsigned port_idx = stream_description.ports[channel_idx];

      // Extract port configuration.
      const radio_configuration::channel& channel = stream.channels[channel_idx];

      // Setup gain.

      set_tx_gain_unprotected(port_idx, channel.gain_dB);

      // Setup frequency.

      if (!set_tx_freq(port_idx, channel.freq)) {
        return;
      }

      // Inform about ignored argument.

      if (!channel.args.empty()) {
        fmt::print("Warning: transmitter {} unused args.\n", port_idx);
      }
    }

    // Add stream description to the list.

    tx_stream_description_list.emplace_back(stream_description);
  }

  // For each receive stream, create stream and configure RF ports.

  // ── Step 11: Configure each Rx stream's channels (ports), gain, and frequency ─
  rx_stream_description_list.reserve(radio_config.rx_streams.size());
  for (unsigned stream_idx = 0, nof_streams = radio_config.rx_streams.size(); stream_idx != nof_streams; ++stream_idx) {
    // Select stream.
    const radio_configuration::stream& stream = radio_config.rx_streams[stream_idx];

    // Prepare stream description.

    radio_uhd_rx_stream::stream_description stream_description = {
        .id = stream_idx, .srate_Hz = actual_rx_rate_Hz, .otw_format = otw_format, .args = stream.args};

    // Setup ports.

    for (unsigned channel_idx = 0, nof_channels = stream.channels.size(); channel_idx != nof_channels; ++channel_idx) {
      // Select the port index.
      unsigned port_idx = rx_port_map.size();

      // Set channel port.
      stream_description.ports.emplace_back(port_idx);

      // Save the stream and channel indexes for the port.
      rx_port_map.emplace_back(port_to_stream_channel(stream_idx, channel_idx));
    }

    // Setup port.

    for (unsigned channel_idx = 0, nof_channels = stream.channels.size(); channel_idx != nof_channels; ++channel_idx) {
      // Get the port index.
      unsigned port_idx = stream_description.ports[channel_idx];

      // Extract port configuration.
      const radio_configuration::channel& channel = stream.channels[channel_idx];

      // Setup gain.

      if (!set_rx_gain_unprotected(port_idx, channel.gain_dB)) {
        return;
      }

      // Setup frequency.

      if (!set_rx_freq(port_idx, channel.freq)) {
        return;
      }

      // Set the same port for TX and RX.

      // Same-port transmission mode: configure the Rx antenna to use the same
      // physical port as Tx (for single-antenna USRPs that time-share Tx and Rx).
      if (radio_config.tx_mode == radio_configuration::transmission_mode::same_port) {
        // Get the selected TX antenna.
        std::string selected_tx_antenna;
        if (!device.get_selected_tx_antenna(selected_tx_antenna, port_idx)) {
          return;
        }

        // Get the available RX antennas.

        std::vector<std::string> rx_antennas;
        if (!device.get_rx_antennas(rx_antennas, port_idx)) {
          return;
        }

        // If the TX antenna is also available for reception, configure the TX antenna as RX antennas as well.

        // Check the Tx antenna is also a valid Rx antenna before switching to it.
        if (std::find(rx_antennas.begin(), rx_antennas.end(), selected_tx_antenna) != rx_antennas.end()) {
          fmt::print("Same port transmission mode: Selecting antenna {} as Rx antenna for channel {}\n",
                     selected_tx_antenna,
                     port_idx);
          if (!device.set_rx_antenna(selected_tx_antenna, port_idx)) {
            return;
          };
        } else {
          fmt::print("Error: Selected TX antenna, i.e., {}, is not available as RX antenna in channel {}. Same port "
                     "transmission mode not suppored.\n",
                     selected_tx_antenna,
                     port_idx);
        }
      }

      // Inform about ignored argument.

      if (!channel.args.empty()) {
        fmt::print("Warning: transmitter {} unused args.\n", port_idx);
      }
    }

    // Add stream description to the list.

    rx_stream_description_list.emplace_back(stream_description);
  }

  // Create baseband gateways.

  // ── Step 12: Create the baseband gateways (one per Tx/Rx stream pair) ────────
  bb_gateways.reserve(radio_config.tx_streams.size());
  for (unsigned i_stream = 0, nof_streams = radio_config.tx_streams.size(); i_stream != nof_streams; ++i_stream) {
    auto& gateway =
        bb_gateways.emplace_back(std::make_unique<radio_uhd_baseband_gateway>(device,
                                                                              async_executor_,
                                                                              notifier_,
                                                                              tx_stream_description_list[i_stream],
                                                                              rx_stream_description_list[i_stream]));

    // Early return if the gateway was not successfully created.

    if (!gateway->is_successful()) {
      return;
    }
  }

  // Restore thread priorities.

  // ── Step 13: Restore normal thread priority now that setup is complete ───────
  if (uhd_set_thread_priority(0, false) != UHD_ERROR_NONE) {
    fmt::print("Error: setting UHD thread priority.\n");
    return;
  }

  // We are successfully initialized.

  // All steps succeeded — the session is ready for use.
  is_init_successful = true;
}


/**
 * @brief Stops all Tx then all Rx streams.
 */
void radio_session_uhd_impl::stop()
{
  // Signal stop for each transmit stream.
  for (auto& gateway : bb_gateways) {
    gateway->get_tx_stream().stop();
  }

  // Signal stop for each receive stream.

  for (auto& gateway : bb_gateways) {
    gateway->get_rx_stream().stop();
  }
}


/**
 * @brief Starts all Tx streams (immediately) and all Rx streams (synchronised at init_time).
 *
 * @param init_time  The radio sample-clock timestamp for synchronised Rx start.
 */
void radio_session_uhd_impl::start(baseband_gateway_timestamp init_time)
{
  // Issue all Tx streams to start.
  for (auto& bb_gateway : bb_gateways) {
    bb_gateway->get_tx_stream().start();
  }

  // Issue all Rx streams to start.

  if (!start_rx_stream(init_time)) {
    fmt::print("Failed to start Rx streams.\n");
  }
}


/**
 * @brief Reads the USRP's current absolute time, converted to sample ticks.
 */
baseband_gateway_timestamp radio_session_uhd_impl::read_current_time()
{
  uhd::time_spec_t time;
  if (!device.get_time_now(time)) {
    fmt::print("Error retrieving time.\n");
  }
  return time.to_ticks(actual_sampling_rate_Hz);
}


/**
 * @brief Sets the Tx centre frequency for every port belonging to the given stream.
 *
 * @param stream_id        The stream (sector) index.
 * @param center_freq_Hz   The new centre frequency, applied to all the
 *                         stream's antenna ports.
 * @return true if successfully applied to every port.
 */
bool radio_session_uhd_impl::set_tx_freq(unsigned stream_id, double center_freq_Hz)
{
  // Iterate all ports searching for the given stream.
  for (unsigned i_port = 0, end = tx_port_map.size(); i_port != end; ++i_port) {
    // Skip if the stream does not match the given stream.
    if (tx_port_map[i_port].first != stream_id) {
      continue;
    }

    // Set transmit frequency for the port.

    if (!set_tx_freq(i_port, {.center_frequency_Hz = center_freq_Hz, .lo_frequency_Hz = 0.0})) {
      return false;
    }
  }


  return true;
}


/**
 * @brief Sets the Rx centre frequency for every port belonging to the given stream.
 */
bool radio_session_uhd_impl::set_rx_freq(unsigned stream_id, double center_freq_Hz)
{
  // Iterate all ports searching for the given stream.
  for (unsigned i_port = 0, end = rx_port_map.size(); i_port != end; ++i_port) {
    // Skip if the stream does not match the given stream.
    if (rx_port_map[i_port].first != stream_id) {
      continue;
    }

    // Set receive frequency for the port.

    if (!set_rx_freq(i_port, {.center_frequency_Hz = center_freq_Hz, .lo_frequency_Hz = 0.0})) {
      return false;
    }
  }


  return true;
}


/**
 * @brief Factory method: constructs a UHD radio session and validates it succeeded.
 *
 * @param config              The radio configuration.
 * @param async_task_executor Thread executor for asynchronous UHD calls.
 * @param notifier            Receives radio event notifications.
 * @return The session, or nullptr if construction failed at any step.
 */
std::unique_ptr<radio_session> radio_factory_uhd_impl::create(const radio_configuration::radio& config,
                                                              task_executor&                    async_task_executor,
                                                              radio_event_notifier&             notifier)
{
  std::unique_ptr<radio_session_uhd_impl> session =
      std::make_unique<radio_session_uhd_impl>(config, async_task_executor, notifier);
  if (!session->is_successful()) {
    return nullptr;
  }


  return session;
}
