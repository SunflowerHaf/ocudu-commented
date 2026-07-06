// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_radio_metrics_collector.h
 * @brief Counts radio hardware real-time failure events for metrics reporting.
 *
 * This class implements radio_event_notifier so it can be registered (via
 * ru_radio_event_dispatcher) to receive every radio hardware event. It counts
 * three significant event types using atomic counters (since events may
 * arrive from a different thread than the one polling the metrics):
 *
 *   LATE:      A transmit packet's timestamp had already passed by the time
 *              the USRP received it — the sample was dropped.
 *   UNDERFLOW: The USRP's internal Tx buffer ran empty before software
 *              supplied the next chunk of samples — a gap occurred in the
 *              transmitted signal.
 *   OVERFLOW:  The USRP's internal Rx buffer filled up before software could
 *              read it — some received samples were lost.
 *
 * These counters are read and reset (atomically exchanged with zero) each
 * time collect_metrics() is called, so each metrics report shows the count
 * of events that occurred since the previous report.
 */

#pragma once


#include "ocudu/radio/radio_event_notifier.h" ///< Base interface this class implements
#include "ocudu/ru/sdr/ru_sdr_metrics.h" ///< radio_metrics — the output struct
#include <atomic>


namespace ocudu {

/// Radio Unit radio notification counter.

/**
 * @brief Counts radio hardware events for periodic metrics reporting.
 */
class ru_radio_metrics_collector : public radio_event_notifier
{
public:
  // See interface for documentation.
  /**
   * @brief Called by the radio session (via the event dispatcher) on every hardware event.
   *
   * Increments the corresponding atomic counter for LATE, UNDERFLOW, and
   * OVERFLOW events. Other event types (START_OF_BURST, END_OF_BURST, OTHER,
   * UNDEFINED) are not counted — they're normal operational events, not failures.
   *
   * @param description  The radio event to count.
   */
  void on_radio_rt_event(const event_description& description) override;

  /// Collect radio metrics.

  /**
   * @brief Reads and resets the event counters into the given metrics struct.
   *
   * Uses atomic exchange to read each counter and reset it to zero in one
   * operation, ensuring no events are lost or double-counted even if more
   * events arrive concurrently from another thread during the read.
   *
   * @param metrics  The output radio_metrics struct to populate.
   */
  void collect_metrics(radio_metrics& metrics);


private:
  /// Count of late transmit packets since the last collect_metrics() call.
  std::atomic<unsigned> late_count      = {};
  /// Count of Tx underflow events since the last collect_metrics() call.
  std::atomic<unsigned> underflow_count = {};
  /// Count of Rx overflow events since the last collect_metrics() call.
  std::atomic<unsigned> overflow_count  = {};
};


} // namespace ocudu
