// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/dpdk/dpdk_ethernet_port_context.h  (65 lines)
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


#include "ocudu/support/units.h"
#include <memory>


struct rte_mempool;


namespace ocudu {
namespace ether {

/// DPDK configuration settings.

/// DPDK configuration settings.
constexpr unsigned MAX_BURST_SIZE  = 64;
constexpr unsigned MAX_BUFFER_SIZE = 9600;

/// DPDK port configuration.

/// DPDK port configuration.
struct dpdk_port_config {
  /// Device identifier.
  /// Device identifier.
  std::string id;
  /// Promiscuous mode flag.
  /// Promiscuous mode flag.
  bool is_promiscuous_mode_enabled;
  /// Ethernet link status checking flag.
  /// Ethernet link status checking flag.
  bool is_link_status_check_enabled;
  /// MTU size.
  /// MTU size.
  units::bytes mtu_size;
};

/// \brief DPDK Ethernet port context.
///
/// Encapsulates and manages the lifetime of the internal DPDK resources of an Ethernet port.

/// \brief DPDK Ethernet port context.
///
/// Encapsulates and manages the lifetime of the internal DPDK resources of an Ethernet port.
class dpdk_port_context
{
  dpdk_port_context(const std::string& port_id_, unsigned dpdk_port_id_, ::rte_mempool* mem_pool_) :
    port_id(port_id_), dpdk_port_id(dpdk_port_id_), mem_pool(mem_pool_)
  {
  }


public:
  /// Creates and initializes a new DPDK port context with the given configuration.
  /// Creates and initializes a new DPDK port context with the given configuration.
  static std::shared_ptr<dpdk_port_context> create(const dpdk_port_config& config);


  ~dpdk_port_context();

  /// Returns the DPDK port identifier of this context .

  /// Returns the DPDK port identifier of this context .
  unsigned get_dpdk_port_id() const { return dpdk_port_id; }

  /// Returns the string port identifier of this context.

  /// Returns the string port identifier of this context.
  const std::string& get_port_id() const { return port_id; }

  /// Returns the mbuf memory pool of this context.

  /// Returns the mbuf memory pool of this context.
  ::rte_mempool* get_mempool() { return mem_pool; }

  /// Returns the mbuf memory pool of this context.

  /// Returns the mbuf memory pool of this context.
  const ::rte_mempool* get_mempool() const { return mem_pool; }


private:
  const std::string    port_id;
  const unsigned       dpdk_port_id;
  ::rte_mempool* const mem_pool;
};


} // namespace ether
} // namespace ocudu
