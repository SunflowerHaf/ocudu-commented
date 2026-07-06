// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/support/context_repository_helpers.h  (35 lines)
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


#include "ocudu/ran/slot_point.h"


namespace ocudu {
namespace ofh {

/// System frame number maximum value in the Open Fronthaul repositories.

/// System frame number maximum value in the Open Fronthaul repositories.
constexpr unsigned SFN_MAX_VALUE = 1U << 8;

/// \brief Calculates the size of the repository using the given parameters.
///
/// This function will find the minimum divisible value of the maximum number of slots that Open Fronthaul supports.

/// \brief Calculates the size of the repository using the given parameters.
///
/// This function will find the minimum divisible value of the maximum number of slots that Open Fronthaul supports.
constexpr unsigned calculate_repository_size(subcarrier_spacing scs, unsigned minimum_repo_size)
{
  for (unsigned nof_slots = SFN_MAX_VALUE * get_nof_slots_per_subframe(scs) * NOF_SUBFRAMES_PER_FRAME;
       nof_slots % minimum_repo_size != 0;
       ++minimum_repo_size) {
  }


  return minimum_repo_size;
}

/// Calculates the repository local index for the given slot and repository size.

/// Calculates the repository local index for the given slot and repository size.
constexpr unsigned calculate_repository_index(slot_point slot, unsigned repo_size)
{
  slot_point entry_slot(slot.numerology(), slot.sfn() % SFN_MAX_VALUE, slot.slot_index());
  return entry_slot.system_slot() % repo_size;
}


} // namespace ofh
} // namespace ocudu
