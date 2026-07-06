// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_device.h
 * @brief Low-level wrapper around UHD's multi_usrp object — the direct interface to the USRP.
 *
 * radio_uhd_device is the lowest layer of the UHD driver, sitting directly
 * above the UHD C++ API. It wraps every UHD call this codebase needs in a
 * exception-safe method (via uhd_exception_handler::safe_execution()),
 * applies sensible defaults per device model, and validates that requested
 * values (gain, frequency, sample rate) fall within the hardware's supported
 * ranges before applying them.
 *
 * This is the class that actually opens the USB/network connection to the
 * physical USRP (usrp_make()), and every subsequent operation (setting gain,
 * tuning frequency, creating Tx/Rx streams, reading sensors) goes through
 * this object's methods.
 */

#pragma once


#include "radio_uhd_device_type.h"
#include "radio_uhd_exception_handler.h"
#include "radio_uhd_rx_stream.h"
#include "radio_uhd_tx_stream.h"
#include "ocudu/ocudulog/ocudulog.h"


namespace ocudu {

/// \brief Determines whether a frequency is valid within a range.
///
/// A frequency is considered valid within a range if the range clips the frequency value within 1 Hz error.

/**
 * @brief Determines whether a frequency is achievable within UHD's reported valid range.
 *
 * UHD's frequency ranges aren't always perfectly continuous due to PLL
 * (phase-locked loop) tuning step granularity. This function checks that
 * clipping the requested frequency to the valid range changes it by less
 * than 1 Hz — i.e. the requested value is, for practical purposes, achievable.
 *
 * @param range  The valid frequency range as reported by UHD for this channel.
 * @param freq   The requested frequency in Hz.
 * @return true if the frequency is within 1 Hz of the valid range.
 */
inline bool radio_uhd_device_validate_freq_range(const uhd::freq_range_t& range, double freq)
{
  double clipped_freq = range.clip(freq);
  return std::abs(clipped_freq - freq) < 1.0;
}

/// \brief Determines whether a gain is valid within a range.
///
/// A gain is considered valid within a range if the range clips the frequency value within 0.01 error.

/**
 * @brief Determines whether a gain value is achievable within UHD's reported valid range.
 *
 * Compares the requested gain to the nearest value UHD would actually apply
 * (which is quantised to the hardware's gain step size), using fixed-point
 * comparison at 0.01 dB precision to avoid floating-point rounding issues.
 *
 * @param range  The valid gain range and step size as reported by UHD.
 * @param gain   The requested gain in dB.
 * @return true if the requested gain matches what UHD would actually apply
 *         (within 0.01 dB).
 */
inline bool radio_uhd_device_validate_gain_range(const uhd::gain_range_t& range, double gain)
{
  int64_t clipped_gain = static_cast<uint64_t>(std::round(range.clip(gain, true) * 100));
  int64_t uint_gain    = static_cast<uint64_t>(gain * 100);


  return (clipped_gain == uint_gain);
}


/// Converts a frequency value from Hz to MHz, for use in human-readable log messages.
constexpr double to_MHz(double value_Hz)
{
  return value_Hz * 1e-6;
}


/**
 * @brief Low-level, exception-safe wrapper around UHD's multi_usrp object.
 *
 * Inherits uhd_exception_handler to get the safe_execution() helper, used
 * throughout to catch and report any UHD exceptions as simple bool returns.
 */
class radio_uhd_device : public uhd_exception_handler
{
public:
  /// Constructor: fetches the "RF" logger for debug-level UHD operation logging.
  radio_uhd_device() : logger(ocudulog::fetch_basic_logger("RF")) {}


  /// Returns true if the USRP device object has been successfully created.
  bool is_valid() const { return usrp != nullptr; }


