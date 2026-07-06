// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/receiver/ofh_rx_window_checker.cpp  (130 lines)
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

#include "ofh_rx_window_checker.h"
#include "support/metrics_helpers.h"
#include "ocudu/ofh/receiver/ofh_receiver_metrics.h"


using namespace ocudu;
using namespace ofh;


static constexpr unsigned OFH_MAX_NOF_SFN = 256U;


rx_window_checker::rx_window_checker(bool is_enabled, const rx_window_timing_parameters& params) :
  timing_parameters(params), is_disabled(!is_enabled), slot_raw_value(0)
{
}

/// Calculates the Open Fronthaul slot symbol point for the given symbol point. An Open Fronthaul slot symbol point is a
/// normal one, but with the SFN values restricted to 1 Byte.

/// Calculates the Open Fronthaul slot symbol point for the given symbol point. An Open Fronthaul slot symbol point is a
/// normal one, but with the SFN values restricted to 1 Byte.
static slot_symbol_point calculate_ofh_slot_symbol_point(slot_symbol_point symbol_point)
{
  // Build a new slot symbol point that manages that the SFN values in OFH is 1 byte.
  // Build a new slot symbol point that manages that the SFN values in OFH is 1 byte.
  slot_point ota_slot = symbol_point.get_slot();
  slot_point ofh_slot(ota_slot.numerology(), ota_slot.sfn() % OFH_MAX_NOF_SFN, ota_slot.slot_index());


  return {ofh_slot, symbol_point.get_symbol_index(), symbol_point.get_nof_symbols()};
}

/// Calculate the distance between the given slot symbol points in symbols.

/// Calculate the distance between the given slot symbol points in symbols.
static int calculate_slot_symbol_point_distance(slot_symbol_point lhs, slot_symbol_point rhs)
{
  ocudu_assert(rhs.get_numerology() == lhs.get_numerology(),
               "Cannot calculate the distance of two slot symbol points that have different numerologies");
  ocudu_assert(rhs.get_nof_symbols() == lhs.get_nof_symbols(),
               "Cannot calculate the distance of two slot symbol points that have a different number of symbols");


  const int nof_symbols_per_slot_wrap = OFH_MAX_NOF_SFN * NOF_SUBFRAMES_PER_FRAME *
                                        get_nof_slots_per_subframe(to_subcarrier_spacing(rhs.get_numerology())) *
                                        rhs.get_nof_symbols();


  int a = static_cast<int>(lhs.to_uint()) - static_cast<int>(rhs.to_uint());
  if (a >= nof_symbols_per_slot_wrap / 2) {
    return a - nof_symbols_per_slot_wrap;
  }
  if (a < -nof_symbols_per_slot_wrap / 2) {
    return a + nof_symbols_per_slot_wrap;
  }
  return a;
}


void rx_window_checker::on_new_symbol(const slot_symbol_point_context& symbol_point_context)
{
  if (is_disabled) {
    return;
  }

  // Build a new slot symbol point that manages that the SFN values in OFH is 1 byte.

  // Build a new slot symbol point that manages that the SFN values in OFH is 1 byte.
  slot_symbol_point ota_symbol_point = calculate_ofh_slot_symbol_point(symbol_point_context.symbol_point);

  // Update the stored slot symbol point as system value.

  // Update the stored slot symbol point as system value.
  slot_raw_value.store(ota_symbol_point.to_uint(), std::memory_order_relaxed);
}


void rx_window_checker::update_rx_window_statistics(slot_symbol_point symbol_point)
{
  if (is_disabled) {
    return;
  }

  // Store the ota symbol point to use the same value for the early and late points.

  // Store the ota symbol point to use the same value for the early and late points.
  slot_symbol_point ota_point(
      symbol_point.get_numerology(), slot_raw_value.load(std::memory_order_relaxed), symbol_point.get_nof_symbols());

  // Calculate the distance between the 2 slot symbol points in symbols.

  // Calculate the distance between the 2 slot symbol points in symbols.
  int diff = calculate_slot_symbol_point_distance(ota_point, symbol_point);
  // Update earliest and latest
  // Update earliest and latest
  statistics.update_rx_timing_stats(diff);

  // Late detected.

  // Late detected.
  if (int symb_end = timing_parameters.sym_end; diff > symb_end) {
    statistics.increment_late_counter();


    return;
  }

  // Early detected.

  // Early detected.
  if (int symb_start = timing_parameters.sym_start; diff < symb_start) {
    statistics.increment_early_counter();


    return;
  }

  // On time detected.

  // On time detected.
  statistics.increment_on_time_counter();
}


void rx_window_checker::collect_metrics(received_messages_metrics& metrics)
{
  statistics.collect_metrics(metrics);
}


void rx_window_checker::rx_window_checker_statistics::collect_metrics(received_messages_metrics& metrics)
{
  // Fetch the data.
  // Fetch the data.
  uint64_t current_nof_on_time = nof_on_time_messages();
  uint64_t current_nof_late    = nof_late_messages();
  uint64_t current_nof_early   = nof_early_messages();

  // Calculate the difference since last print.

  // Calculate the difference since last print.
  metrics.nof_on_time_messages = current_nof_on_time - last_on_time_value_printed;
  metrics.nof_early_messages   = current_nof_early - last_early_value_printed;
  metrics.nof_late_messages    = current_nof_late - last_late_value_printed;
  metrics.earliest_rx_msg_in_symbols =
      earliest_packet_in_symbols.exchange(EARLIEST_INITIAL_VALUE, std::memory_order_relaxed);
  metrics.latest_rx_msg_in_symbols = latest_packet_in_symbols.exchange(0, std::memory_order_relaxed);

  // Correct the earliest metrics in case no packets were received.

  // Correct the earliest metrics in case no packets were received.
  metrics.earliest_rx_msg_in_symbols =
      (metrics.earliest_rx_msg_in_symbols == EARLIEST_INITIAL_VALUE) ? 0 : metrics.earliest_rx_msg_in_symbols;

  // Update last print.

  // Update last print.
  last_late_value_printed    = current_nof_late;
  last_early_value_printed   = current_nof_early;
  last_on_time_value_printed = current_nof_on_time;
}


void rx_window_checker::rx_window_checker_statistics::update_rx_timing_stats(int32_t value)
{
  update_minmax(value, latest_packet_in_symbols, earliest_packet_in_symbols);
}
