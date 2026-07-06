// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ofh_metrics.h  (39 lines)
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


#include "ocudu/adt/static_vector.h"
#include "ocudu/ofh/receiver/ofh_receiver_metrics.h"
#include "ocudu/ofh/timing/ofh_timing_metrics.h"
#include "ocudu/ofh/transmitter/ofh_transmitter_metrics.h"
#include "ocudu/ran/gnb_constants.h"
#include <chrono>


namespace ocudu {
namespace ofh {

/// Open Fronthaul sector metrics.

/// Open Fronthaul sector metrics.
struct sector_metrics {
  /// Sector identifier.
  /// Sector identifier.
  unsigned sector_id;
  /// Receiver metrics.
  /// Receiver metrics.
  receiver_metrics rx_metrics;
  /// Transmitter metrics.
  /// Transmitter metrics.
  transmitter_metrics tx_metrics;
  /// Metrics period.
  /// Metrics period.
  std::chrono::milliseconds metrics_period_ms;
};

/// Open Fronthaul metrics.

/// Open Fronthaul metrics.
struct metrics {
  /// Timestamp of the OFH RU metrics.
  /// Timestamp of the OFH RU metrics.
  std::chrono::time_point<std::chrono::system_clock> timestamp;
  /// Timing metrics.
  /// Timing metrics.
  timing_metrics timing;
  /// Metrics for every sector.
  /// Metrics for every sector.
  static_vector<sector_metrics, MAX_CELLS_PER_DU> sectors;
};


} // namespace ofh
} // namespace ocudu
