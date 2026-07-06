// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_tx_stream.h
 * @brief UHD transmit stream — sends IQ samples to the USRP for over-the-air transmission.
 *
 * radio_uhd_tx_stream implements baseband_gateway_transmitter (the generic
 * interface the lower PHY uses to send samples) using UHD's tx_streamer API.
 * Beyond simple sample transmission, this class handles two non-trivial
 * pieces of behaviour:
 *
 *   1. Burst management via radio_uhd_tx_stream_fsm — tracking when to send
 *      start/end-of-burst flags, especially important in discontinuous Tx mode.
 *
 *   2. Power ramping — in discontinuous Tx mode, the RF amplifier needs time
 *      to reach full power after being switched on. This class can prepend
 *      a configurable amount of zero-valued "padding" samples before the
 *      real data, giving the amplifier time to ramp up before the actual
 *      signal begins (avoiding distortion on the leading edge of each burst).
 *
 * It also runs a background task (run_recv_async_msg) that continuously
 * polls UHD for asynchronous Tx event messages (burst ACKs, late, underflow)
 * and forwards them through the radio_event_notifier.
 */

#pragma once


#include "radio_uhd_exception_handler.h"
#include "radio_uhd_multi_usrp.h"
#include "radio_uhd_tx_stream_fsm.h"
#include "ocudu/gateways/baseband/baseband_gateway_transmitter.h" ///< Base interface this class implements
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_dynamic.h"
#include "ocudu/gateways/baseband/buffer/baseband_gateway_buffer_reader.h"
#include "ocudu/radio/radio_configuration.h"
#include "ocudu/radio/radio_event_notifier.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/synchronization/stop_event.h"


namespace ocudu {

/// Implements a gateway transmitter based on UHD transmit stream.

/**
 * @brief UHD-backed implementation of the transmit side of the baseband gateway.
 */
class radio_uhd_tx_stream : public baseband_gateway_transmitter, public uhd_exception_handler
{
  /// Indicates the stream identification for notifications.
  /// Stream identifier, included in event notifications so the recipient
  /// knows which sector/stream an event refers to.
  unsigned stream_id;
  /// Task executor for asynchronous messages.
  /// Thread executor used to repeatedly poll for asynchronous UHD Tx event messages.
  task_executor& async_executor;
  /// Radio notification interface.
  /// Receives radio event notifications (start/end of burst, late, underflow).
  radio_event_notifier& notifier;
  /// Owns the UHD Tx stream.
  /// The UHD transmit stream object.
  uhd::tx_streamer::sptr stream;
  /// Maximum number of samples in a single packet.
  /// Maximum number of samples UHD will accept in a single send() call.
  unsigned max_packet_size;
  /// Sampling rate in Hz.
  /// Sample rate in Hz, used to convert between sample counts and UHD time specs.
  double srate_hz;
  /// Indicates the number of channels.
  /// Number of antenna channels in this stream.
  unsigned nof_channels;
  /// Indicates the current internal state.
  /// Tracks the burst lifecycle (start/end-of-burst signalling).
  radio_uhd_tx_stream_fsm state_fsm;
  /// Discontinuous transmission mode flag.
  /// Whether discontinuous transmission mode is enabled for this stream.
  bool discontinuous_tx;
  /// Number of samples to advance the burst start to protect against power ramping effects.
  /// Number of zero-padding samples to prepend before each burst, to absorb
  /// power amplifier ramp-up time when discontinuous Tx is enabled.
  unsigned power_ramping_nof_samples;
  /// Stores the time of the last transmitted sample.
  /// Timestamp of the end of the previous transmission, used to compute the
  /// gap available for power ramping padding before the next burst.
  uhd::time_spec_t last_tx_timespec;
  /// Power ramping transmit buffer. It is filled with zeros, used to absorb power ramping when starting a transmission.
  /// Pre-allocated, zero-filled buffer used for power ramping padding samples.
  baseband_gateway_buffer_dynamic power_ramping_buffer;
  /// Stop control.
  /// Coordinates a clean stop of the background async message polling task.
  rt_stop_event_source stop_control;

  /// Receive asynchronous message.

