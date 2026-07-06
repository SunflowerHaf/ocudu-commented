// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/timing/ofh_timing_metrics_collector_impl.cpp  (44 lines)
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

#include "ofh_timing_metrics_collector_impl.h"
#include "../support/metrics_helpers.h"
#include "ocudu/ofh/timing/ofh_timing_metrics.h"


using namespace ocudu;
using namespace ofh;


void timing_metrics_collector_impl::collect_metrics(timing_metrics& metrics)
{
  metrics.nof_skipped_symbols       = nof_skipped_symbols.exchange(0, std::memory_order_relaxed);
  metrics.skipped_symbols_max_burst = skipped_symbols_max_burst.exchange(0, std::memory_order_relaxed);


  uint32_t count_val          = count.exchange(0, std::memory_order_relaxed);
  uint64_t sum_elapsed_val_ns = sum_elapsed_ns.exchange(0, std::memory_order_relaxed);
  uint32_t min_latency_val_ns = min_latency_ns.exchange(default_min_latency_ns, std::memory_order_relaxed);
  uint32_t max_latency_val_ns = max_latency_ns.exchange(default_max_latency_ns, std::memory_order_relaxed);


  metrics.notification_avg_latency_us = count_val ? static_cast<double>(sum_elapsed_val_ns) / count_val / 1000.0 : 0.f;
  metrics.notification_min_latency_us =
      (min_latency_val_ns == default_min_latency_ns) ? 0.f : static_cast<float>(min_latency_val_ns) / 1000.f;
  metrics.notification_max_latency_us =
      (max_latency_val_ns == default_max_latency_ns) ? 0.f : static_cast<float>(max_latency_val_ns) / 1000.f;
}


void timing_metrics_collector_impl::update_skipped_symbols(unsigned num_skipped_symbols)
{
  nof_skipped_symbols.fetch_add(num_skipped_symbols, std::memory_order_relaxed);

  // Update the maximum number of continuous symbols skipped.

  // Update the maximum number of continuous symbols skipped.
  unsigned current_max = skipped_symbols_max_burst.load(std::memory_order_relaxed);
  while (num_skipped_symbols > current_max &&
         !skipped_symbols_max_burst.compare_exchange_weak(current_max, num_skipped_symbols)) {
  }
}


void timing_metrics_collector_impl::update_symbol_notification_latency(std::chrono::nanoseconds notifier_latency)
{
  sum_elapsed_ns.fetch_add(notifier_latency.count(), std::memory_order_relaxed);
  count.fetch_add(1u, std::memory_order_relaxed);
  update_minmax(static_cast<uint32_t>(notifier_latency.count()), max_latency_ns, min_latency_ns);
}
