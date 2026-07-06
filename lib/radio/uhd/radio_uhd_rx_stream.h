// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_rx_stream.h
 * @brief UHD receive stream — captures IQ samples from the USRP for uplink processing.
 *
 * radio_uhd_rx_stream implements baseband_gateway_receiver (the generic
 * interface the lower PHY uses to read incoming samples) using UHD's
 * rx_streamer API. Compared to the Tx stream, the Rx side is simpler — there
 * is no burst management needed since reception is continuous once started.
 *
 * The main complexity here is multi-packet assembly: UHD delivers samples
 * in fixed-size packets (max_packet_size), so when the caller requests a
 * larger buffer's worth of samples, this class issues multiple recv() calls
 * in a loop until the buffer is fully populated, while monitoring for and
 * reporting any error conditions (timeouts, late commands, overflows)
 * encountered along the way.
 */

#pragma once


#include "radio_uhd_exception_handler.h"
#include "radio_uhd_multi_usrp.h"
#include "ocudu/gateways/baseband/baseband_gateway_receiver.h" ///< Base interface this class implements
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_writer.h"
#include "ocudu/radio/radio_configuration.h"
#include "ocudu/radio/radio_event_notifier.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {

/// Implements a gateway receiver based on UHD receive stream.

/**
 * @brief UHD-backed implementation of the receive side of the baseband gateway.
 */
class radio_uhd_rx_stream : public uhd_exception_handler, public baseband_gateway_receiver
{
  /// Indicates if the initialization of the stream was successful.
  /// Whether construction completed successfully.
  bool is_init_successful = false;
  /// Indicates the stream identification for notifications.
  /// Stream identifier, included in event notifications.
  unsigned id;
  /// Sampling rate in hertz.
  /// Sample rate in Hz, used for timestamp conversions.
  double srate_Hz;
  /// Radio notification interface.
  /// Receives radio event notifications (late, overflow, other errors).
  radio_event_notifier& notifier;
  /// Owns the UHD Tx stream.
  /// The UHD receive stream object.
  uhd::rx_streamer::sptr stream;
  /// Maximum number of samples in a single packet.
  /// Maximum number of samples UHD will deliver in a single recv() call.
  unsigned max_packet_size;
  /// Indicates the number of channels.
  /// Number of antenna channels in this stream.
  unsigned nof_channels;
  /// Stop control.
  /// Coordinates a clean stop of in-progress receive operations.
  rt_stop_event_source stop_control;

  /// \brief Receives a single block of baseband samples.
  /// \param[out] nof_rxd_samples Indicate the number of samples received in the block.
  /// \param[in,out] buffs Provides the reception buffers.
  /// \param[in] buffer_offset Indicates the data offset in the reception buffers.
  /// \param[in] metadata Provides the reception metadata.
  /// \return True if no exception is caught. Otherwise false.

  /**
   * @brief Receives a single block of samples from UHD (a single recv() call).
   *
   * @param nof_rxd_samples  Output: number of samples actually received.
   * @param buffs            Destination buffer to write received samples into.
   * @param buffer_offset    Sample offset within buffs to start writing at.
   * @param metadata         Output: UHD receive metadata (timestamp, error code).
   * @return true if no exception was caught.
   */
  bool receive_block(unsigned&                       nof_rxd_samples,
                     baseband_gateway_buffer_writer& buffs,
                     unsigned                        buffer_offset,
                     uhd::rx_metadata_t&             metadata);


public:
  /// Describes the necessary parameters to create an UHD transmit stream.
  /**
   * @brief Configuration needed to create a UHD receive stream.
   */
  struct stream_description {
    /// Identifies the stream.
    /// Identifies this stream for event notifications.
    unsigned id;
    /// Sampling rate in hertz.
    /// Sample rate in Hz.
    double srate_Hz;
    /// Over-the-wire format.
    /// Over-the-wire sample format.
    radio_configuration::over_the_wire_format otw_format;
    /// Stream arguments.
    /// Additional UHD stream arguments.
    std::string args;
    /// Indicates the port indexes for the stream.
    /// The UHD channel indexes (ports) belonging to this stream.
    std::vector<size_t> ports;
  };

  /// \brief Constructs a receive UHD stream.
  /// \param[in] usrp Provides the USRP context.
  /// \param[in] description Provides the stream configuration parameters.
  /// \param[in] notifier_ Provides the radio event notification handler.

  /**
   * @brief Constructs and opens a UHD receive stream.
   *
   * @param usrp        The USRP context.
   * @param description Stream configuration parameters.
   * @param notifier_   Receives radio event notifications.
   */
  radio_uhd_rx_stream(uhd::usrp::multi_usrp::sptr& usrp,
                      const stream_description&    description,
                      radio_event_notifier&        notifier_);

  /// \brief Starts the stream reception.
  /// \param[in] time_spec Indicates the start time of the stream.
  /// \return True if no exception is caught. Otherwise false.

  /**
   * @brief Issues the stream-start command to UHD at the given absolute time.
   *
   * @param time_spec  The UHD timestamp at which streaming should begin.
   *                   If this equals the zero time spec, streaming starts
   *                   immediately rather than at a scheduled future time.
   * @return true if no exception was caught.
   */
  bool start(const uhd::time_spec_t& time_spec);

  /// \brief Stops the reception stream.
  /// \return True if no exception is caught. Otherwise false.

  /**
   * @brief Stops the receive stream.
   * @return true if no exception was caught.
   */
  bool stop();

  /// Gets the optimal transmitter buffer size.

  /// Returns the optimal (maximum) buffer size for receive calls.
  unsigned get_buffer_size() const { return max_packet_size; }

  // See interface for documentation.

  /**
   * @brief Fills the given buffer with received IQ samples, issuing multiple
   *        UHD recv() calls as needed.
   *
   * @param data  Destination buffer to populate (one sub-buffer per channel).
   * @return Metadata including the timestamp of the first received sample.
   */
  metadata receive(baseband_gateway_buffer_writer& data) override;
};


} // namespace ocudu