  /// Polls UHD once for a pending asynchronous Tx event message and dispatches it.
  void recv_async_msg();

  /// Runs the asynchronous message reception through the asynchronous task executor.

  /// Re-enqueues itself on the async executor after each poll, forming a continuous loop.
  void run_recv_async_msg();

  /// \brief Transmits a single baseband block.
  /// \param[out] nof_txd_samples Number of transmitted samples.
  /// \param[in] data             Buffer to transmit.
  /// \param[in] offset           Sample offset in the transmit buffers.
  /// \param[in] md               Transmission metadata.
  /// \return True if no exception is caught in the transmission process, false otherwise.

  /**
   * @brief Transmits a single block of samples to UHD (a single send() call).
   *
   * @param nof_txd_samples  Output: number of samples actually transmitted by this call.
   * @param data             The sample buffer to transmit from.
   * @param offset           Sample offset within data to start transmitting from.
   * @param md               UHD transmit metadata (burst flags, timestamp).
   * @return true if no exception was caught during the call.
   */
  bool transmit_block(unsigned&                             nof_txd_samples,
                      const baseband_gateway_buffer_reader& data,
                      unsigned                              offset,
                      const uhd::tx_metadata_t&             md);


public:
  /// Describes the necessary parameters to create an UHD transmit stream.
  /**
   * @brief Configuration needed to create a UHD transmit stream.
   */
  struct stream_description {
    /// Identifies the stream.
    /// Identifies this stream for event notifications.
    unsigned id;
    /// Over-the-wire format.
    /// Over-the-wire sample format ("sc16", "sc12", "sc8").
    radio_configuration::over_the_wire_format otw_format;
    /// Sampling rate in Hz.
    /// Sample rate in Hz (the actual rate UHD configured, not necessarily the requested rate).
    double srate_hz;
    /// Stream arguments.
    /// Additional UHD stream arguments.
    std::string args;
    /// Indicates the port indexes for the stream.
    /// The UHD channel indexes (ports) belonging to this stream.
    std::vector<size_t> ports;
    /// Enables discontinuous transmission mode.
    /// If true, transmissions are sent as discrete bursts with power ramping
    /// padding rather than as one continuous stream.
    bool discontiuous_tx;
    /// Time by which to advance the burst start, using zero padding to protect against power ramping.
    /// Time in microseconds to advance each burst's start, using zero
    /// padding, to protect against power ramping distortion.
    float power_ramping_us;
  };

  /// \brief Constructs an UHD transmit stream.
  /// \param[in] usrp Provides the USRP context.
  /// \param[in] description Provides the stream configuration parameters.
  /// \param[in] async_executor_ Provides the asynchronous task executor.
  /// \param[in] notifier_ Provides the radio event notification handler.

  /**
   * @brief Constructs and opens a UHD transmit stream.
   *
   * @param usrp            The USRP context (shared_ptr to UHD's multi_usrp).
   * @param description     Stream configuration parameters.
   * @param async_executor_ Thread executor for polling asynchronous Tx messages.
   * @param notifier_       Receives radio event notifications.
   */
  radio_uhd_tx_stream(uhd::usrp::multi_usrp::sptr& usrp,
                      const stream_description&    description,
                      task_executor&               async_executor_,
                      radio_event_notifier&        notifier_);

  /// Gets the optimal transmitter buffer size.

  /// Returns the optimal (maximum) buffer size for transmit calls.
  unsigned get_buffer_size() const { return max_packet_size; }

  // See interface for documentation.

  /**
   * @brief Transmits a block of IQ samples, handling burst management and power ramping.
   *
   * @param data      The samples to transmit, one buffer per antenna channel.
   * @param metadata  Transmission metadata: timestamp and optional partial-block markers.
   */
  void transmit(const baseband_gateway_buffer_reader&        data,
                const baseband_gateway_transmitter_metadata& metadata) override;

  /// Start the transmission.

  /// Starts the background asynchronous Tx event polling task.
  void start();

  /// Stop the transmission.

  /// Stops the stream, sending an end-of-burst if currently mid-burst.
  void stop();
};


} // namespace ocudu