  /**
   * @brief Opens the connection to the USRP hardware.
   *
   * Parses the device address string (e.g. "type=b200" or
   * "addr=192.168.10.2") into a UHD device address dictionary. If no "type"
   * key is given, UHD's device discovery (uhd::device::find()) is used to
   * locate a connected device automatically — this is what allows the
   * config to omit the device type entirely for simple single-USRP setups.
   *
   * Once the device type is known (either given explicitly or discovered),
   * model-specific defaults are applied:
   *
   *   E3xx:  default master clock rate 30.72 MHz.
   *   X3x0:  default master clock rate 184.32 MHz.
   *   X410:  default master clock rate 245.76 MHz.
   *   N3x0:  default master clock rate 122.88 MHz.
   *   N32x:  default master clock rate 245.76 MHz.
   *   B2xx:  no fixed default — enables automatic master clock rate
   *          selection instead (see set_automatic_master_clock_rate()).
   *
   * Network-connected device families (N32x, N3x0, X3x0, X410) also get a
   * default send/receive frame size of 8000 bytes, which tends to give
   * better throughput over ethernet than UHD's built-in default.
   *
   * @param device_address  The UHD device address string (key=value pairs).
   * @return true if the USRP object was successfully created.
   */
  bool usrp_make(const std::string& device_address)
  {
    // Parse args into dictionary.
    // Parse args into a UHD dictionary type.
    uhd::device_addr_t device_addr;
    if (!safe_execution([&device_address, &device_addr]() { device_addr = uhd::device_addr_t(device_address); })) {
      return false;
    }

    // Destroy any previous USRP instance.

    // Destroy any previous USRP instance before opening a new one.
    usrp = nullptr;

    // If device type or name not given in args, select device from found list.

    // If no device type was given, auto-discover a connected device matching
    // the given address (e.g. if only an IP address was specified).
    if (not device_addr.has_key("type")) {
      // Find available devices that match the given device address.
      uhd::device_addrs_t devices = uhd::device::find(device_addr);

      // Stop if no device is found.

      if (devices.empty()) {
        fmt::println("Error: no radio devices found.");
        return false;
      }

      // Select the first available device.

      // Select the first matching device found.
      uhd::device_addr_t first_device_addr = devices.front();
      fmt::print("No device type given, found device with address '{}'\n", first_device_addr.to_string());

      // Append to the device address the device type.

      // Carry the discovered type forward into our device_addr.
      if (first_device_addr.has_key("type")) {
        device_addr.set("type", first_device_addr.get("type"));
      }
    }

    // If device type is known, parse and select default address parameters.

    // Now that the type is known (either given or discovered), apply
    // model-specific defaults if the user hasn't overridden them.
    if (device_addr.has_key("type")) {
      // Get the device type.
      type = radio_uhd_device_type(device_addr.get("type"));


      switch (type) {
        case radio_uhd_device_type::types::E3xx:
          // Set the default master clock rate.
          if (!device_addr.has_key("master_clock_rate")) {
            device_addr.set("master_clock_rate", "30.72e6");
          }
          break;
        case radio_uhd_device_type::types::X3x0:
          // Set the default master clock rate.
          if (!device_addr.has_key("master_clock_rate")) {
            device_addr.set("master_clock_rate", "184.32e6");
          }
          break;
        case radio_uhd_device_type::types::X410:
          // Set the default master clock rate.
          if (!device_addr.has_key("master_clock_rate")) {
            device_addr.set("master_clock_rate", "245.76e6");
          }
          break;
        case radio_uhd_device_type::types::N3x0:
          // Set the default master clock rate.
          if (!device_addr.has_key("master_clock_rate")) {
            device_addr.set("master_clock_rate", "122.88e6");
          }
          break;
        case radio_uhd_device_type::types::N32x:
          // Set the default master clock rate.
          if (!device_addr.has_key("master_clock_rate")) {
            device_addr.set("master_clock_rate", "245.76e6");
          }
          break;
        case radio_uhd_device_type::types::B2xx:
          // B2xx devices have a flexible master clock rate, so we enable
          // automatic selection instead of a fixed default. See
          // set_automatic_master_clock_rate() below.
          if (!device_addr.has_key("master_clock_rate")) {
            automatic_master_clock_rate = true;
          }
          break;
        case radio_uhd_device_type::types::UNKNOWN:
        default:
          // No default parameters are required.
          // No default parameters known for unrecognised device types.
          break;
      }

      // Set frame sizes for network based USRP devices.

      // Network-connected device families benefit from larger frame sizes
      // for better ethernet throughput.
      if ((type == radio_uhd_device_type::types::N32x) || (type == radio_uhd_device_type::types::N3x0) ||
          (type == radio_uhd_device_type::types::X3x0) || (type == radio_uhd_device_type::types::X410)) {
        // Set the default send frame size.
        if (!device_addr.has_key("send_frame_size")) {
          device_addr.set("send_frame_size", "8000");
        }
        // Set the default receive frame size.
        if (!device_addr.has_key("recv_frame_size")) {
          device_addr.set("recv_frame_size", "8000");
        }
      }
    }


    fmt::print("Making USRP object with args '{}'\n", device_addr.to_string());


    // Actually open the connection to the hardware.
    return safe_execution([this, &device_addr]() { usrp = uhd::usrp::multi_usrp::make(device_addr); });
  }


