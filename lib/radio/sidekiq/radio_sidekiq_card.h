// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/sidekiq/radio_sidekiq_card.h  (124 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "radio_sidekiq_rx_stream.h"
#include "radio_sidekiq_tx_stream.h"
#include "ocudu/gateways/baseband/baseband_gateway.h"
#include <memory>
#include <sidekiq_api.h>
#include <sidekiq_params.h>


namespace ocudu {

/// \brief Sidekiq card management class.
///
/// It implements the baseband gateway interface for Sidekiq radios.

/// \brief Sidekiq card management class.
///
/// It implements the baseband gateway interface for Sidekiq radios.
class radio_sidekiq_card : public baseband_gateway
{
public:
  /// Parameters specific to each transmit port.
  /// Parameters specific to each transmit port.
  struct tx_port_params {
    /// TX gain.
    /// TX gain.
    double tx_gain_dB;
    /// TX frequency.
    /// TX frequency.
    double tx_freq_Hz;
  };

  /// Parameters specific to each receive port.

  /// Parameters specific to each receive port.
  struct rx_port_params {
    /// RX gain.
    /// RX gain.
    double rx_gain_dB;
    /// RX frequency.
    /// RX frequency.
    double rx_freq_Hz;
  };

  /// Sidekiq card configuration parameters.

  /// Sidekiq card configuration parameters.
  struct card_description {
    /// Card identifier.
    /// Card identifier.
    unsigned card_id;
    /// Sidekiq stream mode.
    /// Sidekiq stream mode.
    skiq_rx_stream_mode_t stream_mode;
    /// Card sampling rate.
    /// Card sampling rate.
    double srate_Hz;
    /// TX port configuration parameters.
    /// TX port configuration parameters.
    std::vector<tx_port_params> tx_port_config;
    /// RX port configuration parameters.
    /// RX port configuration parameters.
    std::vector<rx_port_params> rx_port_config;
    /// Packed mode flag.
    /// Packed mode flag.
    bool packed_mode;
  };

  /// Constructs a sidekiq radio card.

  /// Constructs a sidekiq radio card.
  radio_sidekiq_card(task_executor&          async_executor,
                     radio_event_notifier&   notifier,
                     const card_description& card_config);

  // See interface for documentation.

  // See interface for documentation.
  baseband_gateway_transmitter& get_transmitter() override { return *tx_stream; }

  // See interface for documentation.

  // See interface for documentation.
  baseband_gateway_receiver& get_receiver() override { return *rx_stream; }

  // See interface for documentation.

  // See interface for documentation.
  unsigned get_transmitter_optimal_buffer_size() const override { return tx_stream->get_buffer_size(); }

  // See interface for documentation.

  // See interface for documentation.
  unsigned get_receiver_optimal_buffer_size() const override { return rx_stream->get_buffer_size(); }

  /// Gets the transmit port instance.

  /// Gets the transmit port instance.
  radio_sidekiq_tx_stream& get_tx_stream() { return *tx_stream; }

  /// Gets the receive port instance.

  /// Gets the receive port instance.
  radio_sidekiq_rx_stream& get_rx_stream() { return *rx_stream; }

  /// Sets the transmit gain for a specific port.

  /// Sets the transmit gain for a specific port.
  bool set_tx_gain(unsigned i_channel, double gain_dB);

  /// Sets the receive gain for a specific port.

  /// Sets the receive gain for a specific port.
  bool set_rx_gain(unsigned i_channel, double gain_dB);

  /// Checks if the card and its radio streams are successfully initialized.

  /// Checks if the card and its radio streams are successfully initialized.
  bool is_successful() const
  {
    return tx_stream && tx_stream->init_successful() && rx_stream && rx_stream->init_successful() &&
           (state.load() == card_states::SUCCESSFUL_INIT);
  }

  /// Stops the radio streams and disables the Sidekiq card.

  /// Stops the radio streams and disables the Sidekiq card.
  void stop();


private:
  /// States of the Sidekiq card.
  /// States of the Sidekiq card.
  enum class card_states { UNINITIALIZED, SUCCESSFUL_INIT, STOP };

  /// Sets the TX LO frequency.

  /// Sets the TX LO frequency.
  bool set_tx_lo_freq(unsigned i_channel, double freq_Hz);

  /// Sets the RX LO frequency.

  /// Sets the RX LO frequency.
  bool set_rx_lo_freq(unsigned i_channel, double freq_Hz);

  /// Current card state.

  /// Current card state.
  std::atomic<card_states> state = {card_states::UNINITIALIZED};
  /// Transmit stream.
  /// Transmit stream.
  std::unique_ptr<radio_sidekiq_tx_stream> tx_stream;
  /// Receive stream.
  /// Receive stream.
  std::unique_ptr<radio_sidekiq_rx_stream> rx_stream;
  /// Card identifier.
  /// Card identifier.
  unsigned card_id;
  /// Number of RF ports in the Tx stream.
  /// Number of RF ports in the Tx stream.
  unsigned nof_tx_ports;
  /// Number of RF ports in the Rx stream.
  /// Number of RF ports in the Rx stream.
  unsigned nof_rx_ports;
  /// Sidekiq card parameters obtained from the SDK during initialization.
  /// Sidekiq card parameters obtained from the SDK during initialization.
  skiq_param_t card_params;
  /// Sidekiq card channel mode, it indicates if single of dual transmission is configured.
  /// Sidekiq card channel mode, it indicates if single of dual transmission is configured.
  skiq_chan_mode_t channel_mode;
  /// Logger instance.
  /// Logger instance.
  ocudulog::basic_logger& logger;
  /// Receive timeout in microseconds.
  /// Receive timeout in microseconds.
  static constexpr double rx_timeout_us = 1000;
};


} // namespace ocudu
