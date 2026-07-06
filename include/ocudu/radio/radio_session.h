// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/radio/radio_session.h  (50 lines)
//
// INTERFACE HEADER — include/ocudu/radio
// Radio hardware interface headers: radio_session (the top-level radio session — controls the USRP), radio_management_plane (start/stop/config), radio_data_plane_rx_notifier and tx_streamer (the IQ sample streaming interfaces), and the radio_notification_handler for overflow/underflow events.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/gateways/baseband/baseband_gateway.h"
#include "ocudu/gateways/baseband/baseband_gateway_timestamp.h"
#include "ocudu/radio/radio_configuration.h"
#include "ocudu/radio/radio_event_notifier.h"
#include "ocudu/radio/radio_management_plane.h"


namespace ocudu {

/// Describes a radio baseband unit session interface.

/// Describes a radio baseband unit session interface.
class radio_session : public radio_base
{
public:
  /// \brief Gets the management plane.
  /// \return The reference to the management plane for this radio session.
  /// \brief Gets the management plane.
  /// \return The reference to the management plane for this radio session.
  virtual radio_management_plane& get_management_plane() = 0;

  /// \brief Gets the data plane.
  /// \param[in] stream_id Stream identifier.
  /// \return The reference to the data plane for this radio session.
  /// \remark An assertion is triggered if the stream identifier is invalid.

  /// \brief Gets the data plane.
  /// \param[in] stream_id Stream identifier.
  /// \return The reference to the data plane for this radio session.
  /// \remark An assertion is triggered if the stream identifier is invalid.
  virtual baseband_gateway& get_baseband_gateway(unsigned stream_id) = 0;

  /// \brief Gets the current time.

  /// \brief Gets the current time.
  virtual baseband_gateway_timestamp read_current_time() = 0;

  /// \brief Starts the radio operation.
  ///
  /// It requests all radio streams to start simultaneously.
  ///
  /// \param[in] init_time Initial time in which streaming shall start.
  /// \remark Radio streams run until halted by a call of the stop() method.
  /// \remark Calling start() more than once results in undefined behavior, even after calling stop().

  /// \brief Starts the radio operation.
  ///
  /// It requests all radio streams to start simultaneously.
  ///
  /// \param[in] init_time Initial time in which streaming shall start.
  /// \remark Radio streams run until halted by a call of the stop() method.
  /// \remark Calling start() more than once results in undefined behavior, even after calling stop().
  virtual void start(baseband_gateway_timestamp init_time) = 0;

  /// \brief Stops the radio session operation.
  ///
  /// Any call to radio operation after calling stop() will return instantly without interacting with the physical
  /// radio.
  ///
  /// \remark Calling stop() without having called start() results in undefined behavior.
  /// \remark Calling start() after stop() results in undefined behavior.

  /// \brief Stops the radio session operation.
  ///
  /// Any call to radio operation after calling stop() will return instantly without interacting with the physical
  /// radio.
  ///
  /// \remark Calling stop() without having called start() results in undefined behavior.
  /// \remark Calling start() after stop() results in undefined behavior.
  virtual void stop() = 0;
};


} // namespace ocudu
