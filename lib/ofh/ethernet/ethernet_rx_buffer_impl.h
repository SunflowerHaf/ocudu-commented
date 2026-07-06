// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_rx_buffer_impl.h  (54 lines)
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

#pragma once


#include "ocudu/ofh/ethernet/ethernet_unique_buffer.h"
#include "ocudu/support/ocudu_assert.h"


namespace ocudu {
namespace ether {


class ethernet_rx_buffer_pool;

/// Receive buffer wrapper dedicated for socket-based Ethernet receiver.

/// Receive buffer wrapper dedicated for socket-based Ethernet receiver.
class ethernet_rx_buffer_impl : public rx_buffer
{
public:
  /// Constructor receives the reference to the pool, from which one buffer is requested.
  /// Constructor receives the reference to the pool, from which one buffer is requested.
  ethernet_rx_buffer_impl(ethernet_rx_buffer_pool& pool_, unsigned id);

  /// Destructor frees this buffer in the pool.

  /// Destructor frees this buffer in the pool.
  ~ethernet_rx_buffer_impl() override;

  /// Copy constructor is deleted.

  /// Copy constructor is deleted.
  ethernet_rx_buffer_impl(const ethernet_rx_buffer_impl& other) = delete;

  /// Copy assignment operator is deleted.

  /// Copy assignment operator is deleted.
  ethernet_rx_buffer_impl& operator=(const ethernet_rx_buffer_impl& other) = delete;

  /// Move constructor.

  /// Move constructor.
  ethernet_rx_buffer_impl(ethernet_rx_buffer_impl&& other) noexcept;

  /// Move assignment operator.

  /// Move assignment operator.
  ethernet_rx_buffer_impl& operator=(ethernet_rx_buffer_impl&& other) noexcept;

  // See interface for documentation.

  // See interface for documentation.
  span<const uint8_t> data() const override;

  /// Returns span of bytes for writing.

  /// Returns span of bytes for writing.
  span<uint8_t> storage();

  /// Sets the actually used size.

  /// Sets the actually used size.
  void resize(unsigned used_size);


private:
  ethernet_rx_buffer_pool& pool;
  int                      id = -1;
  /// Using size instead of a span here to save space and to enable using this class inside a \c unique_task
  /// implementation exploiting small buffer vtable.
  /// Using size instead of a span here to save space and to enable using this class inside a \c unique_task
  /// implementation exploiting small buffer vtable.
  unsigned size = 0;
};


} // namespace ether
} // namespace ocudu
