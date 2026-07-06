// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/transmitter/ofh_transmitter_metrics.h  (56 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: include/ocudu/ofh
// Open Fronthaul public interface headers. CONDITIONAL: linked into the binary via a temporary dependency (see lib/ofh note) but not used at runtime in split-8. These headers define the OFH contract between the lib/ofh library and its callers (primarily lib/ru/ofh).
//
// Contents:
//   ofh/compression/      — IQ compressor/decompressor abstract interfaces and compression parameter types (scheme, data width, BFP exponent).
//   ofh/ecpri/            — eCPRI packet builder, decoder, and property types.
//   ofh/ethernet/         — Ethernet frame builder/receiver interfaces, VLAN tag types, and port configuration.
//   ofh/ofh_factories.h   — Top-level OFH sector factory.
//   ofh/ofh_sector.h      — OFH sector interface (one per radio sector/cell).
//   ofh/receiver/         — OFH uplink receiver interface (delivers received IQ).
//   ofh/serdes/           — C-plane and U-plane message serialiser interfaces.
//   ofh/timing/           — OFH timing controller interface (slot indication source).
//   ofh/transmitter/      — OFH downlink transmitter interface.
// =============================================================================

#pragma once


#include "ocudu/ofh/ethernet/ethernet_transmitter_metrics.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_data_flow_metrics.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul transmitter downlink processing metrics.

/// Open Fronthaul transmitter downlink processing metrics.
struct transmitter_dl_metrics {
  /// OFH transmitter downlink C-Plane processing metrics.
  /// OFH transmitter downlink C-Plane processing metrics.
  tx_data_flow_perf_metrics dl_cp_metrics;
  /// OFH transmitter U-Plane processing metrics.
  /// OFH transmitter U-Plane processing metrics.
  tx_data_flow_perf_metrics dl_up_metrics;
  /// Number of late downlink resource grids received from the PHY.
  /// Number of late downlink resource grids received from the PHY.
  unsigned nof_late_dl_grids;
  /// Number of late Control-Plane downlink messages, ie, messages that were not transmitted.
  /// Number of late Control-Plane downlink messages, ie, messages that were not transmitted.
  unsigned nof_late_cp_dl;
  /// Number of late User-Plane downlink messages, ie, messages that were not transmitted.
  /// Number of late User-Plane downlink messages, ie, messages that were not transmitted.
  unsigned nof_late_up_dl;
};

/// Open Fronthaul transmitter uplink requests processing metrics.

/// Open Fronthaul transmitter uplink requests processing metrics.
struct transmitter_ul_metrics {
  /// Open Fronthaul transmitter uplink C-Plane processing metrics.
  /// Open Fronthaul transmitter uplink C-Plane processing metrics.
  tx_data_flow_perf_metrics ul_cp_metrics;
  /// Number of late uplink request.
  /// Number of late uplink request.
  unsigned nof_late_ul_requests;
  /// Number of late Control-Plane uplink messages, ie, messages that were not transmitted.
  /// Number of late Control-Plane uplink messages, ie, messages that were not transmitted.
  unsigned nof_late_cp_ul;
};

/// Open Fronthaul message transmitter metrics.

/// Open Fronthaul message transmitter metrics.
struct message_transmitter_metrics {
  /// Message enqueueing and transmission statistics.
  /// Message enqueueing and transmission statistics.
  float message_tx_min_latency_us;
  float message_tx_max_latency_us;
  float message_tx_avg_latency_us;

  /// CPU usage in microseconds of the message transmitter processing.

  /// CPU usage in microseconds of the message transmitter processing.
  float cpu_usage_us;
};

/// Open Fronthaul transmitter metrics.

/// Open Fronthaul transmitter metrics.
struct transmitter_metrics {
  transmitter_dl_metrics      dl_metrics;
  transmitter_ul_metrics      ul_metrics;
  message_transmitter_metrics message_tx_metrics;
  ether::transmitter_metrics  eth_transmitter_metrics;
};


} // namespace ofh
} // namespace ocudu
