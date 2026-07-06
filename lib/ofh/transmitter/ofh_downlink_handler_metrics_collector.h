// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_downlink_handler_metrics_collector.h  (58 lines)
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
#include "ofh_data_flow_uplane_downlink_data.h"
#include "ofh_tx_window_checker.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_metrics.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul downlink handler metrics collector.

/// Open Fronthaul downlink handler metrics collector.
class downlink_handler_metrics_collector
{
public:
  downlink_handler_metrics_collector(data_flow_cplane_scheduling_commands& df_cplane,
                                     data_flow_uplane_downlink_data&       df_uplane,
                                     tx_window_checker&                    window_checker_) :
    df_cplane_collector(df_cplane.get_metrics_collector()),
    df_uplane_collector(df_uplane.get_metrics_collector()),
    window_checker(window_checker_)
  {
  }

  /// Updates the number of late messages (messages that were not transmitted) of the Control-Plane downlink by the
  /// given value.

  /// Updates the number of late messages (messages that were not transmitted) of the Control-Plane downlink by the
  /// given value.
  void update_cp_dl_lates(unsigned nof_lates) { nof_late_cp_dl.fetch_add(nof_lates, std::memory_order_relaxed); }

  /// Updates the number of late messages (messages that were not transmitted) of the Control-Plane downlink by the
  /// given value.

  /// Updates the number of late messages (messages that were not transmitted) of the Control-Plane downlink by the
  /// given value.
  void update_up_dl_lates(unsigned nof_lates) { nof_late_up_dl.fetch_add(nof_lates, std::memory_order_relaxed); }

  /// Collects downlink handler metrics.

  /// Collects downlink handler metrics.
  void collect_metrics(transmitter_dl_metrics& metrics)
  {
    if (df_cplane_collector) {
      df_cplane_collector->collect_metrics(metrics.dl_cp_metrics);
    }
    if (df_uplane_collector) {
      df_uplane_collector->collect_metrics(metrics.dl_up_metrics);
    }
    metrics.nof_late_dl_grids = window_checker.get_nof_lates_and_reset();
    metrics.nof_late_cp_dl    = nof_late_cp_dl.exchange(0, std::memory_order_relaxed);
    metrics.nof_late_up_dl    = nof_late_up_dl.exchange(0, std::memory_order_relaxed);
  }


private:
  data_flow_message_encoding_metrics_collector* df_cplane_collector;
  data_flow_message_encoding_metrics_collector* df_uplane_collector;
  tx_window_checker&                            window_checker;
  std::atomic<uint32_t>                         nof_late_cp_dl = {0};
  std::atomic<uint32_t>                         nof_late_up_dl = {0};
};


} // namespace ofh
} // namespace ocudu
