// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/transmitter/helpers.h  (34 lines)
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


#include "ocudu/ofh/transmitter/ofh_transmitter_configuration.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {
namespace ofh {

/// Returns the maximum value between the minimum T1a values in symbol units.

/// Returns the maximum value between the minimum T1a values in symbol units.
inline unsigned get_biggest_min_tx_parameter(const tx_window_timing_parameters& tx_timing_params)
{
  return std::max({tx_timing_params.sym_cp_dl_end, tx_timing_params.sym_cp_ul_end, tx_timing_params.sym_up_dl_end});
}

/// Returns duration of the OFH processing plus the transmission window in symbol units.

/// Returns duration of the OFH processing plus the transmission window in symbol units.
inline unsigned calculate_nof_symbols_before_ota(cyclic_prefix                     cp,
                                                 subcarrier_spacing                scs,
                                                 std::chrono::microseconds         processing_time,
                                                 const tx_window_timing_parameters tx_timing_params)
{
  unsigned nof_symbols = get_nsymb_per_slot(cp);
  auto     symbol_duration_ns =
      std::chrono::duration<double, std::nano>(1e6 / (nof_symbols * get_nof_slots_per_subframe(scs)));
  unsigned processing_time_in_symbols = std::max(1u, unsigned(std::floor(processing_time / symbol_duration_ns)));


  return processing_time_in_symbols + get_biggest_min_tx_parameter(tx_timing_params);
}


} // namespace ofh
} // namespace ocudu
