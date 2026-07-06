// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

/**
 * @file ru_radio_metrics_collector.cpp
 * @brief Implementation of radio hardware event counting for metrics.
 */

#include "ru_radio_metrics_collector.h"


using namespace ocudu;


/**
 * @brief Increments the appropriate counter based on the event type.
 *
 * Uses relaxed memory ordering since these are independent counters with no
 * ordering relationship to other memory operations — only the final count
 * value matters, not the ordering of increments relative to other code.
 *
 * @param description  The radio event reported by the radio session.
 */
void ru_radio_metrics_collector::on_radio_rt_event(const event_description& description)
{
  // Count events.
  switch (description.type) {
    case radio_event_type::LATE:
      late_count.fetch_add(1, std::memory_order_relaxed);
      break;
    case radio_event_type::UNDERFLOW:
      underflow_count.fetch_add(1, std::memory_order_relaxed);
      break;
    case radio_event_type::OVERFLOW:
      overflow_count.fetch_add(1, std::memory_order_relaxed);
      break;
    case radio_event_type::UNDEFINED:
    case radio_event_type::START_OF_BURST:
    case radio_event_type::END_OF_BURST:
    case radio_event_type::OTHER:
      // Uncounted.
      // These are normal operational events, not failures — not counted.
      break;
  }
}


/**
 * @brief Reads each counter and atomically resets it to zero.
 *
 * Using exchange() rather than load()+store() ensures no events are lost:
 * if a new event arrives between the load and the store in a non-atomic
 * read-then-reset, that increment would be silently dropped. exchange()
 * performs the read-and-reset as one indivisible operation.
 *
 * @param metrics  The output struct to populate with the current counts.
 */
void ru_radio_metrics_collector::collect_metrics(radio_metrics& metrics)
{
  metrics.late_count      = late_count.exchange(0, std::memory_order_relaxed);
  metrics.underflow_count = underflow_count.exchange(0, std::memory_order_relaxed);
  metrics.overflow_count  = overflow_count.exchange(0, std::memory_order_relaxed);
}
