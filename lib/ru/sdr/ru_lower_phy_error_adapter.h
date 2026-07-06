// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_lower_phy_error_adapter.h
 * @brief Translates lower PHY error events into RU error notifications and log warnings.
 *
 * The lower PHY can detect several real-time failure conditions where the
 * upper layers did not deliver data in time, or requested more than the
 * system could handle. This adapter:
 *
 *   1. Logs a warning describing exactly what went wrong and when.
 *   2. For the two conditions that the RU's external error_notifier cares
 *      about (late downlink data, late uplink request), forwards a
 *      simplified ru_error_context up to the RU's error notifier, which
 *      ultimately reaches the upper PHY's error handler.
 *   3. Records a "critical trace" event for offline performance analysis
 *      using the trace recording system (if tracing is enabled).
 *
 * These errors indicate the system is failing to meet its real-time deadlines
 * — typically due to CPU overload, OS scheduling jitter, or misconfigured
 * thread affinities. They are a key signal for diagnosing performance problems.
 */

#pragma once


#include "ocudu/instrumentation/traces/critical_traces.h" ///< general_critical_tracer
#include "ocudu/instrumentation/traces/du_traces.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/phy/lower/lower_phy_error_notifier.h" ///< Base interface this class implements
#include "ocudu/phy/support/resource_grid_context.h"
#include "ocudu/ru/ru_error_notifier.h" ///< RU-level error notifier (forwarded to)


namespace ocudu {

/// Lower phy to RU error adapter class.

/**
 * @brief Adapts lower PHY error notifications into RU error notifications plus logging.
 */
class ru_lower_phy_error_adapter : public lower_phy_error_notifier
{
public:
  /**
   * @param logger_    Logger for warning messages about the failure.
   * @param notifier_  RU-level error notifier — forwarded to for late Tx/Rx
   *                   (the upper PHY uses this to track real-time health).
   */
  ru_lower_phy_error_adapter(ocudulog::basic_logger& logger_, ru_error_notifier& notifier_) :
    logger(logger_), notifier(notifier_)
  {
  }

  // See interface for documentation.

  /**
   * @brief Called when a downlink resource grid arrived too late to be transmitted.
   *
   * This means the upper PHY (or something further upstream) did not deliver
   * the resource grid in time for the lower PHY to perform OFDM modulation
   * and hand the samples to the radio before the slot's transmit deadline.
   * The slot is dropped — the USRP will not transmit anything for it,
   * causing a gap in the over-the-air signal.
   *
   * @param context  Identifies the sector and slot that was late.
   */
  void on_late_resource_grid(const resource_grid_context& context) override
  {
    // Forward to the RU error notifier so the upper PHY can track this.
    notifier.on_late_downlink_message(ru_error_context{.slot = context.slot, .sector = context.sector});
    logger.warning(context.slot.sfn(),
                   context.slot.slot_index(),
                   "Real-time failure in lower PHY: Downlink data late for sector {} and slot {}.",
                   context.sector,
                   context.slot);
    // Record a severity-marked trace event for offline performance debugging.
    general_critical_tracer << instant_trace_event{"on_late_resource_grid",
                                                   instant_trace_event::cpu_scope::global,
                                                   instant_trace_event::event_criticality::severe};
  }

  // See interface for documentation.

  /**
   * @brief Called when a PRACH capture request arrived too late.
   *
   * The upper PHY requested a PRACH window capture, but the request arrived
   * after the corresponding samples had already been processed (or discarded)
   * by the lower PHY. Random access attempts in this window may be missed.
   *
   * @param context  Identifies the sector, slot, and start symbol of the missed window.
   */
  void on_prach_request_late(const prach_buffer_context& context) override
  {
    logger.warning(context.slot.sfn(),
                   context.slot.slot_index(),
                   "Real-time failure in lower PHY: PRACH request late for sector {}, slot {} and start symbol {}.",
                   context.sector,
                   context.slot,
                   context.start_symbol);
    general_critical_tracer << instant_trace_event{"on_prach_request_late",
                                                   instant_trace_event::cpu_scope::global,
                                                   instant_trace_event::event_criticality::severe};
  }

  // See interface for documentation.

  /**
   * @brief Called when too many PRACH capture requests are pending simultaneously.
   *
   * The lower PHY has a limited number of concurrent PRACH capture buffers
   * (max_nof_prach_concurrent_requests). If the upper PHY requests more
   * windows than can be buffered, this overflow event fires and the excess
   * request is dropped.
   *
   * @param context  Identifies the sector, slot, and start symbol of the overflowed request.
   */
  void on_prach_request_overflow(const prach_buffer_context& context) override
  {
    logger.warning(context.slot.sfn(),
                   context.slot.slot_index(),
                   "Real-time failure in lower PHY: PRACH request overflow for sector {}, slot {} and start symbol {}.",
                   context.sector,
                   context.slot,
                   context.start_symbol);
    general_critical_tracer << instant_trace_event{"on_prach_request_overflow",
                                                   instant_trace_event::cpu_scope::global,
                                                   instant_trace_event::event_criticality::severe};
  }

  // See interface for documentation.

  /**
   * @brief Called when an uplink data slot request (PUxCH — PUSCH/PUCCH) arrived too late.
   *
   * The upper PHY requested uplink demodulation for a slot, but the request
   * arrived after the lower PHY had already discarded the corresponding
   * received samples. The uplink data for that slot is lost.
   *
   * @param context  Identifies the sector and slot that was late.
   */
  void on_puxch_request_late(const resource_grid_context& context) override
  {
    notifier.on_late_uplink_message(ru_error_context{.slot = context.slot, .sector = context.sector});
    logger.warning(context.slot.sfn(),
                   context.slot.slot_index(),
                   "Real-time failure in lower PHY: PUxCH request late for sector {}, slot {}.",
                   context.sector,
                   context.slot);
    general_critical_tracer << instant_trace_event{"on_puxch_request_late",
                                                   instant_trace_event::cpu_scope::global,
                                                   instant_trace_event::event_criticality::severe};
  }


private:
  /// Logger.
  /// Logger for warning messages about real-time failures.
  ocudulog::basic_logger& logger;
  /// Radio Unit error notifier.
  /// RU-level error notifier — receives simplified error notifications.
  ru_error_notifier& notifier;
};


} // namespace ocudu
