// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_rx_window_checker.h  (85 lines)
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


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ofh/receiver/ofh_receiver_metrics.h"
#include "ocudu/ofh/receiver/ofh_receiver_timing_parameters.h"
#include "ocudu/ofh/timing/ofh_ota_symbol_boundary_notifier.h"
#include <atomic>


namespace ocudu {
namespace ofh {

/// \brief Open Fronthaul reception window checker.
///
/// Checks if the given slot and symbol is within the reception window or not. The window checker also collects
/// statistics and prints them every second.

/// \brief Open Fronthaul reception window checker.
///
/// Checks if the given slot and symbol is within the reception window or not. The window checker also collects
/// statistics and prints them every second.
class rx_window_checker : public ota_symbol_boundary_notifier
{
  /// Helper class that represents the reception window statistics.
  /// Helper class that represents the reception window statistics.
  class rx_window_checker_statistics
  {
    static constexpr unsigned NOF_BITS_PER_COUNTER   = 21U;
    static constexpr int32_t  EARLIEST_INITIAL_VALUE = std::numeric_limits<int32_t>::max();

    /// \brief Latest packet received.
    ///
    /// This value represents the highest number of symbols from OTA when a packet was received.

    /// \brief Latest packet received.
    ///
    /// This value represents the highest number of symbols from OTA when a packet was received.
    std::atomic<int32_t> latest_packet_in_symbols{0};
    /// \brief Earliest packet received.
    ///
    /// This value represents the smallest number of symbols from OTA when a packet was received.
    /// \brief Earliest packet received.
    ///
    /// This value represents the smallest number of symbols from OTA when a packet was received.
    std::atomic<int32_t>  earliest_packet_in_symbols{EARLIEST_INITIAL_VALUE};
    std::atomic<uint64_t> on_time_counter{0};
    std::atomic<uint64_t> early_counter{0};
    std::atomic<uint64_t> late_counter{0};
    uint64_t              last_on_time_value_printed = 0U;
    uint64_t              last_early_value_printed   = 0U;
    uint64_t              last_late_value_printed    = 0U;


  public:
    /// Collect the statistics.
    /// Collect the statistics.
    void collect_metrics(received_messages_metrics& metrics);

    /// Functions to increment the counters.

    /// Functions to increment the counters.
    void increment_on_time_counter() { on_time_counter.fetch_add(1, std::memory_order_relaxed); }
    void increment_early_counter() { early_counter.fetch_add(1, std::memory_order_relaxed); }
    void increment_late_counter() { late_counter.fetch_add(1, std::memory_order_relaxed); }
    void update_rx_timing_stats(int32_t value);

    /// Getters to the message counters.

    /// Getters to the message counters.
    uint64_t nof_on_time_messages() const { return on_time_counter.load(std::memory_order_relaxed); }
    uint64_t nof_early_messages() const { return early_counter.load(std::memory_order_relaxed); }
    uint64_t nof_late_messages() const { return late_counter.load(std::memory_order_relaxed); }
  };


  const rx_window_timing_parameters timing_parameters;
  const bool                        is_disabled;
  rx_window_checker_statistics      statistics;
  std::atomic<uint32_t>             slot_raw_value;


public:
  rx_window_checker(bool is_enabled, const rx_window_timing_parameters& params);

  // See interface for documentation.

  // See interface for documentation.
  void on_new_symbol(const slot_symbol_point_context& symbol_point_context) override;

  // See interface for documentation.

  // See interface for documentation.
  void collect_metrics(received_messages_metrics& metrics);

  /// Returns true if the Rx window checker is disabled, otherwise returns false.

  /// Returns true if the Rx window checker is disabled, otherwise returns false.
  bool disabled() const { return is_disabled; }

  /// Updates the Rx window statistics.

  /// Updates the Rx window statistics.
  void update_rx_window_statistics(slot_symbol_point symbol_point);

  /// Getters to the number of messages.

  /// Getters to the number of messages.
  uint64_t nof_on_time_messages() const { return statistics.nof_on_time_messages(); }
  uint64_t nof_early_messages() const { return statistics.nof_early_messages(); }
  uint64_t nof_late_messages() const { return statistics.nof_late_messages(); }
};


} // namespace ofh
} // namespace ocudu
