// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_transmitter_metrics_collector_impl.h  (58 lines)
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


#include "ofh_downlink_handler_metrics_collector.h"
#include "ofh_message_transmitter_metrics_collector.h"
#include "ofh_uplink_request_handler_metrics_collector.h"
#include "ocudu/ofh/ethernet/ethernet_transmitter_metrics_collector.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_metrics_collector.h"


namespace ocudu {
namespace ofh {


class transmitter_metrics_collector_impl : public transmitter_metrics_collector
{
public:
  transmitter_metrics_collector_impl(bool                                      metrics_enabled,
                                     downlink_handler_metrics_collector&       dl_metrics_collector_,
                                     uplink_request_handler_metrics_collector& ul_metrics_collector_,
                                     message_transmitter_metrics_collector&    message_tx_collector_,
                                     ether::transmitter_metrics_collector*     eth_transmitter_collector_) :
    is_disabled(!metrics_enabled),
    dl_metrics_collector(dl_metrics_collector_),
    ul_metrics_collector(ul_metrics_collector_),
    message_tx_collector(message_tx_collector_),
    eth_transmitter_collector(eth_transmitter_collector_)
  {
  }

  /// Returns true if the metrics collector is disabled.

  /// Returns true if the metrics collector is disabled.
  bool disabled() const { return is_disabled; }

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(transmitter_metrics& metric) override
  {
    if (is_disabled) {
      return;
    }


    dl_metrics_collector.collect_metrics(metric.dl_metrics);
    ul_metrics_collector.collect_metrics(metric.ul_metrics);
    message_tx_collector.collect_metrics(metric.message_tx_metrics);
    if (eth_transmitter_collector) {
      eth_transmitter_collector->collect_metrics(metric.eth_transmitter_metrics);
    }
  }


private:
  const bool                                is_disabled;
  downlink_handler_metrics_collector&       dl_metrics_collector;
  uplink_request_handler_metrics_collector& ul_metrics_collector;
  message_transmitter_metrics_collector&    message_tx_collector;
  ether::transmitter_metrics_collector*     eth_transmitter_collector;
};


} // namespace ofh
} // namespace ocudu
