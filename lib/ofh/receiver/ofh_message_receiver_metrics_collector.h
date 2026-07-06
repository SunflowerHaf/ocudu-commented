// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_message_receiver_metrics_collector.h  (76 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#pragma once


#include "ofh_data_flow_uplane_decoding_metrics_collector.h"
#include "ocudu/ofh/receiver/ofh_receiver_metrics.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul message receiver metrics collector.

/// Open Fronthaul message receiver metrics collector.
class message_receiver_metrics_collector
{
public:
  message_receiver_metrics_collector(bool                                          is_enabled_,
                                     data_flow_message_decoding_metrics_collector& df_uplink_metrics_collector_,
                                     data_flow_message_decoding_metrics_collector& df_prach_metrics_collector_) :
    is_enabled(is_enabled_),
    df_uplink_metrics_collector(df_uplink_metrics_collector_),
    df_prach_metrics_collector(df_prach_metrics_collector_)
  {
  }

  /// Returns true if the metrics collector is enabled, false otherwise.

  /// Returns true if the metrics collector is enabled, false otherwise.
  bool enabled() const { return is_enabled; }

  /// Updates the PRACH message decoding statistics given the execution time taken by processing a received message.

  /// Updates the PRACH message decoding statistics given the execution time taken by processing a received message.
  void update_prach_stats(std::chrono::nanoseconds exec_latency)
  {
    df_prach_metrics_collector.update_stats(exec_latency);
  }

  /// Updates the uplink data message decoding statistics given the execution time taken by processing a received
  /// message.

  /// Updates the uplink data message decoding statistics given the execution time taken by processing a received
  /// message.
  void update_uplink_stats(std::chrono::nanoseconds exec_latency)
  {
    df_uplink_metrics_collector.update_stats(exec_latency);
  }

  /// Updates the number of skipped messages by increasing the counter the given value.

  /// Updates the number of skipped messages by increasing the counter the given value.
  void update_skipped_messages(unsigned value) { nof_skipped_messages.fetch_add(value, std::memory_order_relaxed); }

  /// Increases dropped messages by one.

  /// Increases dropped messages by one.
  void increase_dropped_messages() { nof_dropped_messages.fetch_add(1, std::memory_order_relaxed); }

  /// Collects message receiver performance metrics.

  /// Collects message receiver performance metrics.
  void collect_metrics(message_decoding_performance_metrics& metrics)
  {
    if (!enabled()) {
    }


    df_uplink_metrics_collector.collect_metrics(metrics.data_processing_metrics);
    df_prach_metrics_collector.collect_metrics(metrics.prach_processing_metrics);
    metrics.nof_dropped_messages = nof_dropped_messages.exchange(0, std::memory_order_relaxed);
    metrics.nof_skipped_messages = nof_skipped_messages.exchange(0, std::memory_order_relaxed);
  }


private:
  const bool                                    is_enabled;
  data_flow_message_decoding_metrics_collector& df_uplink_metrics_collector;
  data_flow_message_decoding_metrics_collector& df_prach_metrics_collector;
  /// \brief Number of possible skipped OFH messages.
  ///
  /// A message is considered skipped when the expected sequence id does not match the  message sequence id, and the
  /// message sequence id value is higher than expected.
  /// \brief Number of possible skipped OFH messages.
  ///
  /// A message is considered skipped when the expected sequence id does not match the  message sequence id, and the
  /// message sequence id value is higher than expected.
  std::atomic<unsigned> nof_skipped_messages = {0};
  /// \brief Number of OFH messages dropped.
  ///
  /// A message is dropped when the expected sequence id does not match the message sequence id and the message sequence
  /// id value is smaller than expected..
  /// \brief Number of OFH messages dropped.
  ///
  /// A message is dropped when the expected sequence id does not match the message sequence id and the message sequence
  /// id value is smaller than expected..
  std::atomic<unsigned> nof_dropped_messages = {0};
};


} // namespace ofh
} // namespace ocudu
