// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/ethernet_transmitter_config.h  (29 lines)
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


#include "ocudu/ofh/ethernet/ethernet_mac_address.h"
#include "ocudu/support/units.h"


namespace ocudu {
namespace ether {

/// Configuration for the Ethernet transmitter.

/// Configuration for the Ethernet transmitter.
struct transmitter_config {
  /// Ethernet interface name or identifier.
  /// Ethernet interface name or identifier.
  std::string interface;
  /// Promiscuous mode flag.
  /// Promiscuous mode flag.
  bool is_promiscuous_mode_enabled = false;
  /// Ethernet link status checking flag.
  /// Ethernet link status checking flag.
  bool is_link_status_check_enabled = false;
  /// If set to true, metrics are enabled in the Ethernet transmitter.
  /// If set to true, metrics are enabled in the Ethernet transmitter.
  bool are_metrics_enabled = false;
  /// MTU size.
  /// MTU size.
  units::bytes mtu_size;
  /// Destination MAC address.
  /// Destination MAC address.
  mac_address mac_dst_address;
};


} // namespace ether
} // namespace ocudu
