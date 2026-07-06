// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ofh_metrics_collector_impl.cpp  (38 lines)
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

#include "ofh_metrics_collector_impl.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter_metrics_collector.h"
#include "ocudu/ofh/ofh_metrics.h"


using namespace ocudu;
using namespace ofh;


metrics_collector_impl::metrics_collector_impl(receiver_metrics_collector*    rx_metrics_collector_,
                                               transmitter_metrics_collector* tx_metrics_collector_,
                                               unsigned                       sector_id_) :
  sector_id(sector_id_),
  rx_metrics_collector(rx_metrics_collector_),
  tx_metrics_collector(tx_metrics_collector_),
  last_timestamp(std::chrono::high_resolution_clock::now())
{
  is_enabled = (rx_metrics_collector && tx_metrics_collector);
}


void metrics_collector_impl::collect_metrics(sector_metrics& metric)
{
  if (disabled()) {
    return;
  }


  auto tp_now      = std::chrono::high_resolution_clock::now();
  metric.sector_id = sector_id;

  // Collect receiver metrics.

  // Collect receiver metrics.
  rx_metrics_collector->collect_metrics(metric.rx_metrics);
  // Collect transmitter metrics.
  // Collect transmitter metrics.
  tx_metrics_collector->collect_metrics(metric.tx_metrics);


  metric.metrics_period_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_now - last_timestamp);
  last_timestamp           = tp_now;
}