  /**
   * @brief Validates the physical connection to the device meets minimum requirements.
   *
   * Currently only checks B2xx devices, which require USB 3.0 to achieve
   * the throughput needed for real-time 5G operation — USB 2.0 cannot supply
   * enough bandwidth for the IQ sample stream at typical 5G sample rates.
   *
   * @return true if the connection is valid (or the check doesn't apply to
   *         this device type); false if a B2xx device is connected via USB < 3.
   */
  bool is_connection_valid()
  {
    // If the device is a B2xx, check if the USB is version 3.
    if (type == radio_uhd_device_type::types::B2xx) {
      // Get USB version.
      unsigned usb_version = 0;
      bool     success     = safe_execution([this, &usb_version]() {
        usb_version = usrp->get_device()->get_tree()->access<unsigned>("/mboards/0/usb_version").get();
      });

      // The USB version is invalid if the USB version is accessed successfully and the version is not 3.

      if (success && (usb_version != 3)) {
        fmt::print("USRP operating over USB version {}, USB 3 is required.\n", usb_version);
        return false;
      }
    }


    return true;
  }


  /// Returns the detected device family (B2xx, X3x0, N3x0, etc.).
  radio_uhd_device_type get_type() const { return type; }


  /// Retrieves the list of available motherboard sensor names (e.g. "gps_locked", "ref_locked").
  bool get_mboard_sensor_names(std::vector<std::string>& sensors)
  {
    return safe_execution([this, &sensors]() { sensors = usrp->get_mboard_sensor_names(); });
  }


  /// Retrieves the list of available Rx daughterboard sensor names.
  bool get_rx_sensor_names(std::vector<std::string>& sensors)
  {
    return safe_execution([this, &sensors]() { sensors = usrp->get_rx_sensor_names(); });
  }


  /// Reads a motherboard sensor's value as a real (floating point) number, e.g. GPS time.
  bool get_sensor(const std::string& sensor_name, double& sensor_value)
  {
    return safe_execution(
        [this, &sensor_name, &sensor_value]() { sensor_value = usrp->get_mboard_sensor(sensor_name).to_real(); });
  }


  /// Reads a motherboard sensor's value as a boolean, e.g. "gps_locked" or "ref_locked".
  bool get_sensor(const std::string& sensor_name, bool& sensor_value)
  {
    return safe_execution(
        [this, &sensor_name, &sensor_value]() { sensor_value = usrp->get_mboard_sensor(sensor_name).to_bool(); });
  }


  /// Reads an Rx daughterboard sensor's value as a boolean (e.g. LO lock status).
  bool get_rx_sensor(const std::string& sensor_name, bool& sensor_value)
  {
    return safe_execution(
        [this, &sensor_name, &sensor_value]() { sensor_value = usrp->get_rx_sensor(sensor_name).to_bool(); });
  }


