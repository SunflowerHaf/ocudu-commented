// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ofh/ethernet/dpdk/dpdk_ethernet_rx_buffer.h  (59 lines)
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


#include "ocudu/ofh/ethernet/ethernet_unique_buffer.h"
#include "ocudu/support/ocudu_assert.h"
#include <rte_ethdev.h>


namespace ocudu {
namespace ether {

/// Receive buffer wrapper dedicated for DPDK Ethernet receiver.

/// Receive buffer wrapper dedicated for DPDK Ethernet receiver.
class dpdk_rx_buffer_impl : public rx_buffer
{
public:
  explicit dpdk_rx_buffer_impl(::rte_mbuf* mbuf_) : mbuf(mbuf_)
  {
    ocudu_assert(mbuf, "Invalid DPDK mbuf was passed to dpdk_rx_buffer_impl");
  }

  /// Copy constructor is deleted.

  /// Copy constructor is deleted.
  dpdk_rx_buffer_impl(dpdk_rx_buffer_impl& /**/) = delete;

  /// Move constructor.

  /// Move constructor.
  dpdk_rx_buffer_impl(dpdk_rx_buffer_impl&& other) noexcept
  {
    mbuf       = other.mbuf;
    other.mbuf = nullptr;
  }

  /// Move assignment operator.

  /// Move assignment operator.
  dpdk_rx_buffer_impl& operator=(dpdk_rx_buffer_impl&& other) noexcept
  {
    // Free stored mbuf.
    // Free stored mbuf.
    ::rte_pktmbuf_free(mbuf);


    mbuf       = other.mbuf;
    other.mbuf = nullptr;
    return *this;
  }


  ~dpdk_rx_buffer_impl() { ::rte_pktmbuf_free(mbuf); }

  // See interface for documentation.

  // See interface for documentation.
  span<const uint8_t> data() const override
  {
    ocudu_assert(mbuf != nullptr, "Invalid dpdk_rx_buffer_impl accessed");


    ::uint8_t* eth_data = rte_pktmbuf_mtod(mbuf, uint8_t*);
    return span<const uint8_t>(eth_data, mbuf->pkt_len);
  }


private:
  ::rte_mbuf* mbuf;
};


} // namespace ether
} // namespace ocudu
