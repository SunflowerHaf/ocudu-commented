// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief NEON support for OFH Compression algorithms.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/neon_helpers.h  (59 lines)
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

/// \file
/// \brief NEON support for OFH Compression algorithms.

#pragma once


#include <algorithm>
#include <arm_neon.h>
#include <cstdint>


namespace ocudu {
namespace ofh {
namespace neon {

/// \brief Determines BFP exponent for the resource block passed in a vector of three NEON registers.
///
/// The content of the three NEON registers is represented in the table below. Here REx stands for one component of
/// a unique resource element (16 bits long):
/// |       |         |         |           |         |
/// | ----- | ------- | ------- | --------- | ------- |
/// | \c reg0: | RE0 RE0 | RE1 RE1 | RE2 RE2   | RE3 RE3 |
/// | \c reg1: | RE4 RE4 | RE5 RE5 | RE6 RE6   | RE7 RE7 |
/// | \c reg2: | RE8 RE8 | RE9 RE9 | RE10 RE10 | RE11 RE11 |
///
/// \param[in] vec_s16x3  Vector of three NEON registers storing 16bit IQ pairs of the resource block.
/// \param[in] data_width Compressed samples bit width.
///
/// \return Calculated exponent value.

/// \brief Determines BFP exponent for the resource block passed in a vector of three NEON registers.
///
/// The content of the three NEON registers is represented in the table below. Here REx stands for one component of
/// a unique resource element (16 bits long):
/// |       |         |         |           |         |
/// | ----- | ------- | ------- | --------- | ------- |
/// | \c reg0: | RE0 RE0 | RE1 RE1 | RE2 RE2   | RE3 RE3 |
/// | \c reg1: | RE4 RE4 | RE5 RE5 | RE6 RE6   | RE7 RE7 |
/// | \c reg2: | RE8 RE8 | RE9 RE9 | RE10 RE10 | RE11 RE11 |
///
/// \param[in] vec_s16x3  Vector of three NEON registers storing 16bit IQ pairs of the resource block.
/// \param[in] data_width Compressed samples bit width.
///
/// \return Calculated exponent value.
inline uint8_t determine_bfp_exponent(int16x8x3_t vec_s16x3, unsigned data_width)
{
  // Max allowed exponent (accounts for the extra bit used for sign).
  // Max allowed exponent (accounts for the extra bit used for sign).
  const uint16_t max_lzcnt   = (16 - data_width) + 1;
  uint16x4_t     vec_max_lzc = vdup_n_u16(max_lzcnt);

  // Calculate maximum value in the resource block (following instructions perform three pairwise comparisons between
  // the three registers and then find a maximum value across resulting vector).

  // Calculate maximum value in the resource block (following instructions perform three pairwise comparisons between
  // the three registers and then find a maximum value across resulting vector).
  int16x8_t tmp_max_s16 = vmaxq_s16(vmaxq_s16(vec_s16x3.val[0], vec_s16x3.val[1]), vec_s16x3.val[2]);
  int16_t   max_s16     = vmaxvq_s16(tmp_max_s16);

  // Calculate minimum value in the resource block (following instructions perform three pairwise comparisons between
  // the three registers and then find a minimum value across resulting vector).

  // Calculate minimum value in the resource block (following instructions perform three pairwise comparisons between
  // the three registers and then find a minimum value across resulting vector).
  int16x8_t tmp_min_s16 = vminq_s16(vminq_s16(vec_s16x3.val[0], vec_s16x3.val[1]), vec_s16x3.val[2]);
  int16_t   min_s16     = vminvq_s16(tmp_min_s16);

  // Calculate maximum absolute value.

  // Calculate maximum absolute value.
  uint16_t max_abs = std::max(std::abs(max_s16), std::abs(min_s16) - 1);

  // Calculate number of leading zeros.

  // Calculate number of leading zeros.
  uint16x4_t lzc_u16 = vclz_u16(vdup_n_u16(max_abs));

  // Calculate exponent.

  // Calculate exponent.
  return static_cast<uint8_t>(vget_lane_u16(vqsub_u16(vec_max_lzc, lzc_u16), 0));
}


} // namespace neon
} // namespace ofh
} // namespace ocudu
