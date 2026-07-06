// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_config_uhd_validator.cpp
 * @brief Implementation of structural validation for UHD radio configurations.
 *
 * Each sub-validator function checks one aspect of the configuration and
 * prints a specific error message if invalid. The top-level
 * is_configuration_valid() runs them all in sequence, stopping at the first failure.
 */

#include "radio_config_uhd_validator.h"
#include "fmt/base.h"
#include <regex>
#include <set>


using namespace ocudu;


/**
 * @brief Validates that the clock and sync source enum values are recognised.
 *
 * @param sources  Contains the clock source (reference oscillator) and sync
 *                 source (timing/1PPS reference) settings.
 * @return true if both are one of the recognised values (DEFAULT, INTERNAL,
 *         EXTERNAL, GPSDO).
 */
static bool validate_clock_sources(const radio_configuration::clock_sources& sources)
{
  static const std::set<radio_configuration::clock_sources::source> valid_clock_sources = {
      radio_configuration::clock_sources::source::DEFAULT,
      radio_configuration::clock_sources::source::INTERNAL,
      radio_configuration::clock_sources::source::EXTERNAL,
      radio_configuration::clock_sources::source::GPSDO};


  if (valid_clock_sources.count(sources.clock) == 0) {
    fmt::print("Invalid clock source.\n");
    return false;
  }


  if (valid_clock_sources.count(sources.sync) == 0) {
    fmt::print("Invalid sync source.\n");
    return false;
  }


  return true;
}


/**
 * @brief Validates that a centre frequency value is a sensible non-zero, finite number.
 *
 * @param lo_freq  Frequency tuning parameters (centre frequency and optional LO offset).
 * @param is_tx    Used only for the error message wording (Tx vs Rx).
 * @return true if the centre frequency passes std::isnormal() (non-zero,
 *         non-subnormal, finite).
 */
static bool validate_lo_freq(const radio_configuration::lo_frequency& lo_freq, bool is_tx)
{
  if (!std::isnormal(lo_freq.center_frequency_Hz)) {
    fmt::print("{} center frequency must be non-zero, NAN nor infinite.\n", is_tx ? "TX" : "RX");
    return false;
  }


  return true;
}


/**
 * @brief Validates the format of a UHD device/channel/stream arguments string.
 *
 * UHD device arguments use a comma-separated key=value format, e.g.
 * "type=b200,master_clock_rate=30.72e6". This function checks the string
 * matches that expected pattern using a regular expression, catching typos
 * before they reach UHD (which would otherwise either silently ignore the
 * malformed argument or throw a less helpful error).
 *
 * @param args  The arguments string to check.
 * @return true if empty (no arguments is valid) or matches the key=value
 *         comma-separated pattern; false otherwise.
 */
static bool validate_args_format(const std::string& args)
{
  // Empty arguments are valid.
  // Empty arguments are valid.
  if (args.empty()) {
    return true;
  }

  // Channel argument example: channel_arg0=123,channel_arg2=foo

  // Channel argument example: channel_arg0=123,channel_arg2=foo
  std::cmatch cmatch;
  std::regex  exp_channel_args(R"(^((([A-z]|_|[0-9])*\=([A-z]|_|[0-9])*),*)*$)");
  std::regex_match(args.c_str(), cmatch, exp_channel_args);


  if (cmatch.empty()) {
    fmt::print("Arguments '{}' format is invalid.\n", args);
    return false;
  }


  return true;
}


/**
 * @brief Validates one channel's configuration (frequency, gain, arguments).
 *
 * @param channel  The channel config to validate.
 * @param is_tx    Used for error message wording.
 * @return true if frequency, gain, and arguments are all valid.
 */
static bool validate_channel(const radio_configuration::channel& channel, bool is_tx)
{
  if (!validate_lo_freq(channel.freq, is_tx)) {
    return false;
  }


  if (std::isnan(channel.gain_dB) || std::isinf(channel.gain_dB)) {
    fmt::print("Channel gain must not be NAN nor infinite.\n");
    return false;
  }


  if (!validate_args_format(channel.args)) {
    return false;
  }


  return true;
}


/**
 * @brief Validates one stream's configuration (its channel list and arguments).
 *
 * A "stream" groups one or more channels together (e.g. for a MIMO USRP with
 * 2 Tx antennas, the single Tx stream would contain 2 channels).
 *
 * @param stream  The stream config to validate.
 * @param is_tx   Used for error message wording.
 * @return true if the stream has at least one channel and all its channels
 *         and arguments are valid.
 */
