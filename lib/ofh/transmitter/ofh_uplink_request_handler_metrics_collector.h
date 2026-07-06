// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_uplink_request_handler_metrics_collector.h  (44 lines)
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


#include "ofh_data_flow_cplane_scheduling_commands.h"
#include "ofh_tx_window_checker.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_metrics.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul uplink request handler metrics collector.

/// Open Fronthaul uplink request handler metrics collector.
class uplink_request_handler_metrics_collector
{
public:
  uplink_request_handler_metrics_collector(data_flow_message_encoding_metrics_collector* df_metrics_collector_,
                                           tx_window_checker&                            window_checker_) :
    df_metrics_collector(df_metrics_collector_), window_checker(window_checker_)
  {
  }

  /// Updates the number of late messages (messages that were not transmitted) of the Control-Plane uplink by the
  /// given value.

  /// Updates the number of late messages (messages that were not transmitted) of the Control-Plane uplink by the
  /// given value.
  void update_cp_ul_lates(unsigned nof_lates) { nof_late_cp_ul.fetch_add(nof_lates, std::memory_order_relaxed); }

  /// Collects uplink request handler metrics.

  /// Collects uplink request handler metrics.
  void collect_metrics(transmitter_ul_metrics& metrics)
  {
    if (df_metrics_collector) {
      df_metrics_collector->collect_metrics(metrics.ul_cp_metrics);
    }
    metrics.nof_late_ul_requests = window_checker.get_nof_lates_and_reset();
    metrics.nof_late_cp_ul       = nof_late_cp_ul.exchange(0, std::memory_order_relaxed);
  }


private:
  data_flow_message_encoding_metrics_collector* df_metrics_collector;
  tx_window_checker&                            window_checker;
  std::atomic<uint32_t>                         nof_late_cp_ul = {0};
};


} // namespace ofh
} // namespace ocudu
