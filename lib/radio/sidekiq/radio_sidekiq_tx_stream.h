// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/sidekiq/radio_sidekiq_tx_stream.h  (101 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "tx_alignment_buffer.h"
#include "ocudu/gateways/baseband/baseband_gateway_transmitter.h"
#include "ocudu/radio/radio_configuration.h"
#include "ocudu/radio/radio_event_notifier.h"
#include <sidekiq_api.h>


namespace ocudu {

/// Implements a gateway transmitter based on a sidekiq transmit stream.

/// Implements a gateway transmitter based on a sidekiq transmit stream.
class radio_sidekiq_tx_stream : public baseband_gateway_transmitter
{
public:
  /// Describes the necessary parameters to create a sidekiq transmit stream.
  /// Describes the necessary parameters to create a sidekiq transmit stream.
  struct stream_description {
    /// Sidekiq card identifier.
    /// Sidekiq card identifier.
    unsigned card_id;
    /// Sidekiq RX stream mode, used to determine the TX block size.
    /// Sidekiq RX stream mode, used to determine the TX block size.
    skiq_rx_stream_mode_t stream_mode;
    /// Sidekiq channel mode.
    /// Sidekiq channel mode.
    skiq_chan_mode_t channel_mode;
    /// Transmission ports inside the given card required for streaming.
    /// Transmission ports inside the given card required for streaming.
    std::vector<skiq_tx_hdl_t> tx_port_handles;
    /// Packed mode flag.
    /// Packed mode flag.
    bool packed_mode;
  };

  /// \brief Constructs a Sidekiq transmit stream.

  /// \brief Constructs a Sidekiq transmit stream.
  radio_sidekiq_tx_stream(const stream_description& description, radio_event_notifier& notifier_);

  /// Gets the optimal transmitter buffer size.

  /// Gets the optimal transmitter buffer size.
  unsigned get_buffer_size() const;

  // See interface for documentation.

  // See interface for documentation.
  void transmit(const baseband_gateway_buffer_reader&        data,
                const baseband_gateway_transmitter_metadata& metadata) override;

  /// Stop the transmission.

  /// Stop the transmission.
  void stop();

  /// Wait until radio is notify_stop.

  /// Wait until radio is notify_stop.
  void wait_stop();

  /// Checks if the stream is successfully initialized.

  /// Checks if the stream is successfully initialized.
  bool init_successful();


private:
  /// Transmit stream states.
  /// Transmit stream states.
  enum class tx_states : unsigned { UNINITIALIZED, SUCCESSFUL_INIT, IN_BURST, WAIT_STOP, STOPPED };

  /// \brief Transmits a single radio block.
  ///
  /// This method attempts to enqueue the transmission of a Sidekiq sample block from the contents of a baseband buffer
  /// at the given timestamp.
  ///
  /// \param[in] data Baseband buffer containing the samples to transmit.
  /// \param[in] timestamp RF timestamp of the first sample to transmit.
  /// \remark An assertion will be triggered if the number of ports and samples in \c data does not match the transmit
  ///         block size.

  /// \brief Transmits a single radio block.
  ///
  /// This method attempts to enqueue the transmission of a Sidekiq sample block from the contents of a baseband buffer
  /// at the given timestamp.
  ///
  /// \param[in] data Baseband buffer containing the samples to transmit.
  /// \param[in] timestamp RF timestamp of the first sample to transmit.
  /// \remark An assertion will be triggered if the number of ports and samples in \c data does not match the transmit
  ///         block size.
  void transmit_block(const baseband_gateway_buffer_reader& data, baseband_gateway_timestamp timestamp);

  /// Handles the transition to the stopped state once the TX stream has stopped.

  /// Handles the transition to the stopped state once the TX stream has stopped.
  void on_stream_stop();

  /// Detects and handles transmit late events.

  /// Detects and handles transmit late events.
  void detect_handle_lates();

  /// Transmission state.

  /// Transmission state.
  std::atomic<tx_states> state = {tx_states::UNINITIALIZED};
  /// Radio notification interface.
  /// Radio notification interface.
  radio_event_notifier& notifier;
  /// Card identifier.
  /// Card identifier.
  unsigned card_id;
  /// Transmission ports inside the given card that are configured for streaming.
  /// Transmission ports inside the given card that are configured for streaming.
  std::vector<skiq_tx_hdl_t> tx_port_handles;
  /// Sidekiq channel mode.
  /// Sidekiq channel mode.
  skiq_chan_mode_t channel_mode;
  /// Number of samples per port in a sidekiq transmit block.
  /// Number of samples per port in a sidekiq transmit block.
  unsigned nof_port_samples_block;
  /// Number of data words per port in a sidekiq transmit block.
  /// Number of data words per port in a sidekiq transmit block.
  unsigned nof_port_data_words_block;
  /// Sidekiq transmission block.
  /// Sidekiq transmission block.
  skiq_tx_block_t* tx_block;
  /// Buffer used to align samples into chunks of \c nof_samples_block.
  /// Buffer used to align samples into chunks of \c nof_samples_block.
  detail::tx_alignment_buffer alignment_buffer;
  /// \brief RF lates check period in number of RF blocks.
  /// \remark A low period may cause a reduction of performance in the Host-FPGA communication.
  /// \brief RF lates check period in number of RF blocks.
  /// \remark A low period may cause a reduction of performance in the Host-FPGA communication.
  static constexpr baseband_gateway_timestamp tx_late_check_period = 1000;
  /// Last timestamp at which lates were checked.
  /// Last timestamp at which lates were checked.
  baseband_gateway_timestamp last_late_check_ts;
  /// Counter for the total number of RF lates.
  /// Counter for the total number of RF lates.
  std::array<uint32_t, RADIO_MAX_NOF_CHANNELS> total_nof_lates;
  /// Packed mode flag.
  /// Packed mode flag.
  bool packed_mode;
};


} // namespace ocudu
