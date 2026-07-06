// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/transmitter/ofh_transmitter.h  (40 lines)
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


#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include "ocudu/ofh/transmitter/ofh_downlink_handler.h"
#include "ocudu/ofh/transmitter/ofh_uplink_request_handler.h"


namespace ocudu {
namespace ofh {


class operation_controller;
class transmitter_metrics_collector;

/// Open Fronthaul transmitter interface.

/// Open Fronthaul transmitter interface.
class transmitter
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~transmitter() = default;

  /// Returns the uplink request handler of this Open Fronthaul transmitter.

  /// Returns the uplink request handler of this Open Fronthaul transmitter.
  virtual uplink_request_handler& get_uplink_request_handler() = 0;

  /// Returns the downlink handler of this Open Fronthaul transmitter.

  /// Returns the downlink handler of this Open Fronthaul transmitter.
  virtual downlink_handler& get_downlink_handler() = 0;

  /// Returns the controller of this Open Fronthaul transmitter.

  /// Returns the controller of this Open Fronthaul transmitter.
  virtual operation_controller& get_operation_controller() = 0;

  /// Returns the OTA symbol boundary notifier of this Open Fronthaul transmitter.

  /// Returns the OTA symbol boundary notifier of this Open Fronthaul transmitter.
  virtual ota_symbol_boundary_notifier& get_ota_symbol_boundary_notifier() = 0;

  /// Returns the metrics collector of this Open Fronthaul transmitter or nullptr if metrics are disabled.

  /// Returns the metrics collector of this Open Fronthaul transmitter or nullptr if metrics are disabled.
  virtual transmitter_metrics_collector* get_metrics_collector() = 0;
};


} // namespace ofh
} // namespace ocudu
