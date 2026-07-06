// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/ofh_tx_window_checker.h  (73 lines)
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


#include "ocudu/ocudulog/ocudulog.h"
#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include <atomic>


namespace ocudu {
namespace ofh {

/// Open Fronthaul transmission window checker.

/// Open Fronthaul transmission window checker.
class tx_window_checker : public ota_symbol_boundary_notifier
{
public:
  tx_window_checker(ocudulog::basic_logger& logger_,
                    unsigned                sector_id_,
                    uint32_t                advance_time_in_symbols_,
                    uint32_t                nof_symbols_) :
    logger(logger_), sector_id(sector_id_), advance_time_in_symbols(advance_time_in_symbols_), nof_symbols(nof_symbols_)
  {
  }

  // See interface for documentation.

  // See interface for documentation.
  void on_new_symbol(const slot_symbol_point_context& symbol_point_context) override
  {
    // This atomic is only written from a single thread.
    // This atomic is only written from a single thread.
    count_val.store(symbol_point_context.symbol_point.to_uint(), std::memory_order::memory_order_relaxed);
  }

  /// Returns true if the given slot is already late compared to the current OTA time, otherwise false.

  /// Returns true if the given slot is already late compared to the current OTA time, otherwise false.
  bool is_late(slot_point slot)
  {
    slot_symbol_point ota_symbol_point(
        slot.numerology(), count_val.load(std::memory_order::memory_order_relaxed), nof_symbols);

    // Use symbol 0 as the worst case for the resource grid slot.

    // Use symbol 0 as the worst case for the resource grid slot.
    slot_symbol_point rg_point(slot, 0, nof_symbols);
    rg_point -= advance_time_in_symbols;


    if (ota_symbol_point < rg_point) {
      return false;
    }


    if (OCUDU_UNLIKELY(logger.debug.enabled())) {
      logger.debug("Sector#{}: a late upper-PHY downlink request arrived to OFH in slot '{}_{}' with current "
                   "ota_slot='{}_{}', OFH processing time requires a minimum of '{}' symbols",
                   sector_id,
                   slot,
                   0,
                   ota_symbol_point.get_slot(),
                   ota_symbol_point.get_symbol_index(),
                   advance_time_in_symbols);
    }


    late_counter.fetch_add(1, std::memory_order_relaxed);
    return true;
  }


  uint32_t get_nof_lates_and_reset() { return late_counter.exchange(0, std::memory_order_relaxed); }


private:
  ocudulog::basic_logger& logger;
  const unsigned          sector_id;
  const uint32_t          advance_time_in_symbols;
  const uint32_t          nof_symbols;
  std::atomic<uint32_t>   count_val;
  std::atomic<uint32_t>   late_counter{0};
};


} // namespace ofh
} // namespace ocudu
