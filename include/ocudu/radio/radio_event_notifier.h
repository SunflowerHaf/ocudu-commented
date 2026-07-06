// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/radio/radio_event_notifier.h  (104 lines)
//
// INTERFACE HEADER — include/ocudu/radio
// Radio hardware interface headers: radio_session (the top-level radio session — controls the USRP), radio_management_plane (start/stop/config), radio_data_plane_rx_notifier and tx_streamer (the IQ sample streaming interfaces), and the radio_notification_handler for overflow/underflow events.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/radio/radio_base.h"
#include <cstdint>
#include <optional>


namespace ocudu {

/// Radio event sources.

/// Radio event sources.
enum class radio_event_source {
  /// Default event value meaning it is not set.
  /// Default event value meaning it is not set.
  UNDEFINED = 0,
  /// The event is from a receiver chain.
  /// The event is from a receiver chain.
  RECEIVE,
  /// The event is from a transmit chain.
  /// The event is from a transmit chain.
  TRANSMIT,
  /// The event cause is not listed from the above chain.
  /// The event cause is not listed from the above chain.
  OTHER
};

/// Translate an event_source to a string.

/// Translate an event_source to a string.
inline const char* to_string(radio_event_source value)
{
  switch (value) {
    case radio_event_source::UNDEFINED:
      return "undefined";
    case radio_event_source::RECEIVE:
      return "rx";
    case radio_event_source::TRANSMIT:
      return "tx";
    case radio_event_source::OTHER:
      return "other";
  }
  return "";
}

/// Radio event types.

/// Radio event types.
enum class radio_event_type {
  /// Default event value meaning it is not set.
  /// Default event value meaning it is not set.
  UNDEFINED = 0,
  /// Indicates an start of a burst.
  /// Indicates an start of a burst.
  START_OF_BURST,
  /// Indicates the end of a burst.
  /// Indicates the end of a burst.
  END_OF_BURST,
  /// The transmit data arrives late to the baseband unit.
  /// The transmit data arrives late to the baseband unit.
  LATE,
  /// The transmit data is not generated fast enough.
  /// The transmit data is not generated fast enough.
  UNDERFLOW,
  /// The receive buffers are not read fast enough.
  /// The receive buffers are not read fast enough.
  OVERFLOW,
  /// The event cause is not listed from the above causes.
  /// The event cause is not listed from the above causes.
  OTHER
};

/// Translate an event_type to a string.

/// Translate an event_type to a string.
inline const char* to_string(radio_event_type value)
{
  switch (value) {
    case radio_event_type::UNDEFINED:
      return "undefined";
    case radio_event_type::START_OF_BURST:
      return "start-of-burst";
    case radio_event_type::END_OF_BURST:
      return "end-of-burst";
    case radio_event_type::LATE:
      return "late";
    case radio_event_type::UNDERFLOW:
      return "underflow";
    case radio_event_type::OVERFLOW:
      return "overflow";
    case radio_event_type::OTHER:
      return "other";
  }
  return "";
}

/// \brief Describes a baseband unit event notifier interface.
///
/// This class describes an interface used by the baseband unit to notify events related with its operation.

/// \brief Describes a baseband unit event notifier interface.
///
/// This class describes an interface used by the baseband unit to notify events related with its operation.
class radio_event_notifier : public radio_base
{
public:
  /// Describes a radio notification.
  /// Describes a radio notification.
  struct event_description {
    /// Indicates the stream identifier that triggered the event if it is available.
    /// Indicates the stream identifier that triggered the event if it is available.
    std::optional<unsigned> stream_id;
    /// Indicates the channel identifier that triggered the event if it is available.
    /// Indicates the channel identifier that triggered the event if it is available.
    std::optional<unsigned> channel_id;
    /// Indicates the source of the event.
    /// Indicates the source of the event.
    radio_event_source source = radio_event_source::UNDEFINED;
    /// Indicates the event type.
    /// Indicates the event type.
    radio_event_type type = radio_event_type::UNDEFINED;
    /// Indicates the timestamp of this event if it is available.
    /// Indicates the timestamp of this event if it is available.
    std::optional<uint64_t> timestamp;
  };

  /// Notifies a new event that affected the real-time operation of the radio.

  /// Notifies a new event that affected the real-time operation of the radio.
  virtual void on_radio_rt_event(const event_description& description) = 0;
};


} // namespace ocudu