  /// Sets the USRP's absolute time, synchronised at the next unknown PPS edge.
  bool set_time_unknown_pps(const uhd::time_spec_t& timespec)
  {
    return safe_execution([this, &timespec]() { usrp->set_time_unknown_pps(timespec); });
  }


  /// Retrieves the list of available Rx antenna port names for a channel.
  bool get_rx_antennas(std::vector<std::string>& rx_antennas, unsigned channel_id)
  {
    return safe_execution([this, &rx_antennas, channel_id]() { rx_antennas = usrp->get_rx_antennas(channel_id); });
  }


  /// Selects which physical antenna port is used for Rx on a given channel.
  bool set_rx_antenna(const std::string& rx_antenna, unsigned channel_id)
  {
    return safe_execution([this, &rx_antenna, channel_id]() { usrp->set_rx_antenna(rx_antenna, channel_id); });
  }


  /// Retrieves the currently selected Tx antenna port name for a channel.
  bool get_selected_tx_antenna(std::string& tx_antenna, unsigned channel_id)
  {
    return safe_execution([this, &tx_antenna, channel_id]() { tx_antenna = usrp->get_tx_antenna(channel_id); });
  }


  /**
   * @brief Selects the optimal master clock rate for B2xx devices.
   *
   * The master clock rate is the FPGA's internal sample clock, from which the
   * actual Tx/Rx sample rate is derived (typically by integer decimation).
   * B2xx devices support a configurable master clock rate, so this picks the
   * value within the device's valid range that's nearest to the requested
   * sample rate. For other device families, this is a no-op (they use a
   * fixed default applied in usrp_make() instead).
   *
   * @param srate_Hz  The desired sample rate, used to choose the nearest
   *                  valid master clock rate.
   * @return true if successful (or not applicable for this device type).
   */
  bool set_automatic_master_clock_rate(double srate_Hz)
  {
    // Skip automatic master clock rate if it is not available.
    if (!automatic_master_clock_rate) {
      return true;
    }


    return safe_execution([this, srate_Hz]() {
      // Get range of valid master clock rates.
      uhd::meta_range_t range = usrp->get_master_clock_rate_range();

      // Select the nearest valid master clock rate.
      double mcr_Hz = range.clip(srate_Hz);

      usrp->set_master_clock_rate(mcr_Hz);
    });
  }


  /// Reads the USRP's current absolute time.
  bool get_time_now(uhd::time_spec_t& timespec)
  {
    return safe_execution([this, &timespec]() { timespec = usrp->get_time_now(); });
  }


