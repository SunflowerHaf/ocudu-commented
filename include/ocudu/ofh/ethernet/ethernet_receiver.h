// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/ethernet_receiver.h  (29 lines)
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
namespace ether {


class receiver_metrics_collector;
class receiver_operation_controller;

/// \brief Describes an Ethernet receiver.
///
/// The receiver notifies incoming Ethernet frames through the \c frame_notifier interface.

/// \brief Describes an Ethernet receiver.
///
/// The receiver notifies incoming Ethernet frames through the \c frame_notifier interface.
class receiver
{
public:
  /// Default destructor.
  /// Default destructor.
  virtual ~receiver() = default;

  /// Returns the operation controller of this Ethernet receiver.

  /// Returns the operation controller of this Ethernet receiver.
  virtual receiver_operation_controller& get_operation_controller() = 0;

  /// Returns the metrics collector of this Ethernet receiver or nullptr if metrics are disabled.

  /// Returns the metrics collector of this Ethernet receiver or nullptr if metrics are disabled.
  virtual receiver_metrics_collector* get_metrics_collector() = 0;
};


} // namespace ether
} // namespace ocudu
