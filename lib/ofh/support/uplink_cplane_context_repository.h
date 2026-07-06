// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/uplink_cplane_context_repository.h  (99 lines)
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


#include "context_repository_helpers.h"
#include "ocudu/ofh/ofh_constants.h"
#include "ocudu/ofh/serdes/ofh_cplane_message_properties.h"
#include "ocudu/ran/slot_pdu_capacity_constants.h"
#include <array>
#include <atomic>
#include <vector>


namespace ocudu {
namespace ofh {

/// Uplink Control-Plane context.

/// Uplink Control-Plane context.
struct ul_cplane_context {
  /// Filter index.
  /// Filter index.
  filter_index_type filter_index;
  /// Start symbol identifier.
  /// Start symbol identifier.
  uint8_t start_symbol;
  /// Starting PRB of data section.
  /// Starting PRB of data section.
  uint16_t prb_start;
  /// Number of contiguous PRBs per data section.
  /// Number of contiguous PRBs per data section.
  uint16_t nof_prb;
  /// Number of symbols.
  /// Number of symbols.
  uint8_t nof_symbols;
};

/// Uplink Control-Plane context repository.

/// Uplink Control-Plane context repository.
class uplink_cplane_context_repository
{
  using repo_entry = std::array<std::atomic<uint64_t>, MAX_SUPPORTED_EAXC_ID_VALUE>;

  /// Repository storage.

  /// Repository storage.
  std::vector<repo_entry> repo;

  /// Returns the entry of the repository for the given slot and eAxC.

  /// Returns the entry of the repository for the given slot and eAxC.
  std::atomic<uint64_t>& get_entry(slot_point slot, unsigned eaxc)
  {
    unsigned index = calculate_repository_index(slot, repo.size());
    return repo[index][eaxc];
  }

  /// Returns the entry of the repository for the given slot and eAxC.

  /// Returns the entry of the repository for the given slot and eAxC.
  const std::atomic<uint64_t>& get_entry(slot_point slot, unsigned eaxc) const
  {
    unsigned index = calculate_repository_index(slot, repo.size());
    return repo[index][eaxc];
  }

  /// Packs the given context.

  /// Packs the given context.
  static uint64_t pack_context(ul_cplane_context context)
  {
    uint64_t data = 0;
    data |= static_cast<uint8_t>(context.filter_index);
    data |= static_cast<uint64_t>(context.start_symbol) << 8;
    data |= static_cast<uint64_t>(context.prb_start) << 16;
    data |= static_cast<uint64_t>(context.nof_prb) << 32;
    data |= static_cast<uint64_t>(context.nof_symbols) << 48;


    return data;
  }

  /// Unpacks the given packed context.

  /// Unpacks the given packed context.
  static ul_cplane_context unpack_context(uint64_t data)
  {
    return {static_cast<filter_index_type>(data),
            static_cast<uint8_t>(data >> 8),
            static_cast<uint16_t>(data >> 16),
            static_cast<uint16_t>(data >> 32),
            static_cast<uint8_t>(data >> 48)};
  }


public:
  explicit uplink_cplane_context_repository(unsigned size_) : repo(size_)
  {
    static_assert(MAX_PRACH_OCCASIONS_PER_SLOT == 1,
                  "Uplink Control-Plane context repository only supports one context per slot and eAxC");
  }

  /// Add the given context to the repo at the given slot and eAxC.

  /// Add the given context to the repo at the given slot and eAxC.
  void add(slot_point slot, unsigned eaxc, ul_cplane_context new_context)
  {
    auto& entry = get_entry(slot, eaxc);
    entry.store(pack_context(new_context), std::memory_order_relaxed);
  }

  /// Returns a context that matches the given slot and eAxC.

  /// Returns a context that matches the given slot and eAxC.
  ul_cplane_context get(slot_point slot, unsigned eaxc) const
  {
    const auto& entry = get_entry(slot, eaxc);
    return unpack_context(entry.load(std::memory_order_relaxed));
  }
};


} // namespace ofh
} // namespace ocudu
