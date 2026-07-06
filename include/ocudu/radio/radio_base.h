// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/radio/radio_base.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/radio
// Radio hardware interface headers: radio_session (the top-level radio session — controls the USRP), radio_management_plane (start/stop/config), radio_data_plane_rx_notifier and tx_streamer (the IQ sample streaming interfaces), and the radio_notification_handler for overflow/underflow events.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {

/// Describes the base interface for radio classes.

/// Describes the base interface for radio classes.
class radio_base
{
protected:
  /// Allow default constructor for child.
  /// Allow default constructor for child.
  radio_base() = default;


public:
  /// Provides default destructor.
  /// Provides default destructor.
  virtual ~radio_base() = default;

  /// Forbid copy constructor.

  /// Forbid copy constructor.
  radio_base(const radio_base& other) = delete;

  /// Forbid move constructor.

  /// Forbid move constructor.
  radio_base(radio_base&& other) = delete;

  /// Forbid copy assignment operator.

  /// Forbid copy assignment operator.
  radio_base& operator=(const radio_base&) = delete;

  /// Forbid move assignment operator.

  /// Forbid move assignment operator.
  radio_base& operator=(radio_base&&) = delete;
};
} // namespace ocudu
