// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/receiver/ofh_receiver_metrics.h  (51 lines)
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


#include "ocudu/ofh/ethernet/ethernet_receiver_metrics.h"
#include "ocudu/ofh/receiver/ofh_receiver_data_flow_metrics.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul received messages metrics.

/// Open Fronthaul received messages metrics.
struct received_messages_metrics {
  /// Number of OFH messages received on time.
  /// Number of OFH messages received on time.
  unsigned nof_on_time_messages;
  /// Number of OFH messages received early.
  /// Number of OFH messages received early.
  unsigned nof_early_messages;
  /// Number of OFH messages received late.
  /// Number of OFH messages received late.
  unsigned nof_late_messages;
  /// Earliest received message in symbol units respect OTA.
  /// Earliest received message in symbol units respect OTA.
  int earliest_rx_msg_in_symbols;
  /// Latest received message in symbol units respect OTA.
  /// Latest received message in symbol units respect OTA.
  int latest_rx_msg_in_symbols;
};

/// Open Fronthaul reception window closing metrics.

/// Open Fronthaul reception window closing metrics.
struct closed_rx_window_metrics {
  /// Number of requested uplink symbols that were not fully received within the expected reception window.
  /// Number of requested uplink symbols that were not fully received within the expected reception window.
  unsigned nof_missing_uplink_symbols;
  /// Number of PRACH context that were not fully received within the expected reception window.
  /// Number of PRACH context that were not fully received within the expected reception window.
  unsigned nof_missing_prach_contexts;
};

/// Open Fronthaul received messages decoding performance metrics.

/// Open Fronthaul received messages decoding performance metrics.
struct message_decoding_performance_metrics {
  rx_data_flow_perf_metrics data_processing_metrics;
  rx_data_flow_perf_metrics prach_processing_metrics;
  unsigned                  nof_dropped_messages;
  unsigned                  nof_skipped_messages;
};

/// Open Fronthaul receiver metrics.

/// Open Fronthaul receiver metrics.
struct receiver_metrics {
  closed_rx_window_metrics             closed_window_metrics;
  received_messages_metrics            rx_messages_metrics;
  message_decoding_performance_metrics rx_decoding_perf_metrics;
  ether::receiver_metrics              eth_receiver_metrics;
};


} // namespace ofh
} // namespace ocudu