  /**
   * @brief Configures the USRP's reference clock and timing synchronisation sources.
   *
   * Two distinct things are configured here, both derived from the same
   * radio_configuration::clock_sources struct:
   *
   *   clock source ("clock_src"): where the device gets its reference
   *     oscillator frequency from. "internal" uses the device's own TCXO/OCXO;
   *     "external" uses an external 10 MHz reference; "gpsdo" uses a
   *     GPS-disciplined oscillator if the device has one fitted.
   *
   *   sync/time source ("sync_src" / time source): where the device gets its
   *     PPS (Pulse-Per-Second) timing pulse from, used to align the absolute
   *     sample timestamp across multiple devices. Same three options.
   *
   * The implementation has two code paths depending on the UHD library
   * version: older versions (< 3.14.0) use separate set_time_source() and
   * set_clock_source() calls with explicit validation against the supported
   * source lists; newer versions use the combined set_sync_source() API.
   *
   * @param config  The desired clock and sync source settings.
   * @return true if successfully applied.
   */
  bool set_sync_source(const radio_configuration::clock_sources& config)
  {
    // Convert clock source to string.
    // Map the clock source enum to the string UHD expects.
    std::string clock_src;
    switch (config.clock) {
      case radio_configuration::clock_sources::source::DEFAULT:
      case radio_configuration::clock_sources::source::INTERNAL:
        clock_src = "internal";
        break;
      case radio_configuration::clock_sources::source::EXTERNAL:
        clock_src = "external";
        break;
      case radio_configuration::clock_sources::source::GPSDO:
        clock_src = "gpsdo";
        break;
    }

    // Convert sync source to string.

    // Map the sync/time source enum to the string UHD expects.
    std::string sync_src;
    switch (config.sync) {
      case radio_configuration::clock_sources::source::DEFAULT:
      case radio_configuration::clock_sources::source::INTERNAL:
        sync_src = "internal";
        break;
      case radio_configuration::clock_sources::source::EXTERNAL:
        sync_src = "external";
        break;
      case radio_configuration::clock_sources::source::GPSDO:
        sync_src = "gpsdo";
        break;
    }


    logger.debug("Setting PPS source to '{}' and clock source to '{}'.", sync_src, clock_src);
#if UHD_VERSION < 3140099
    // Older UHD versions require separately validating and setting time/clock source.
    return safe_execution([this, &sync_src, &clock_src]() {
      std::vector<std::string> time_sources = usrp->get_time_sources(0);
      if (std::find(time_sources.begin(), time_sources.end(), sync_src) == time_sources.end()) {
        on_error("Invalid time source {}. Supported: {}", sync_src, span<const std::string>(time_sources));
        return;
      }
      std::vector<std::string> clock_sources = usrp->get_clock_sources(0);
      if (std::find(clock_sources.begin(), clock_sources.end(), clock_src) == clock_sources.end()) {
        on_error("Invalid clock source {}. Supported: {}", clock_src, span<const std::string>(clock_sources));
        return;
      }


      usrp->set_time_source(sync_src);
      usrp->set_clock_source(clock_src);
    });
#else
    // Newer UHD versions expose a combined sync-source setter.
    return safe_execution([this, &sync_source, &clock_source]() { usrp->set_sync_source(clock_source, sync_source); });
#endif
  }


  /**
   * @brief Sets the Rx sample rate, validating it against the device's supported range.
   *
   * @param actual_rate  Output: the rate UHD actually configured (may differ
   *                     slightly from the requested rate due to clock divider
   *                     granularity).
   * @param rate         The requested Rx sample rate in Hz.
   * @return true if the rate was valid and successfully set.
   */
  bool set_rx_rate(double& actual_rate, double rate)
  {
    logger.debug("Setting Rx Rate to {} MHz.", to_MHz(rate));


    return safe_execution([this, &actual_rate, rate]() {
      uhd::meta_range_t range = usrp->get_rx_rates();


      if (!radio_uhd_device_validate_freq_range(range, rate)) {
        on_error("Rx Rate {} MHz is invalid. The nearest valid value is {}.", to_MHz(rate), to_MHz(range.clip(rate)));
        return;
      }


      usrp->set_rx_rate(rate);

      actual_rate = usrp->get_rx_rate();
    });
  }


  /**
   * @brief Sets the Tx sample rate, validating it against the device's supported range.
   *
   * @param actual_rate  Output: the rate UHD actually configured.
   * @param rate         The requested Tx sample rate in Hz.
   * @return true if the rate was valid and successfully set.
   */
  bool set_tx_rate(double& actual_rate, double rate)
  {
    logger.debug("Setting Tx Rate to {} MHz.", to_MHz(rate));


    return safe_execution([this, &actual_rate, rate]() {
      uhd::meta_range_t range = usrp->get_tx_rates();


      if (!radio_uhd_device_validate_freq_range(range, rate)) {
        on_error("Tx Rate {} MHz is invalid. The nearest valid value is {}.", to_MHz(rate), to_MHz(range.clip(rate)));
        return;
      }


      usrp->set_tx_rate(rate);

      actual_rate = usrp->get_tx_rate();
    });
  }


