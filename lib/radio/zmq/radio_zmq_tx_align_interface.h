// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/radio/zmq/radio_zmq_tx_align_interface.h  (22 lines)
//
// DIRECTORY: lib/radio
// Radio hardware driver layer. lib/radio/uhd/ implements the UHD (USRP Hardware Driver) backend: opens the USRP device, sets sample rate/centre frequency/gain, streams IQ samples to/from the hardware. lib/radio/ shared contains the radio factory (selects the UHD backend at runtime) and the radio_notification_handler base.
//
// =============================================================================

#pragma once


#include "ocudu/gateways/baseband/baseband_gateway_timestamp.h"
#include <chrono>


namespace ocudu {

/// Interface for transmitter alignment from the receiver.

/// Interface for transmitter alignment from the receiver.
class radio_zmq_tx_align_interface
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~radio_zmq_tx_align_interface() = default;

  /// Aligns a transmit stream by transmitting zeros until the indicated timestamp.

  /// Aligns a transmit stream by transmitting zeros until the indicated timestamp.
  virtual bool align(baseband_gateway_timestamp timestamp, std::chrono::milliseconds timeout) = 0;
};


} // namespace ocudu
