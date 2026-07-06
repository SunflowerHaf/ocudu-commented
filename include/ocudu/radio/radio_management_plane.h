// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/radio/radio_management_plane.h  (41 lines)
//
// INTERFACE HEADER — include/ocudu/radio
// Radio hardware interface headers: radio_session (the top-level radio session — controls the USRP), radio_management_plane (start/stop/config), radio_data_plane_rx_notifier and tx_streamer (the IQ sample streaming interfaces), and the radio_notification_handler for overflow/underflow events.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/radio/radio_base.h"


namespace ocudu {

/// Defines a radio baseband unit management plane interface.

/// Defines a radio baseband unit management plane interface.
class radio_management_plane : public radio_base
{
public:
  /// \brief Set the transmission gain of a given port in runtime.
  /// \param[in] port_id Indicates the port identifier.
  /// \param[in] gain_dB Indicates the new gain.
  /// \return True if the operation is successful. Otherwise, false.
  /// \note The port identifier is indexed from stream ascending order and then port.
  /// \brief Set the transmission gain of a given port in runtime.
  /// \param[in] port_id Indicates the port identifier.
  /// \param[in] gain_dB Indicates the new gain.
  /// \return True if the operation is successful. Otherwise, false.
  /// \note The port identifier is indexed from stream ascending order and then port.
  virtual bool set_tx_gain(unsigned port_id, double gain_dB) = 0;

  /// \brief Set the reception gain of a given port in runtime.
  /// \param[in] port_id Indicates the port identifier.
  /// \param[in] gain_dB Indicates the new gain.
  /// \return True if the operation is successful. Otherwise, false.
  /// \note The port identifier is indexed from stream ascending order and then port.

  /// \brief Set the reception gain of a given port in runtime.
  /// \param[in] port_id Indicates the port identifier.
  /// \param[in] gain_dB Indicates the new gain.
  /// \return True if the operation is successful. Otherwise, false.
  /// \note The port identifier is indexed from stream ascending order and then port.
  virtual bool set_rx_gain(unsigned port_id, double gain_dB) = 0;

  /// \brief Set the transmission center frequency of all ports related to a stream.
  /// \param[in] stream_id      Radio stream identifier.
  /// \param[in] center_freq_Hz New center frequency in Hertz.
  /// \return True if the operation is successful. Otherwise, false.

  /// \brief Set the transmission center frequency of all ports related to a stream.
  /// \param[in] stream_id      Radio stream identifier.
  /// \param[in] center_freq_Hz New center frequency in Hertz.
  /// \return True if the operation is successful. Otherwise, false.
  virtual bool set_tx_freq(unsigned stream_id, double center_freq_Hz) = 0;

  /// \brief Set the reception center frequency of all ports related to a stream.
  /// \param[in] stream_id      Radio stream identifier.
  /// \param[in] center_freq_Hz New center frequency in Hertz.
  /// \return True if the operation is successful. Otherwise, false.

  /// \brief Set the reception center frequency of all ports related to a stream.
  /// \param[in] stream_id      Radio stream identifier.
  /// \param[in] center_freq_Hz New center frequency in Hertz.
  /// \return True if the operation is successful. Otherwise, false.
  virtual bool set_rx_freq(unsigned stream_id, double center_freq_Hz) = 0;
};


} // namespace ocudu