  /// Sets the time at which subsequent USRP commands (e.g. gain/frequency changes) should take effect.
  bool set_command_time(const uhd::time_spec_t& timespec)
  {
    return safe_execution([this, &timespec]() { usrp->set_command_time(timespec); });
  }


  /**
   * @brief Creates a UHD transmit stream and wraps it in a radio_uhd_tx_stream object.
   *
   * @param async_executor  Thread executor for processing asynchronous Tx event messages.
   * @param notifier        Receives notifications of Tx events (late/underflow/etc.).
   * @param description     Stream configuration (sample rate, ports, OTW format).
   * @return The constructed Tx stream, or nullptr if creation failed.
   */
  std::unique_ptr<radio_uhd_tx_stream> create_tx_stream(task_executor&                                 async_executor,
                                                        radio_event_notifier&                          notifier,
                                                        const radio_uhd_tx_stream::stream_description& description)
  {
    std::unique_ptr<radio_uhd_tx_stream> stream =
        std::make_unique<radio_uhd_tx_stream>(usrp, description, async_executor, notifier);


    if (stream->is_successful()) {
      return stream;
    }


    return nullptr;
  }


  /**
   * @brief Creates a UHD receive stream and wraps it in a radio_uhd_rx_stream object.
   *
   * @param notifier     Receives notifications of Rx events (late/overflow/etc.).
   * @param description  Stream configuration (sample rate, ports, OTW format).
   * @return The constructed Rx stream, or nullptr if creation failed (with an
   *         error message printed to stdout).
   */
  std::unique_ptr<radio_uhd_rx_stream> create_rx_stream(radio_event_notifier&                          notifier,
                                                        const radio_uhd_rx_stream::stream_description& description)
  {
    std::unique_ptr<radio_uhd_rx_stream> stream = std::make_unique<radio_uhd_rx_stream>(usrp, description, notifier);


    if (stream->is_successful()) {
      return stream;
    }


    fmt::println("Error: failed to create receive stream {}. {}.", description.id, stream->get_error_message().c_str());
    return nullptr;
  }


  /**
   * @brief Sets transmit gain for a channel, validating against the device's supported range.
   *
   * @param ch    The channel index.
   * @param gain  The requested gain in dB.
   * @return true if the gain was valid and successfully set.
   */
  bool set_tx_gain(unsigned ch, double gain)
  {
    logger.debug("Setting channel {} Tx gain to {:.2f} dB.", ch, gain);


    return safe_execution([this, ch, gain]() {
      uhd::gain_range_t range = usrp->get_tx_gain_range(ch);


      if (!radio_uhd_device_validate_gain_range(range, gain)) {
        on_error("Tx gain (i.e., {} dB) is out-of-range. Range is [{}, {}] dB in steps of {} dB.",
                 gain,
                 range.start(),
                 range.stop(),
                 range.step());
        return;
      }


      usrp->set_tx_gain(gain, ch);
    });
  }


  /**
   * @brief Sets receive gain for a channel, validating against the device's supported range.
   *
   * @param ch    The channel index.
   * @param gain  The requested gain in dB.
   * @return true if the gain was valid and successfully set.
   */
  bool set_rx_gain(size_t ch, double gain)
  {
    logger.debug("Setting channel {} Rx gain to {:.2f} dB.", ch, gain);


    return safe_execution([this, ch, gain]() {
      uhd::gain_range_t range = usrp->get_rx_gain_range(ch);


      if (!radio_uhd_device_validate_gain_range(range, gain)) {
        on_error("Rx gain (i.e., {} dB) is out-of-range. Range is [{}, {}] dB in steps of {} dB.",
                 gain,
                 range.start(),
                 range.stop(),
                 range.step());
        return;
      }


      usrp->set_rx_gain(gain, ch);
    });
  }


