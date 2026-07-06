// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/zmq/radio_zmq_rx_channel.h  (89 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "radio_zmq_rx_channel_fsm.h"
#include "ocudu/adt/blocking_queue.h"
#include "ocudu/adt/complex.h"
#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/radio/radio_event_notifier.h"
#include "ocudu/support/executors/task_executor.h"
#include "ocudu/support/synchronization/stop_event.h"
#include <zmq.h>


namespace ocudu {

/// Radio receive channel over ZeroMQ socket.

/// Radio receive channel over ZeroMQ socket.
class radio_zmq_rx_channel
{
  /// Indicates the stream identifier. Used for notifying events.
  /// Indicates the stream identifier. Used for notifying events.
  unsigned stream_id;
  /// Channel identifier. Used for notifying events.
  /// Channel identifier. Used for notifying events.
  unsigned channel_id;
  /// Indicates the current state of the stream.
  /// Indicates the current state of the stream.
  radio_zmq_rx_channel_fsm state_fsm;
  /// Stop control.
  /// Stop control.
  rt_stop_event_source stop_control;
  /// ZMQ socket.
  /// ZMQ socket.
  void* sock = nullptr;
  /// ZMQ socket type.
  /// ZMQ socket type.
  int socket_type;
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
  /// Stores transmit buffer.
  /// Stores transmit buffer.
  blocking_queue<cf_t> circular_buffer;
  /// Transmission buffer.
  /// Transmission buffer.
  std::vector<cf_t> buffer;
  /// Notification handler.
  /// Notification handler.
  radio_event_notifier& notification_handler;
  /// Asynchronous task executor.
  /// Asynchronous task executor.
  task_executor& async_executor;


public:
  /// Describes the necessary parameters to create a ZMQ Tx channel.
  /// Describes the necessary parameters to create a ZMQ Tx channel.
  struct channel_description {
    /// Indicates the socket type.
    /// Indicates the socket type.
    int socket_type;
    /// Indicates the address to bind.
    /// Indicates the address to bind.
    std::string address;
    /// Stream identifier.
    /// Stream identifier.
    unsigned stream_id;
    /// Channel identifier.
    /// Channel identifier.
    unsigned channel_id;
    /// Stream identifier string.
    /// Stream identifier string.
    std::string channel_id_str;
    /// Logging level.
    /// Logging level.
    ocudulog::basic_levels log_level;
    /// Indicates the socket send and receive timeout in milliseconds. It is ignored if it is zero.
    /// Indicates the socket send and receive timeout in milliseconds. It is ignored if it is zero.
    unsigned trx_timeout_ms;
    /// Indicates the socket linger timeout in milliseconds. If is ignored if trx_timeout_ms is zero.
    /// Indicates the socket linger timeout in milliseconds. If is ignored if trx_timeout_ms is zero.
    unsigned linger_timeout_ms;
    /// Buffer size.
    /// Buffer size.
    unsigned buffer_size;
  };


  radio_zmq_rx_channel(void*                      zmq_context,
                       const channel_description& config,
                       radio_event_notifier&      notification_handler,
                       task_executor&             async_executor_);


  ~radio_zmq_rx_channel();


  bool is_successful() const { return state_fsm.is_running(); }


  void start();


  void stop();


  void receive(span<cf_t> buffer);


private:
  void send_request();


  void receive_response();


  void run_async();
};


} // namespace ocudu
