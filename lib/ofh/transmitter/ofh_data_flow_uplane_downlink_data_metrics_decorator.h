// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_data_flow_uplane_downlink_data_metrics_decorator.h  (92 lines)
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
#include "ofh_data_flow_uplane_downlink_data.h"
#include "ocudu/support/resource_usage/scoped_resource_usage.h"
#include <memory>


namespace ocudu {
namespace ofh {

/// Open Fronthaul User-Plane downlink data flow metrics decorator.

/// Open Fronthaul User-Plane downlink data flow metrics decorator.
class data_flow_uplane_downlink_metrics_decorator : public data_flow_uplane_downlink_data,
                                                    public data_flow_message_encoding_metrics_collector
{
public:
  explicit data_flow_uplane_downlink_metrics_decorator(
      std::unique_ptr<data_flow_uplane_downlink_data> data_flow_uplane_) :
    data_flow_uplane(std::move(data_flow_uplane_))
  {
    ocudu_assert(data_flow_uplane, "Invalid data flow");
  }

  // See interface for documentation.

  // See interface for documentation.
  operation_controller& get_operation_controller() override { return controller; }

  // See interface for documentation.

  // See interface for documentation.
  void enqueue_section_type_1_message(const data_flow_uplane_resource_grid_context& context,
                                      const shared_resource_grid&                   grid) override
  {
    resource_usage_utils::measurements m;
    {
      // Use scoped resource usage class to measure CPU usage of this block.
      // Use scoped resource usage class to measure CPU usage of this block.
      resource_usage_utils::scoped_resource_usage rusage_tracker(m);
      data_flow_uplane->enqueue_section_type_1_message(context, grid);
    }
    count.fetch_add(1u, std::memory_order_relaxed);
    sum_elapsed_ns.fetch_add(m.duration.count(), std::memory_order_relaxed);
    update_minmax(static_cast<uint32_t>(m.duration.count()), max_latency_ns, min_latency_ns);
  }

  // See interface for documentation.

  // See interface for documentation.
  data_flow_message_encoding_metrics_collector* get_metrics_collector() override { return this; }

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(tx_data_flow_perf_metrics& metrics) override
  {
    uint32_t total_count = count.load(std::memory_order_relaxed);
    uint32_t min_latency = min_latency_ns.load(std::memory_order_relaxed);
    uint32_t max_latency = max_latency_ns.load(std::memory_order_relaxed);
    uint64_t sum_elapsed = sum_elapsed_ns.load(std::memory_order_relaxed);


    metrics.message_packing_avg_latency_us =
        total_count ? static_cast<double>(sum_elapsed) / total_count / 1000.0 : 0.f;


    metrics.message_packing_max_latency_us =
        (max_latency == default_max_latency_ns) ? 0.f : static_cast<float>(max_latency) / 1000.f;


    metrics.message_packing_min_latency_us =
        (min_latency == default_min_latency_ns) ? 0.f : static_cast<float>(min_latency) / 1000.f;


    metrics.cpu_usage_us = static_cast<double>(sum_elapsed) / 1000.0;


    reset();
  }


private:
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


  std::unique_ptr<data_flow_uplane_downlink_data> data_flow_uplane;
  operation_controller_dummy                      controller;


  std::atomic<uint32_t> count          = {};
  std::atomic<uint64_t> sum_elapsed_ns = {};
  std::atomic<uint32_t> min_latency_ns = default_min_latency_ns;
  std::atomic<uint32_t> max_latency_ns = default_max_latency_ns;
};


} // namespace ofh
} // namespace ocudu