  /**
   * @brief Sets the transmit centre frequency for a channel.
   *
   * Supports both standard tuning (UHD automatically picks LO and DSP
   * frequencies) and manual LO frequency control: if config.lo_frequency_Hz
   * is set, the LO is forced to that specific frequency and the digital
   * (DSP) frequency shift is computed automatically to make up the
   * difference to the requested centre frequency. Manual LO control is used
   * to move LO leakage (a spurious tone at the LO frequency) out of the
   * desired signal band.
   *
   * @param ch      The channel index.
   * @param config  Centre frequency and optional LO frequency override.
   * @return true if the frequency was valid and successfully set.
   */
  bool set_tx_freq(uint32_t ch, const radio_configuration::lo_frequency& config)
  {
    logger.debug("Setting channel {} Tx frequency to {} MHz.", ch, to_MHz(config.center_frequency_Hz));


    return safe_execution([this, ch, &config]() {
      uhd::freq_range_t range = usrp->get_tx_freq_range(ch);


      if (!radio_uhd_device_validate_freq_range(range, config.center_frequency_Hz)) {
        on_error("Tx RF frequency {} MHz is out-of-range. Range is {}.",
                 to_MHz(config.center_frequency_Hz),
                 range.to_pp_string());
        return;
      }

      // Create tune request.

      uhd::tune_request_t tune_request(config.center_frequency_Hz);

      // If the LO frequency is defined, force a LO frequency and set the DSP frequency to auto.

      // If an LO frequency override is given, force it and let UHD compute
      // the DSP (digital) frequency shift automatically.
      if (std::isnormal(config.lo_frequency_Hz)) {
        tune_request.rf_freq         = config.lo_frequency_Hz;
        tune_request.rf_freq_policy  = uhd::tune_request_t::POLICY_MANUAL;
        tune_request.dsp_freq_policy = uhd::tune_request_t::POLICY_AUTO;
      }


      usrp->set_tx_freq(tune_request, ch);
    });
  }


  /**
   * @brief Sets the receive centre frequency for a channel.
   *
   * Same logic as set_tx_freq() above, applied to the receive path.
   *
   * @param ch      The channel index.
   * @param config  Centre frequency and optional LO frequency override.
   * @return true if the frequency was valid and successfully set.
   */
  bool set_rx_freq(uint32_t ch, const radio_configuration::lo_frequency& config)
  {
    logger.debug("Setting channel {} Rx frequency to {} MHz.", ch, to_MHz(config.center_frequency_Hz));


    return safe_execution([this, ch, &config]() {
      uhd::freq_range_t range = usrp->get_rx_freq_range(ch);


      if (!radio_uhd_device_validate_freq_range(range, config.center_frequency_Hz)) {
        on_error("Rx RF frequency {} MHz is out-of-range. Range is {}.",
                 to_MHz(config.center_frequency_Hz),
                 range.to_pp_string());
        return;
      }

      // Create tune request.

      uhd::tune_request_t tune_request(config.center_frequency_Hz);

      // If the LO frequency is defined, force a LO frequency and set the DSP frequency to auto.

      if (std::isnormal(config.lo_frequency_Hz)) {
        tune_request.rf_freq         = config.lo_frequency_Hz;
        tune_request.rf_freq_policy  = uhd::tune_request_t::POLICY_MANUAL;
        tune_request.dsp_freq_policy = uhd::tune_request_t::POLICY_AUTO;
      }


      usrp->set_rx_freq(tune_request, ch);
    });
  }


private:
  /// The UHD multi_usrp object itself — null until usrp_make() succeeds.
  uhd::usrp::multi_usrp::sptr usrp                        = nullptr;
  /// The detected device family (set during usrp_make()).
  radio_uhd_device_type       type                        = radio_uhd_device_type::types::UNKNOWN;
  /// Whether to auto-select the master clock rate (true only for B2xx devices
  /// without an explicit master_clock_rate argument).
  bool                        automatic_master_clock_rate = false;
  /// Logger for UHD-related debug messages (gain/frequency changes, etc.).
  ocudulog::basic_logger&     logger;
};


} // namespace ocudu
