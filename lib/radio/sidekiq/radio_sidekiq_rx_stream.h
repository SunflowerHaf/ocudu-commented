// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/sidekiq/radio_sidekiq_rx_stream.h  (106 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "rx_alignment_buffer.h"
#include "ocudu/gateways/baseband/baseband_gateway_receiver.h"
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_writer.h"
#include "ocudu/radio/radio_configuration.h"
#include "ocudu/radio/radio_event_notifier.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/units.h"
#include <sidekiq_api.h>


namespace ocudu {

/// Implements a gateway receiver based on a sidekiq receive stream.

/// Implements a gateway receiver based on a sidekiq receive stream.
class radio_sidekiq_rx_stream : public baseband_gateway_receiver
{
public:
  /// Describes the necessary parameters to create a sidekiq Rx stream.
  /// Describes the necessary parameters to create a sidekiq Rx stream.
  struct stream_description {
    /// Sidekiq card identifyer.
    /// Sidekiq card identifyer.
    unsigned card_id;
    /// Sidekiq stream mode.
    /// Sidekiq stream mode.
    skiq_rx_stream_mode_t stream_mode;
    /// Configured Rx ports inside the given card.
    /// Configured Rx ports inside the given card.
    std::vector<skiq_rx_hdl_t> rx_port_handles;
    /// Packed mode flag.
    /// Packed mode flag.
    bool packed_mode;
  };

  /// \brief Constructs a sidekiq receive stream.
  ///
  /// \param[in] description Stream configuration parameters.
  /// \param[in] notifier_   Radio notifier.

  /// \brief Constructs a sidekiq receive stream.
  ///
  /// \param[in] description Stream configuration parameters.
  /// \param[in] notifier_   Radio notifier.
  radio_sidekiq_rx_stream(const stream_description& description, radio_event_notifier& notifier_);

  /// Gets the optimal receiver buffer size.

  /// Gets the optimal receiver buffer size.
  unsigned get_buffer_size() const;

  /// \brief Starts the receive stream at the time indicated by \c init_time.
  ///
  /// \param[in] init_time Sidekiq system timestamp value at which the receive stream should start.

  /// \brief Starts the receive stream at the time indicated by \c init_time.
  ///
  /// \param[in] init_time Sidekiq system timestamp value at which the receive stream should start.
  void start(baseband_gateway_timestamp init_time);

  /// Stop the transmission.

  /// Stop the transmission.
  void stop();

  /// Wait until the receive stream has stopped.

  /// Wait until the receive stream has stopped.
  void wait_stop();

  /// Checks if the stream is successfully initialized.

  /// Checks if the stream is successfully initialized.
  bool init_successful();

  // See interface for documentation.

  // See interface for documentation.
  metadata receive(baseband_gateway_buffer_writer& data) override;


private:
  /// Rx stream states.
  /// Rx stream states.
  enum class rx_states : unsigned {
    /// The stream is not initialized.
    /// The stream is not initialized.
    UNINITIALIZED,
    /// The stream has been initialized and is ready to start receiving samples.
    /// The stream has been initialized and is ready to start receiving samples.
    SUCCESSFUL_INIT,
    /// Samples are being streamed from the radio.
    /// Samples are being streamed from the radio.
    STREAMING,
    /// The stream has been requested to stop and is waiting for unfinished receive operations to complete.
    /// The stream has been requested to stop and is waiting for unfinished receive operations to complete.
    WAIT_STOP,
    /// Reception has stopped.
    /// Reception has stopped.
    STOPPED
  };

  /// \brief Handles reception of a single Rx block.
  ///
  /// \param[out] rx_block Sidekiq receive block with the received samples, if the receive operation was successful.
  /// \param[out] rx_port_handle Port handle of the received samples.
  /// \return \c true if the receive operation was successful, \c false otherwise.
  /// \warning The contents of \c rx_block are not valid and must be ignored is this function returns \c false.

  /// \brief Handles reception of a single Rx block.
  ///
  /// \param[out] rx_block Sidekiq receive block with the received samples, if the receive operation was successful.
  /// \param[out] rx_port_handle Port handle of the received samples.
  /// \return \c true if the receive operation was successful, \c false otherwise.
  /// \warning The contents of \c rx_block are not valid and must be ignored is this function returns \c false.
  bool receive_block(skiq_rx_block_t** rx_block, skiq_rx_hdl_t* rx_port_handle);

  /// Handles RX overflow events.

  /// Handles RX overflow events.
  void handle_rx_overflow() const;

  /// Handles the transition into the stopped state once reception has stopped.

  /// Handles the transition into the stopped state once reception has stopped.
  void on_stream_stop();

  /// Current stream state.

  /// Current stream state.
  std::atomic<rx_states> state = {rx_states::UNINITIALIZED};
  /// Radio notification interface.
  /// Radio notification interface.
  radio_event_notifier& notifier;
  /// Identifies the card of the Rx port.
  /// Identifies the card of the Rx port.
  unsigned card_id;
  /// Configured Rx ports inside the given card.
  /// Configured Rx ports inside the given card.
  std::vector<skiq_rx_hdl_t> rx_port_handles;
  /// Number of samples in a sidekiq receive block.
  /// Number of samples in a sidekiq receive block.
  unsigned nof_samples_block;
  /// Number of 32-bit data words in a sidekiq receive block.
  /// Number of 32-bit data words in a sidekiq receive block.
  unsigned nof_data_words_block;
  /// Buffer used to align samples into chunks of \c nof_samples_block.
  /// Buffer used to align samples into chunks of \c nof_samples_block.
  detail::rx_alignment_buffer alignment_buffer;
  /// Packed mode flag.
  /// Packed mode flag.
  bool packed_mode;
};


} // namespace ocudu
