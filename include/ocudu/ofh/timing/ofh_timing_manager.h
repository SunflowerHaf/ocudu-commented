// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/timing/ofh_timing_manager.h  (31 lines)
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


#include "ocudu/ofh/ofh_controller.h"
#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier_manager.h"
#include "ocudu/ofh/timing/ofh_timing_metrics_collector.h"


namespace ocudu {
namespace ofh {

/// Open Fronthaul timing manager.

/// Open Fronthaul timing manager.
class timing_manager
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~timing_manager() = default;

  /// Returns the controller of this timing manager.

  /// Returns the controller of this timing manager.
  virtual operation_controller& get_controller() = 0;

  /// Returns the OTA symbol boundary notifier manager of this timing manager.

  /// Returns the OTA symbol boundary notifier manager of this timing manager.
  virtual ota_symbol_boundary_notifier_manager& get_ota_symbol_boundary_notifier_manager() = 0;

  /// Returns the timing metrics collector of this timing manager.

  /// Returns the timing metrics collector of this timing manager.
  virtual timing_metrics_collector& get_metrics_collector() = 0;
};


} // namespace ofh
} // namespace ocudu
