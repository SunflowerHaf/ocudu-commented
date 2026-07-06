// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_rx_metrics_collector_impl.h  (85 lines)
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
#include "ocudu/ofh/ethernet/ethernet_receiver_metrics.h"
#include "ocudu/ofh/ethernet/ethernet_receiver_metrics_collector.h"


namespace ocudu {
namespace ether {

/// Open Fronthaul Ethernet receiver metrics collector implementation.

/// Open Fronthaul Ethernet receiver metrics collector implementation.
class receiver_metrics_collector_impl : public receiver_metrics_collector
{
public:
  explicit receiver_metrics_collector_impl(bool enabled_) : enabled(enabled_) {}

  /// Returns true if the metrics collector is disabled, false otherwise.

  /// Returns true if the metrics collector is disabled, false otherwise.
  bool disabled() const { return !enabled; }

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(receiver_metrics& metrics) override
  {
    if (disabled()) {
      return;
    }


    uint32_t total_number_of_packets = total_nof_packets.load(std::memory_order_relaxed);
    uint64_t sum_rx_time             = sum_rx_time_ns.load(std::memory_order_relaxed);


    metrics.avg_packet_rx_latency_us =
        total_number_of_packets ? static_cast<double>(sum_rx_time) / total_number_of_packets / 1000.0 : 0.f;
    metrics.max_packet_rx_latency_us = static_cast<float>(max_rx_latency_ns.load(std::memory_order_relaxed)) / 1000.f;
    metrics.total_nof_bytes          = sum_rx_bytes.load(std::memory_order_relaxed);
    metrics.cpu_usage_us             = static_cast<double>(sum_rx_time) / 1000.0;


    reset_stats();
  }

  /// Returns new measurement object.

  /// Returns new measurement object.
  ofh::time_execution_measurer create_time_execution_measurer() const
  {
    return ofh::time_execution_measurer(!disabled());
  }

  /// Updates internal statistics.

  /// Updates internal statistics.
  void update_stats(std::chrono::nanoseconds elapsed_ns, uint64_t nof_bytes = 0, uint64_t nof_packets = 1)
  {
    if (disabled()) {
      return;
    }


    sum_rx_time_ns.fetch_add(elapsed_ns.count(), std::memory_order_relaxed);
    if (nof_bytes > 0) {
      sum_rx_bytes.fetch_add(nof_bytes, std::memory_order_relaxed);
      total_nof_packets.fetch_add(nof_packets, std::memory_order_relaxed);
      ofh::update_minmax(static_cast<uint32_t>(elapsed_ns.count() / nof_packets), max_rx_latency_ns, min_rx_latency_ns);
    }
  }


private:
  static constexpr uint32_t default_min_latency_ns = std::numeric_limits<uint32_t>::max();
  static constexpr uint32_t default_max_latency_ns = std::numeric_limits<uint32_t>::min();

  /// Resets values of all internal counters.

  /// Resets values of all internal counters.
  void reset_stats()
  {
    sum_rx_time_ns.store(0, std::memory_order_relaxed);
    sum_rx_bytes.store(0, std::memory_order_relaxed);
    total_nof_packets.store(0, std::memory_order_relaxed);
    min_rx_latency_ns.store(default_min_latency_ns, std::memory_order_relaxed);
    max_rx_latency_ns.store(default_max_latency_ns, std::memory_order_relaxed);
  }


  const bool            enabled;
  std::atomic<uint64_t> sum_rx_time_ns    = {};
  std::atomic<uint64_t> sum_rx_bytes      = {};
  std::atomic<uint32_t> total_nof_packets = {};
  std::atomic<uint32_t> min_rx_latency_ns = default_min_latency_ns;
  std::atomic<uint32_t> max_rx_latency_ns = default_max_latency_ns;
};


} // namespace ether
} // namespace ocudu
