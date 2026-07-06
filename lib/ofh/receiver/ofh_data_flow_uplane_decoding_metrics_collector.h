// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_data_flow_uplane_decoding_metrics_collector.h  (89 lines)
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


#include "../support/metrics_helpers.h"
#include "ocudu/ofh/receiver/ofh_receiver_data_flow_metrics.h"
#include <atomic>
#include <chrono>
#include <limits>


namespace ocudu {
namespace ofh {

/// Open Fronthaul receiver data flow performance metrics collector.

/// Open Fronthaul receiver data flow performance metrics collector.
class data_flow_message_decoding_metrics_collector
{
public:
  explicit data_flow_message_decoding_metrics_collector(bool is_enabled) : is_disabled(!is_enabled) {}

  /// Returns true if the metrics collector is enabled, false otherwise.

  /// Returns true if the metrics collector is enabled, false otherwise.
  bool enabled() const { return !is_disabled; }

  /// Updates the performance statistics.
  ///
  /// \param[in] exec_latency Execution time taken by processing a received message.

  /// Updates the performance statistics.
  ///
  /// \param[in] exec_latency Execution time taken by processing a received message.
  void update_stats(std::chrono::nanoseconds exec_latency)
  {
    if (is_disabled) {
      return;
    }


    sum_elapsed_ns.fetch_add(exec_latency.count(), std::memory_order_relaxed);
    count.fetch_add(1u, std::memory_order_relaxed);
    update_minmax(static_cast<uint32_t>(exec_latency.count()), max_latency_ns, min_latency_ns);
  }

  /// Increases by one the number of dropped messages.

  /// Increases by one the number of dropped messages.
  void increase_dropped_messages() { nof_dropped_messages.fetch_add(1, std::memory_order_relaxed); }

  /// Collect the performance metrics of a data flow.

  /// Collect the performance metrics of a data flow.
  void collect_metrics(rx_data_flow_perf_metrics& metrics)
  {
    metrics.nof_dropped_messages = nof_dropped_messages.exchange(0, std::memory_order_relaxed);


    uint32_t count_val          = count.load(std::memory_order_relaxed);
    uint32_t min_latency_val_ns = min_latency_ns.load(std::memory_order_relaxed);
    uint32_t max_latency_val_ns = max_latency_ns.load(std::memory_order_relaxed);
    uint64_t sum_elapsed_val_ns = sum_elapsed_ns.load(std::memory_order_relaxed);


    metrics.message_unpacking_avg_latency_us =
        count_val ? static_cast<double>(sum_elapsed_val_ns) / count_val / 1000.0 : 0.f;


    metrics.message_unpacking_min_latency_us =
        (min_latency_val_ns == default_min_latency_ns) ? 0.f : static_cast<float>(min_latency_val_ns) / 1000.f;


    metrics.message_unpacking_max_latency_us =
        (max_latency_val_ns == default_max_latency_ns) ? 0.f : static_cast<float>(max_latency_val_ns) / 1000.f;


    metrics.cpu_usage_us = static_cast<double>(sum_elapsed_val_ns) / 1000.0;


    reset();
  }


private:
  /// Default values for min and max latencies.
  /// Default values for min and max latencies.
  static constexpr uint32_t default_min_latency_ns = std::numeric_limits<uint32_t>::max();
  static constexpr uint32_t default_max_latency_ns = std::numeric_limits<uint32_t>::min();

  /// Resets values of all internal counters.

  /// Resets values of all internal counters.
  void reset()
  {
    count.store(0, std::memory_order_relaxed);
    sum_elapsed_ns.store(0, std::memory_order_relaxed);
    min_latency_ns.store(default_min_latency_ns, std::memory_order_relaxed);
    max_latency_ns.store(default_max_latency_ns, std::memory_order_relaxed);
  }


  std::atomic<uint32_t> count                = {};
  std::atomic<uint64_t> sum_elapsed_ns       = {};
  std::atomic<uint32_t> min_latency_ns       = default_min_latency_ns;
  std::atomic<uint32_t> max_latency_ns       = default_max_latency_ns;
  std::atomic<uint32_t> nof_dropped_messages = {0};


  const bool is_disabled;
};


} // namespace ofh
} // namespace ocudu
