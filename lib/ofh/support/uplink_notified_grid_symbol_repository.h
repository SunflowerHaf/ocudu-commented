// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/uplink_notified_grid_symbol_repository.h  (154 lines)
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


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/slot_point.h"
#include <atomic>
#include <optional>
#include <vector>


namespace ocudu {
namespace ofh {

/// Uplink notified grid symbol repository. Stores the symbols that have been notified to upper layers for a given slot.

/// Uplink notified grid symbol repository. Stores the symbols that have been notified to upper layers for a given slot.
class uplink_notified_grid_symbol_repository
{
  /// Starting from bit 16, it codifies if the symbol is valid (1) or not valid (0).
  /// Starting from bit 16, it codifies if the symbol is valid (1) or not valid (0).
  static constexpr unsigned VALID_SYMBOL_BITMASK_START_BIT = 16;
  /// Cyclic prefix bit. 1 for extended, 0 for normal.
  /// Cyclic prefix bit. 1 for extended, 0 for normal.
  static constexpr unsigned EXTENDED_CP_BIT = 14;
  /// Used entry bit. 1 for slot used, 0 slot not used.
  /// Used entry bit. 1 for slot used, 0 slot not used.
  static constexpr unsigned USED_SLOT_BIT                    = 15;
  static constexpr uint32_t USED_SLOT_BITMAP                 = 1u << USED_SLOT_BIT;
  static constexpr uint32_t EXTENDED_CP_BITMAP               = 1u << EXTENDED_CP_BIT;
  static constexpr uint32_t ALL_SYMBOLS_NOTIFIED_CP_NORMAL   = (1u << get_nsymb_per_slot(cyclic_prefix::NORMAL)) - 1;
  static constexpr uint32_t ALL_SYMBOLS_NOTIFIED_CP_EXTENDED = (1u << get_nsymb_per_slot(cyclic_prefix::EXTENDED)) - 1;


  using repo_entry = std::atomic<uint32_t>;
  std::vector<repo_entry> repo;

  /// Returns the entry for the given slot.

  /// Returns the entry for the given slot.
  std::atomic<uint32_t>& get_entry(slot_point slot) { return repo[slot.system_slot() % repo.size()]; }

  /// Returns true if the slot is used, otherwise false.

  /// Returns true if the slot is used, otherwise false.
  static constexpr bool is_slot_used(uint32_t value) { return value & USED_SLOT_BITMAP; }

  /// Returns true if all symbols have been notified, otherwise false.

  /// Returns true if all symbols have been notified, otherwise false.
  static constexpr bool are_all_symbols_notified(uint32_t value)
  {
    if (value & EXTENDED_CP_BITMAP) {
      return (value & ALL_SYMBOLS_NOTIFIED_CP_EXTENDED) == ALL_SYMBOLS_NOTIFIED_CP_EXTENDED;
    }


    return (value & ALL_SYMBOLS_NOTIFIED_CP_NORMAL) == ALL_SYMBOLS_NOTIFIED_CP_NORMAL;
  }

  /// Returns true if any symbol smaller than the given symbol has not been notified, otherwise false.

  /// Returns true if any symbol smaller than the given symbol has not been notified, otherwise false.
  static constexpr bool is_any_previous_symbol_missed(uint32_t value, unsigned symbol)
  {
    for (unsigned i = 0, e = symbol; i != e; ++i) {
      if (((value >> i) & 1) == 0) {
        return true;
      }
    }


    return false;
  }

  /// Returns the maximum number of symbols of the given value.

  /// Returns the maximum number of symbols of the given value.
  static constexpr unsigned get_nof_symbols(uint32_t value)
  {
    return get_nsymb_per_slot(static_cast<cyclic_prefix::options>((value & EXTENDED_CP_BITMAP) >> EXTENDED_CP_BIT));
  }

  /// Returns the number of symbols to notify starting from the given symbol.

  /// Returns the number of symbols to notify starting from the given symbol.
  static constexpr unsigned get_nof_symbols_to_notify(uint32_t value, unsigned symbol)
  {
    unsigned nof_symbols = get_nof_symbols(value);


    value = value >> symbol;

    // :TODO: use ctz when the public API is implemented.
    // Start in one to count for symbol and check the higher symbols.

    // :TODO: use ctz when the public API is implemented.
    // Start in one to count for symbol and check the higher symbols.
    for (unsigned i = 1, e = nof_symbols - symbol; i != e; ++i) {
      if (((value >> i) & 1) == 0) {
        return i;
      }
    }

    // At this point all the upper symbols are received, notify all of them.

    // At this point all the upper symbols are received, notify all of them.
    return nof_symbols - symbol;
  }

  /// Clears the slot by setting the entry to not used.

  /// Clears the slot by setting the entry to not used.
  void clear_slot(slot_point slot) { get_entry(slot).store(0, std::memory_order_relaxed); }


public:
  struct results {
    results() : valid_symbols(MAX_NSYMB_PER_SLOT) {}
    interval<unsigned>                 symbols;
    bounded_bitset<MAX_NSYMB_PER_SLOT> valid_symbols;
  };


  explicit uplink_notified_grid_symbol_repository(unsigned size) : repo(size) {}

  /// Adds an entry to the repository for the given slot and start_symbol. Usually start symbol is 0 for the whole grid,
  /// but can be modified.

  /// Adds an entry to the repository for the given slot and start_symbol. Usually start symbol is 0 for the whole grid,
  /// but can be modified.
  void add(slot_point slot, unsigned start_symbol = 0U, cyclic_prefix cp = cyclic_prefix::NORMAL)
  {
    ocudu_assert(start_symbol < MAX_NSYMB_PER_SLOT, "Invalid start symbol '{}'", start_symbol);


    uint32_t value = USED_SLOT_BITMAP;
    if (cp == cyclic_prefix::EXTENDED) {
      value |= EXTENDED_CP_BITMAP;
    }

    // Mark the bits as already sent for symbols < start_symbol.

    // Mark the bits as already sent for symbols < start_symbol.
    value |= static_cast<uint32_t>((uint32_t(1u) << start_symbol) - 1);


    get_entry(slot).store(value, std::memory_order_relaxed);
  }

  /// Updates grid received symbol for the given slot and returns a list of symbols to notify.

  /// Updates grid received symbol for the given slot and returns a list of symbols to notify.
  std::optional<results> update_rx_symbol_and_compute_symbols_to_notify(slot_point slot, unsigned symbol, bool is_valid)
  {
    ocudu_assert(symbol < MAX_NSYMB_PER_SLOT, "Invalid symbol '{}'", symbol);


    uint32_t bitmask = 0;
    bitmask |= uint32_t(1u) << symbol;
    // Set the bitmask validity.
    // Set the bitmask validity.
    if (is_valid) {
      bitmask |= uint32_t(1u) << (symbol + VALID_SYMBOL_BITMASK_START_BIT);
    }


    uint32_t value = get_entry(slot).fetch_or(bitmask, std::memory_order_relaxed);


    if (!is_slot_used(value)) {
      return std::nullopt;
    }


    if (is_any_previous_symbol_missed(value, symbol)) {
      return std::nullopt;
    }


    unsigned nof_symbols_to_notify = get_nof_symbols_to_notify(value, symbol);


    value |= bitmask;


    if (are_all_symbols_notified(value)) {
      clear_slot(slot);
    }


    results output;
    output.symbols = {symbol, symbol + nof_symbols_to_notify};
    output.valid_symbols.from_uint64(uint64_t(value >> VALID_SYMBOL_BITMASK_START_BIT));


    return std::make_optional<results>(output);
  }
};


} // namespace ofh
} // namespace ocudu
