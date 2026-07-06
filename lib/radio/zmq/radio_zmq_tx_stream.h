// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/zmq/radio_zmq_tx_stream.h  (72 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "radio_zmq_tx_align_interface.h"
#include "radio_zmq_tx_channel.h"
#include "ocudu/gateways/baseband/baseband_gateway_timestamp.h"
#include "ocudu/gateways/baseband/baseband_gateway_transmitter.h"
#include "ocudu/radio/radio_constants.h"
#include <array>
#include <memory>


namespace ocudu {

/// Implements a gateway receiver based on ZMQ transmit socket.

/// Implements a gateway receiver based on ZMQ transmit socket.
class radio_zmq_tx_stream : public baseband_gateway_transmitter, public radio_zmq_tx_align_interface
{
  /// Radio notification handler interface.
  /// Radio notification handler interface.
  radio_event_notifier& notification_handler;
  /// Indicates whether the class was initialized successfully.
  /// Indicates whether the class was initialized successfully.
  bool successful = false;
  /// Stores independent channels.
  /// Stores independent channels.
  std::vector<std::unique_ptr<radio_zmq_tx_channel>> channels;
  /// Buffer to hold complex floating-point based samples.
  /// Buffer to hold complex floating-point based samples.
  std::vector<cf_t> cf_buffer;
  /// Per-channel linear amplitude gains. Atomic for lock-free concurrent set/read.
  /// Per-channel linear amplitude gains. Atomic for lock-free concurrent set/read.
  std::array<std::atomic<float>, RADIO_MAX_NOF_CHANNELS> channel_gains;


public:
  /// Describes the necessary parameters to create a ZMQ Tx stream.
  /// Describes the necessary parameters to create a ZMQ Tx stream.
  struct stream_description {
    /// Indicates the socket type.
    /// Indicates the socket type.
    int socket_type;
    /// Indicates the addresses to bind. The number of elements indicate the number of channels.
    /// Indicates the addresses to bind. The number of elements indicate the number of channels.
    std::vector<std::string> address;
    /// Stream identifier.
    /// Stream identifier.
    unsigned stream_id;
    /// Stream identifier string.
    /// Stream identifier string.
    std::string stream_id_str;
    /// Logging level.
    /// Logging level.
    ocudulog::basic_levels log_level;
    /// Indicates the socket send and receive timeout in milliseconds. It is ignored if it is zero.
    /// Indicates the socket send and receive timeout in milliseconds. It is ignored if it is zero.
    unsigned trx_timeout_ms;
    /// Indicates the socket linger timeout in milliseconds. If is ignored if trx_timeout_ms is zero.
    /// Indicates the socket linger timeout in milliseconds. If is ignored if trx_timeout_ms is zero.
    unsigned linger_timeout_ms;
    /// Indicates the channel buffer size.
    /// Indicates the channel buffer size.
    unsigned buffer_size;
  };


  radio_zmq_tx_stream(void*                     zmq_context,
                      const stream_description& config,
                      task_executor&            async_executor_,
                      radio_event_notifier&     notification_handler);


  bool is_successful() const { return successful; }

  // See interface for documentation.

  // See interface for documentation.
  bool align(baseband_gateway_timestamp timestamp, std::chrono::milliseconds timeout) override;

  // See interface for documentation.

  // See interface for documentation.
  void transmit(const baseband_gateway_buffer_reader& data, const baseband_gateway_transmitter_metadata& md) override;


  void start(baseband_gateway_timestamp init_time);


  void stop();

  /// Sets the linear amplitude gain for a specific channel.

  /// Sets the linear amplitude gain for a specific channel.
  void set_channel_gain(unsigned channel_id, float gain_linear);
};


} // namespace ocudu
