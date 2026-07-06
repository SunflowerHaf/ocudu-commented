// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/radio/radio_constants.h  (17 lines)
//
// INTERFACE HEADER — include/ocudu/radio
// Radio hardware interface headers: radio_session (the top-level radio session — controls the USRP), radio_management_plane (start/stop/config), radio_data_plane_rx_notifier and tx_streamer (the IQ sample streaming interfaces), and the radio_notification_handler for overflow/underflow events.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


namespace ocudu {

/// Maximum number of channels per stream in a radio baseband unit.

/// Maximum number of channels per stream in a radio baseband unit.
constexpr unsigned RADIO_MAX_NOF_CHANNELS = 4;

/// Maximum number of streams that a radio baseband unit can support.

/// Maximum number of streams that a radio baseband unit can support.
constexpr unsigned RADIO_MAX_NOF_STREAMS = 8;

/// Total maximum number of ports that a radio baseband unit can support.

/// Total maximum number of ports that a radio baseband unit can support.
constexpr unsigned RADIO_MAX_NOF_PORTS = RADIO_MAX_NOF_CHANNELS * RADIO_MAX_NOF_STREAMS;


} // namespace ocudu
