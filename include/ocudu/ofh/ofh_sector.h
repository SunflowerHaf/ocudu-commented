// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ofh_sector.h  (37 lines)
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


namespace ocudu {
namespace ofh {


class operation_controller;
class error_notifier;
class receiver;
class metrics_collector;
class transmitter;

/// \brief Open Fronthaul sector interface.
///
/// A sector represents the minimum entity to send and receive data from the Open Fronthaul.

/// \brief Open Fronthaul sector interface.
///
/// A sector represents the minimum entity to send and receive data from the Open Fronthaul.
class sector
{
public:
  virtual ~sector() = default;

  /// Returns the Open Fronthaul receiver of this sector.

  /// Returns the Open Fronthaul receiver of this sector.
  virtual receiver& get_receiver() = 0;

  /// Returns the Open Fronthaul transmitter of this sector.

  /// Returns the Open Fronthaul transmitter of this sector.
  virtual transmitter& get_transmitter() = 0;

  /// Returns the Open Fronthaul controller of this sector.

  /// Returns the Open Fronthaul controller of this sector.
  virtual operation_controller& get_operation_controller() = 0;

  /// Returns the Open Fronthaul metrics collector of this sector or nullptr if metrics are disabled.

  /// Returns the Open Fronthaul metrics collector of this sector or nullptr if metrics are disabled.
  virtual metrics_collector* get_metrics_collector() = 0;
};


} // namespace ofh
} // namespace ocudu
