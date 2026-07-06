// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/**
 * @file radio_uhd_baseband_gateway.h
 * @brief The UHD implementation of the baseband_gateway interface.
 *
 * baseband_gateway is the standard interface the lower PHY uses to send and
 * receive IQ samples, regardless of which radio backend is in use (UHD, ZMQ,
 * etc.). This class is the UHD-specific implementation — it owns one Tx
 * stream and one Rx stream (each handling potentially multiple antenna
 * channels) and exposes them through the generic interface.
 *
 * One radio_uhd_baseband_gateway is created per cell sector (see
 * radio_session_uhd_impl construction in radio_uhd_impl.cpp), since each
 * cell needs its own independent Tx/Rx stream pair to/from the USRP.
 */

#pragma once


#include "radio_uhd_device.h"
#include "radio_uhd_rx_stream.h"
#include "radio_uhd_tx_stream.h"
#include "ocudu/gateways/baseband/baseband_gateway.h" ///< Base interface this class implements
#include <memory>


namespace ocudu {

/// \brief Implement baseband gateway interface for UHD.
///
/// It contains a transmit stream and a receive stream.

/**
 * @brief UHD-backed implementation of the baseband_gateway interface.
 *
 * Owns a transmit stream and a receive stream, both created from the shared
 * UHD device connection.
 */
class radio_uhd_baseband_gateway : public baseband_gateway
{
public:
  /**
   * @param device            The shared UHD device connection (the radio_uhd_device).
   * @param async_executor    Thread executor for asynchronous Tx event messages.
   * @param notifier          Receives radio event notifications (late, underflow, overflow).
   * @param tx_stream_config  Configuration for this sector's transmit stream.
   * @param rx_stream_config  Configuration for this sector's receive stream.
   */
  radio_uhd_baseband_gateway(radio_uhd_device&                              device,
                             task_executor&                                 async_executor,
                             radio_event_notifier&                          notifier,
                             const radio_uhd_tx_stream::stream_description& tx_stream_config,
                             const radio_uhd_rx_stream::stream_description& rx_stream_config) :
    tx_stream(device.create_tx_stream(async_executor, notifier, tx_stream_config)),
    rx_stream(device.create_rx_stream(notifier, rx_stream_config))
  {
  }

  // See interface for documentation.

  /// Returns the transmitter interface (where the lower PHY writes outgoing IQ samples).
  baseband_gateway_transmitter& get_transmitter() override { return *tx_stream; }

  // See interface for documentation.

  /// Returns the receiver interface (where the lower PHY reads incoming IQ samples).
  baseband_gateway_receiver& get_receiver() override { return *rx_stream; }

  // See interface for documentation.

  /// Returns the optimal buffer size for transmit calls (the UHD stream's max packet size).
  unsigned get_transmitter_optimal_buffer_size() const override { return tx_stream->get_buffer_size(); }

  // See interface for documentation.

  /// Returns the optimal buffer size for receive calls (the UHD stream's max packet size).
  unsigned get_receiver_optimal_buffer_size() const override { return rx_stream->get_buffer_size(); }

  /// Gets the transmit stream instance.

  /// Returns a direct reference to the Tx stream (used by ru_controller_sdr_impl to start/stop it).
  radio_uhd_tx_stream& get_tx_stream() { return *tx_stream; }

  /// Gets the transmit stream.

  /// Returns a direct reference to the Rx stream.
  radio_uhd_rx_stream& get_rx_stream() { return *rx_stream; }

  /// Checks if the streams are successfully initialized.

  /**
   * @brief Checks both streams were created successfully.
   *
   * Called immediately after construction; if false, the radio session
   * construction is aborted (see radio_session_uhd_impl constructor).
   *
   * @return true if both Tx and Rx streams were created and initialised successfully.
   */
  bool is_successful() const
  {
    if (!tx_stream || !rx_stream) {
      return false;
    }


    return tx_stream->is_successful() && rx_stream->is_successful();
  }


private:
  /// Transmit stream.
  /// This sector's transmit stream.
  std::unique_ptr<radio_uhd_tx_stream> tx_stream;
  /// Receive stream.
  /// This sector's receive stream.
  std::unique_ptr<radio_uhd_rx_stream> rx_stream;
};


} // namespace ocudu
