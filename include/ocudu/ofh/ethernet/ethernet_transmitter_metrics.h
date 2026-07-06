// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/ethernet_transmitter_metrics.h  (28 lines)
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


#include <cstdint>


namespace ocudu {
namespace ether {

/// Open Fronthaul Ethernet transmitter metrics.

/// Open Fronthaul Ethernet transmitter metrics.
struct transmitter_metrics {
  /// Average instantaneous transmission throughput in Megabits per second.
  /// Average instantaneous transmission throughput in Megabits per second.
  float avg_rate_Mbps;
  /// Average latency of packet transmission in microseconds.
  /// Average latency of packet transmission in microseconds.
  float avg_packet_tx_latency_us;
  /// Maximum latency of packet transmission in microseconds.
  /// Maximum latency of packet transmission in microseconds.
  float max_packet_tx_latency_us;
  /// Minimum latency of packet transmission in microseconds.
  /// Minimum latency of packet transmission in microseconds.
  float min_packet_tx_latency_us;
  /// Total number of bytes transmitted during metrics period.
  /// Total number of bytes transmitted during metrics period.
  uint64_t total_nof_bytes;
  /// CPU usage in microseconds of the Ethernet transmitter.
  /// CPU usage in microseconds of the Ethernet transmitter.
  float cpu_usage_us;
};


} // namespace ether
} // namespace ocudu