static bool validate_stream(const radio_configuration::stream& stream, bool is_tx)
{
  if (stream.channels.empty()) {
    fmt::print("Streams must contain at least one channel.\n");
    return false;
  }


  for (const radio_configuration::channel& channel : stream.channels) {
    if (!validate_channel(channel, is_tx)) {
      return false;
    }
  }


  if (!validate_args_format(stream.args)) {
    return false;
  }


  return true;
}


/**
 * @brief Validates that the sample rate is a sensible positive, finite number.
 *
 * @param sampling_rate  The configured sample rate in Hz.
 * @return true if std::isnormal() and greater than zero.
 */
static bool validate_sampling_rate(double sampling_rate)
{
  if (!std::isnormal(sampling_rate)) {
    fmt::print("The sampling rate must be non-zero, NAN nor infinite.\n");
    return false;
  }


  if (sampling_rate < 0.0) {
    fmt::print("The sampling rate must be greater than zero.\n");
    return false;
  }


  return true;
}


/**
 * @brief Validates that the over-the-wire (OTW) format enum value is recognised.
 *
 * Note: SC8 is intentionally absent from this validation set even though
 * radio_uhd_tx_stream.cpp and radio_uhd_rx_stream.cpp both handle it — this
 * suggests SC8 may not be fully validated here (a potential gap worth being
 * aware of if you encounter SC8-related configuration issues).
 *
 * @param otw_format  The configured over-the-wire format.
 * @return true if it's one of DEFAULT, SC12, or SC16.
 */
static bool validate_otw_format(radio_configuration::over_the_wire_format otw_format)
{
  static const std::set<radio_configuration::over_the_wire_format> valid_otw_formats = {
      radio_configuration::over_the_wire_format::DEFAULT,
      radio_configuration::over_the_wire_format::SC12,
      radio_configuration::over_the_wire_format::SC16};


  if (valid_otw_formats.count(otw_format) == 0) {
    fmt::print("The selected over the wire format is not supported.\n");
    return false;
  }


  return true;
}


/**
 * @brief Validates the complete UHD radio configuration.
 *
 * Runs all the sub-validators above in sequence. A few notable checks:
 *
 *   - Tx and Rx stream counts must match (one Rx stream per Tx stream — they're
 *     paired by index throughout the rest of the driver).
 *   - At least one stream must be configured.
 *   - For B2x0 devices specifically (detected via the "type=b2" substring in
 *     the device args), the number of Tx and Rx antennas per stream must match
 *     — these devices don't support asymmetric MIMO configurations.
 *   - Power ramping time must be non-negative.
 *
 * @param config  The complete radio configuration to validate.
 * @return true if every check passes; false on the first failure.
 */
bool radio_config_uhd_config_validator::is_configuration_valid(const radio_configuration::radio& config) const
{
  if (!validate_clock_sources(config.clock)) {
    return false;
  }


  if (config.tx_streams.size() != config.rx_streams.size()) {
    fmt::print("Transmit and receive number of streams must be equal.\n");
    return false;
  }


  if (config.tx_streams.empty()) {
    fmt::print("At least one transmit and one receive stream must be configured.\n");
    return false;
  }


  for (const radio_configuration::stream& tx_stream : config.tx_streams) {
    if (!validate_stream(tx_stream, true)) {
      return false;
    }
  }


  for (const radio_configuration::stream& rx_stream : config.rx_streams) {
    if (!validate_stream(rx_stream, false)) {
      return false;
    }
  }


  // Note: this duplicates the earlier check (apparent redundancy in the
  // original code), but is harmless since the condition was already verified true.
  if (config.tx_streams.size() != config.rx_streams.size()) {
    fmt::print("Transmit and receive number of streams must be equal.\n");
    return false;
  }


  // B2x0-specific constraint: these devices do not support a different
  // number of Tx and Rx antennas on the same stream.
  if (config.args.find("type=b2") != std::string::npos) {
    for (unsigned i_stream = 0, nof_streams = config.tx_streams.size(); i_stream != nof_streams; ++i_stream) {
      if (config.tx_streams[i_stream].channels.size() != config.rx_streams[i_stream].channels.size()) {
        fmt::print("B2x0 devices do not support different number of transmit and receive antennas.\n");
        return false;
      }
    }
  }


  if (!validate_sampling_rate(config.sampling_rate_Hz)) {
    return false;
  }


  if (!validate_otw_format(config.otw_format)) {
    return false;
  }


  if (config.power_ramping_us < 0) {
    fmt::print("Power ramping time, i.e., {:.1f} us, must be positive or zero.\n", config.power_ramping_us);
    return false;
  }


  return true;
}
