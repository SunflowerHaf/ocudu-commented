// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_radio_event_handler.h
 * @brief Logging and fan-out handlers for radio hardware (UHD) events.
 *
 * The radio_session (UHD-backed in this deployment) reports hardware-level
 * events through the radio_event_notifier interface: late transmit packets,
 * Tx underflows (the USRP ran out of samples to transmit), and Rx overflows
 * (the receive buffer filled up before software could drain it).
 *
 * This file defines two implementations of that interface:
 *
 *   ru_radio_logger_event_handler:  Writes a warning to the RF log for
 *                                   significant events (late, underflow,
 *                                   overflow), and a debug-level message
 *                                   for every event regardless of severity.
 *
 *   ru_radio_event_dispatcher:      Fans a single event out to multiple
 *                                   handlers. Used by ru_sdr_impl to send
 *                                   every radio event to both the metrics
 *                                   collector (for counting) and the logger
 *                                   (for visibility) simultaneously.
 */

#pragma once


#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/radio/radio_event_notifier.h" ///< Base interface both classes implement


namespace ocudu {

/// Radio Unit radio event logger.

/**
 * @brief Logs radio hardware events to the RF log channel.
 */
class ru_radio_logger_event_handler : public radio_event_notifier
{
public:
  /**
   * @param logger_  The RF logger to write event messages to.
   */
  explicit ru_radio_logger_event_handler(ocudulog::basic_logger& logger_) : logger(logger_) {}

  // See interface for documentation.

  /**
   * @brief Called by the radio session when a hardware event occurs.
   *
   * For the three real-time failure types (LATE, UNDERFLOW, OVERFLOW), logs
   * a warning — these indicate the system is failing to keep up with the
   * radio's real-time deadlines and are important operational signals.
   *
   * Additionally, every event (regardless of type) is logged at debug level
   * with full detail (type, source, timestamp if available) for deep
   * diagnostics when debug logging is enabled.
   *
   * @param description  The event type, source, and optional timestamp.
   */
  void on_radio_rt_event(const event_description& description) override
  {
    // Warn-level logging for real-time failure conditions.
    if (description.type == radio_event_type::LATE || description.type == radio_event_type::UNDERFLOW ||
        description.type == radio_event_type::OVERFLOW) {
      logger.warning("Real-time failure in RF: {}", to_string(description.type));
    }


    static const auto& log_format_debug = "Real-time failure in RF: Type={} Source={} Timestamp={}";


    // Debug-level logging with full detail, for every event type.
    if (description.timestamp.has_value()) {
      logger.debug(
          log_format_debug, to_string(description.type), to_string(description.source), *description.timestamp);
    } else {
      logger.debug(log_format_debug, to_string(description.type), to_string(description.source), "na");
    }
  }


private:
  /// The RF logger to write event messages to.
  ocudulog::basic_logger& logger;
};

/// Radio event dispatcher.

/**
 * @brief Fans out a single radio event to multiple registered handlers.
 *
 * Used by ru_sdr_impl to ensure every radio event reaches both the
 * metrics collector (which counts occurrences) and the logger handler
 * (which writes log messages), without either needing to know about the other.
 */
class ru_radio_event_dispatcher : public radio_event_notifier
{
  /// The list of handlers to forward every event to.
  std::vector<radio_event_notifier*> handlers;


public:
  /**
   * @param handlers_  The handlers to receive every radio event. Must be
   *                   non-empty and contain no null pointers.
   */
  explicit ru_radio_event_dispatcher(std::vector<radio_event_notifier*> handlers_) : handlers(std::move(handlers_))
  {
    ocudu_assert(!handlers.empty(), "Empty list of radio event notifiers");
    ocudu_assert(std::all_of(handlers.begin(), handlers.end(), [](auto* handler) { return handler != nullptr; }),
                 "Invalid radio event notifier");
  }

  // See interface for documentation.

  /**
   * @brief Forwards the event to every registered handler in order.
   *
   * @param description  The radio event to dispatch.
   */
  void on_radio_rt_event(const event_description& description) override
  {
    for (auto* handler : handlers) {
      handler->on_radio_rt_event(description);
    }
  }
};


} // namespace ocudu
