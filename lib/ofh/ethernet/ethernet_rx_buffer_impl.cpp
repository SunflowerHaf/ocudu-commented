// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_rx_buffer_impl.cpp  (56 lines)
//
// ⚠  CONDITIONAL — only active with DPDK (lib/hal) or as OFH split-7.2 RU (lib/ofh, lib/ru/ofh).
//
// DIRECTORY: lib/ofh
// Open Fronthaul (OFH) library — implements the O-RAN 7.2x split between a Radio Unit (O-RU) and the O-DU. CONDITIONAL: compiled into the binary but never called at runtime in split-8 (which uses the SDR/UHD path instead). The OFH stack is the alternative to the split-8 radio path.
//
// Contents:
//   lib/ofh/compression/  — IQ sample compression/decompression (BFP, mod-comp, sRSRP) as defined in O-RAN.WG4.CUS specification.
//   lib/ofh/ecpri/        — eCPRI packet builder and decoder (the layer-2 protocol that carries ORAN C/U-plane messages over Ethernet).
//   lib/ofh/ethernet/     — Raw Ethernet socket layer; also a DPDK Ethernet backend for line-rate packet processing.
//   lib/ofh/receiver/     — OFH uplink receiver: deframes eCPRI packets, decompresses IQ, and delivers symbols to the upper PHY.
//   lib/ofh/serdes/       — Serialise/deserialise C-plane (control) and U-plane (user/data) ORAN messages.
//   lib/ofh/support/      — Shared OFH utilities (sequence number handling, TX window management).
//   lib/ofh/timing/       — OFH timing controller: generates slot indications from Ethernet PTP timestamps and maintains the T1a/Ta4 timing windows.
//   lib/ofh/transmitter/  — OFH downlink transmitter: compresses IQ, builds eCPRI packets, and enqueues them for Ethernet transmission.
// =============================================================================

#include "ethernet_rx_buffer_impl.h"
#include "ethernet_rx_buffer_pool.h"


using namespace ocudu;
using namespace ether;


ethernet_rx_buffer_impl::ethernet_rx_buffer_impl(ethernet_rx_buffer_pool& pool_, unsigned id_) : pool(pool_), id(id_)
{
  size = pool.get_data(id).size();
}


ethernet_rx_buffer_impl::ethernet_rx_buffer_impl(ethernet_rx_buffer_impl&& other) noexcept :
  pool(other.pool), id(std::exchange(other.id, -1)), size(std::exchange(other.size, 0))
{
}


ethernet_rx_buffer_impl& ethernet_rx_buffer_impl::operator=(ethernet_rx_buffer_impl&& other) noexcept
{
  id         = other.id;
  size       = other.size;
  other.id   = -1;
  other.size = 0;


  return *this;
}


span<const uint8_t> ethernet_rx_buffer_impl::data() const
{
  ocudu_assert(id >= 0, "Invalid Ethernet rx buffer accessed");
  return pool.get_data(id).first(size);
}


span<uint8_t> ethernet_rx_buffer_impl::storage()
{
  ocudu_assert(id >= 0, "Invalid Ethernet rx buffer accessed");
  return pool.get_data(id);
}


void ethernet_rx_buffer_impl::resize(unsigned used_size)
{
  ocudu_assert(id >= 0, "Invalid Ethernet rx buffer accessed");
  ocudu_assert(used_size <= pool.get_data(id).size(),
               "The size of buffer can not be bigger than the allocated size of {} bytes",
               pool.get_data(id).size());
  size = used_size;
}


ethernet_rx_buffer_impl::~ethernet_rx_buffer_impl()
{
  if (id >= 0) {
    pool.free(id);
  }
}
