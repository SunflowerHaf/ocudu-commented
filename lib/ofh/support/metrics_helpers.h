// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/metrics_helpers.h  (57 lines)
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


#include "ocudu/adt/noop_functor.h"
#include <atomic>
#include <chrono>
#include <memory>


namespace ocudu {
namespace ofh {


template <typename T>
inline void update_minmax(T new_value, std::atomic<T>& max, std::atomic<T>& min)
{
  auto current_min = min.load(std::memory_order_relaxed);
  auto current_max = max.load(std::memory_order_relaxed);
  while (new_value < current_min && !min.compare_exchange_weak(current_min, new_value)) {
  }
  while (new_value > current_max && !max.compare_exchange_weak(current_max, new_value)) {
  }
}

/// Helper class measuring execution time if metrics are enabled.

/// Helper class measuring execution time if metrics are enabled.
class time_execution_measurer
{
public:
  /// The constructor starts measuring execution time of a code-block if metrics are enabled, or does nothing otherwise.
  /// The constructor starts measuring execution time of a code-block if metrics are enabled, or does nothing otherwise.
  explicit time_execution_measurer(bool is_enabled_) : is_enabled(is_enabled_)
  {
    if (is_enabled) {
      start_tp = std::chrono::high_resolution_clock::now();
    }
  }

  /// Calculates and returns the execution time of a code-block if metrics are enabled, or does nothing otherwise.

  /// Calculates and returns the execution time of a code-block if metrics are enabled, or does nothing otherwise.
  std::chrono::nanoseconds stop()
  {
    if (is_enabled) {
      auto stop_tp = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::nanoseconds>(stop_tp - start_tp);
    }


    return {};
  }


private:
  /// The measurer measures the execution time if the flag is set to true, otherwise no operation is performed.
  /// The measurer measures the execution time if the flag is set to true, otherwise no operation is performed.
  const bool is_enabled;

  /// Time point marking the start of a new measurement.

  /// Time point marking the start of a new measurement.
  std::chrono::high_resolution_clock::time_point start_tp = {};
};


} // namespace ofh
} // namespace ocudu
