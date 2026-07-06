// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/ethernet/ethernet_rx_buffer_pool.h  (74 lines)
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


#include "ethernet_rx_buffer_impl.h"
#include "ocudu/adt/mpmc_queue.h"
#include "ocudu/adt/span.h"
#include "ocudu/support/math/math_utils.h"
#include "ocudu/support/ocudu_assert.h"
#include "ocudu/support/units.h"
#include <optional>
#include <vector>


namespace ocudu {
namespace ether {

/// Pool of buffers accessed by a socket-based Ethernet receiver.

/// Pool of buffers accessed by a socket-based Ethernet receiver.
class ethernet_rx_buffer_pool
{
  /// Allocate 4MB of storage, evenly divided between Ethernet receive buffers.
  /// Allocate 4MB of storage, evenly divided between Ethernet receive buffers.
  static constexpr units::bytes ETH_BUFFER_POOL_SIZE{4096000};


  using rx_buffer_id_list =
      concurrent_queue<unsigned, concurrent_queue_policy::lockfree_mpmc, concurrent_queue_wait_policy::non_blocking>;


  unsigned number_of_buffers;


  std::vector<std::vector<uint8_t>> entries;
  rx_buffer_id_list                 free_list;


public:
  /// Constructor allocates buffers with given size, assigns an ID to each of them and puts them into a list of free
  /// buffers.
  /// Constructor allocates buffers with given size, assigns an ID to each of them and puts them into a list of free
  /// buffers.
  explicit ethernet_rx_buffer_pool(unsigned buffer_size) :
    number_of_buffers(divide_ceil(ETH_BUFFER_POOL_SIZE.value(), buffer_size)),
    entries(number_of_buffers),
    free_list(number_of_buffers)
  {
    for (unsigned i = 0; i != number_of_buffers; ++i) {
      entries[i].resize(buffer_size);
      while (!free_list.try_push(i)) {
      }
    }
  }

  /// Tries to get an ID of a free buffer from the pre-allocated storage.

  /// Tries to get an ID of a free buffer from the pre-allocated storage.
  std::optional<ethernet_rx_buffer_impl> reserve()
  {
    unsigned buffer_id;
    if (free_list.try_pop(buffer_id)) {
      return std::make_optional<ethernet_rx_buffer_impl>(*this, buffer_id);
    }
    return std::nullopt;
  }

  /// Marks the buffer with given ID as free.

  /// Marks the buffer with given ID as free.
  void free(unsigned buffer_id)
  {
    // Push identifier back in the pool.
    // Push identifier back in the pool.
    while (!free_list.try_push(buffer_id)) {
    }
  }

  /// Returns the span of data belonging to a buffer with the given ID.

  /// Returns the span of data belonging to a buffer with the given ID.
  span<uint8_t> get_data(unsigned id)
  {
    ocudu_assert(id < entries.size(), "Buffer index ({}) is out of range ({}).", id, entries.size());
    return {entries[id].data(), entries[id].size()};
  }
};


} // namespace ether
} // namespace ocudu
