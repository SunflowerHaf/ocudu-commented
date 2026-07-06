// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ofh_metrics_collector_impl.h  (40 lines)
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


#include "ocudu/ofh/ethernet/ethernet_receiver_metrics_collector.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter_metrics_collector.h"
#include "ocudu/ofh/ofh_sector_metrics_collector.h"
#include "ocudu/ofh/receiver/ofh_receiver_metrics_collector.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_metrics_collector.h"
#include <chrono>


namespace ocudu {
namespace ofh {

/// Open Fronthaul sector metrics collector implementation.

/// Open Fronthaul sector metrics collector implementation.
class metrics_collector_impl : public metrics_collector
{
  bool                           is_enabled = false;
  const unsigned                 sector_id;
  receiver_metrics_collector*    rx_metrics_collector;
  transmitter_metrics_collector* tx_metrics_collector;

  /// The time point when the metrics where collected last time.

  /// The time point when the metrics where collected last time.
  std::chrono::high_resolution_clock::time_point last_timestamp = {};


public:
  metrics_collector_impl(receiver_metrics_collector*    rx_metrics_collector_,
                         transmitter_metrics_collector* tx_metrics_collector_,
                         unsigned                       sector_id_);

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(sector_metrics& metric) override;

  /// Returns true if the metrics are disabled, otherwise true.

  /// Returns true if the metrics are disabled, otherwise true.
  bool disabled() const { return !is_enabled; }
};


} // namespace ofh
} // namespace ocudu
