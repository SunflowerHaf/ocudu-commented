// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief AVX2 support for OFH Compression algorithms.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ofh/compression/avx2_helpers.h  (111 lines)
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
/// \brief AVX2 support for OFH Compression algorithms.

#pragma once


#include "ocudu/adt/span.h"
#include <immintrin.h>


namespace ocudu {
namespace ofh {
namespace mm256 {

/// Type of AVX2 intrinsic calculating min or max values between two vectors.

/// Type of AVX2 intrinsic calculating min or max values between two vectors.
using _mm256_comparator = __m256i (*)(__m256i a, __m256i b);

/// \brief Finds the maximum (or minimum) 16bit sample in each of the two input resource blocks, returns its absolute
/// value.
///
/// Finds absolute maximum (or minimum, depending on the comparator passed as the template argument) values
/// for each of the two RBs passed in a three AVX2 registers.
///
/// Registers are evenly divided between two RBs so that IQ samples of each RB occupy one 128bit lane.
/// The following diagram shows the input format. Here RBx stands for one unique RE (a pair of IQ samples, 32 bits long)
/// pertaining to a respective RB:
/// |       |         |         |         |         |
/// | ----- | ------- | ------- | ------- | ------- |
/// | \c v0_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
/// | \c v1_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
/// | \c v2_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
///
/// The function first performs vertical min/max search across the three registers (comparing 16bit samples), then
/// horizontal min/max across elements in each 128bit lane of the resulting vector. Finally, the function takes the
/// absolute value of the two 16bit samples computed thus far and stores them in the output span.
///
/// \tparam    COMPARE  AVX2 intrinsic used for comparison, either \c mm256_min_epi16 or \c _mm256_max_epi16.
/// \tparam    OFFSET   Subtracts an offset to the resultant absolute value.
/// \param[out] abs     A span of two absolute values of max (or min) samples in each of the two input RBs.
/// \param[in] v0_epi16 AVX2 register storing first four IQ pairs of each of the two RB.
/// \param[in] v1_epi16 AVX2 register storing second four IQ pairs of each of the two RB.
/// \param[in] v2_epi16 AVX2 register storing last four IQ pairs of each of the two RB.

/// \brief Finds the maximum (or minimum) 16bit sample in each of the two input resource blocks, returns its absolute
/// value.
///
/// Finds absolute maximum (or minimum, depending on the comparator passed as the template argument) values
/// for each of the two RBs passed in a three AVX2 registers.
///
/// Registers are evenly divided between two RBs so that IQ samples of each RB occupy one 128bit lane.
/// The following diagram shows the input format. Here RBx stands for one unique RE (a pair of IQ samples, 32 bits long)
/// pertaining to a respective RB:
/// |       |         |         |         |         |
/// | ----- | ------- | ------- | ------- | ------- |
/// | \c v0_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
/// | \c v1_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
/// | \c v2_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
///
/// The function first performs vertical min/max search across the three registers (comparing 16bit samples), then
/// horizontal min/max across elements in each 128bit lane of the resulting vector. Finally, the function takes the
/// absolute value of the two 16bit samples computed thus far and stores them in the output span.
///
/// \tparam    COMPARE  AVX2 intrinsic used for comparison, either \c mm256_min_epi16 or \c _mm256_max_epi16.
/// \tparam    OFFSET   Subtracts an offset to the resultant absolute value.
/// \param[out] abs     A span of two absolute values of max (or min) samples in each of the two input RBs.
/// \param[in] v0_epi16 AVX2 register storing first four IQ pairs of each of the two RB.
/// \param[in] v1_epi16 AVX2 register storing second four IQ pairs of each of the two RB.
/// \param[in] v2_epi16 AVX2 register storing last four IQ pairs of each of the two RB.
template <_mm256_comparator COMPARE, unsigned OFFSET>
inline void find_rbs_abs_min_max_values(span<uint16_t> abs, __m256i v0_epi16, __m256i v1_epi16, __m256i v2_epi16)
{
  // Find vertical min/max across every 3 16bit values in each resource block.
  // Find vertical min/max across every 3 16bit values in each resource block.
  __m256i cmp_8val_epi16 = COMPARE(COMPARE(v0_epi16, v1_epi16), v2_epi16);
  // Now 16bit vector elements look as follows:
  // [max(I00, I08, I04), max(Q00, Q08, Q04), max(I01, I09, I05), max(Q01, Q09, Q05), ...].

  // Swap 64bit words inside 128bit lanes and find 4 min/max values.
  // Now 16bit vector elements look as follows:
  // [max(I00, I08, I04), max(Q00, Q08, Q04), max(I01, I09, I05), max(Q01, Q09, Q05), ...].

  // Swap 64bit words inside 128bit lanes and find 4 min/max values.
  __m256i cmp_8val_swp_epi16 = _mm256_shuffle_epi32(cmp_8val_epi16, 0x4e);
  __m256i cmp_4val_epi16     = COMPARE(cmp_8val_epi16, cmp_8val_swp_epi16);
  // Swap 32bit words and find 2 min/max values.
  // Swap 32bit words and find 2 min/max values.
  __m256i cmp_4val_swp_epi16 = _mm256_shuffle_epi32(cmp_4val_epi16, 0x1b);
  __m256i cmp_2val_epi16     = COMPARE(cmp_4val_epi16, cmp_4val_swp_epi16);
  // Swap 16bit words and find final min/max values for each RB.
  // Swap 16bit words and find final min/max values for each RB.
  const __m256i shuffle_mask = _mm256_setr_epi8(
      2, 3, 0, 1, 6, 7, 4, 5, 8, 9, 10, 11, 14, 15, 12, 13, 2, 3, 0, 1, 6, 7, 4, 5, 8, 9, 10, 11, 14, 15, 12, 13);
  __m256i cmp_2val_swp_epi16 = _mm256_shuffle_epi8(cmp_2val_epi16, shuffle_mask);
  __m256i cmp_rb0_rb1_epi16  = COMPARE(cmp_2val_epi16, cmp_2val_swp_epi16);
  __m256i cmp_rb0_rb1_epu16  = _mm256_abs_epi16(cmp_rb0_rb1_epi16);


  if (OFFSET != 0) {
    cmp_rb0_rb1_epu16 = _mm256_subs_epu16(cmp_rb0_rb1_epu16, _mm256_set1_epi16(OFFSET));
  }

  // Extract absolute minimum/maximum values for each RB.

  // Extract absolute minimum/maximum values for each RB.
  abs[0] = _mm256_extract_epi16(cmp_rb0_rb1_epu16, 0);
  abs[1] = _mm256_extract_epi16(cmp_rb0_rb1_epu16, 8);
}

/// \brief Finds maximum absolute value across 16bit IQ samples in each of the two input resource blocks passed in three
/// AVX2 registers.
///
/// The content of the three input AVX2 registers is represented in the table below. Here RBx means one unique RE
/// (pair of IQ samples, 32 bits long) pertaining to a respective RB:
/// |       |         |         |         |         |
/// | ----- | ------- | ------- | ------- | ------- |
/// | \c rb0_epi16:  | RB0 RB0 | RB0 RB0 | RB0 RB0 | RB0 RB0 |
/// | \c rb01_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
/// | \c rb1_epi16:  | RB1 RB1 | RB1 RB1 | RB1 RB1 | RB1 RB1 |
///
/// \param[out] max_abs   A span of two maximum absolute values in the two input RBs.
/// \param[in] rb0_epi16  AVX2 register storing 16bit IQ pairs of the first RB.
/// \param[in] rb01_epi16 AVX2 register storing 16bit IQ pairs of the first and second RBs.
/// \param[in] rb1_epi16  AVX2 register storing 16bit IQ pairs of the second RB.

/// \brief Finds maximum absolute value across 16bit IQ samples in each of the two input resource blocks passed in three
/// AVX2 registers.
///
/// The content of the three input AVX2 registers is represented in the table below. Here RBx means one unique RE
/// (pair of IQ samples, 32 bits long) pertaining to a respective RB:
/// |       |         |         |         |         |
/// | ----- | ------- | ------- | ------- | ------- |
/// | \c rb0_epi16:  | RB0 RB0 | RB0 RB0 | RB0 RB0 | RB0 RB0 |
/// | \c rb01_epi16: | RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 |
/// | \c rb1_epi16:  | RB1 RB1 | RB1 RB1 | RB1 RB1 | RB1 RB1 |
///
/// \param[out] max_abs   A span of two maximum absolute values in the two input RBs.
/// \param[in] rb0_epi16  AVX2 register storing 16bit IQ pairs of the first RB.
/// \param[in] rb01_epi16 AVX2 register storing 16bit IQ pairs of the first and second RBs.
/// \param[in] rb1_epi16  AVX2 register storing 16bit IQ pairs of the second RB.
inline void calculate_max_abs(span<unsigned> max_abs, __m256i rb0_epi16, __m256i rb01_epi16, __m256i rb1_epi16)
{
  std::array<uint16_t, 2> abs_min_values;
  std::array<uint16_t, 2> abs_max_values;

  // Reorganize vectors to be able to vertically compare 16bit samples pertaining to the same resource block:
  // [ RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 ]
  // [ RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 ]
  // [ RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 ]

  // Reorganize vectors to be able to vertically compare 16bit samples pertaining to the same resource block:
  // [ RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 ]
  // [ RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 ]
  // [ RB0 RB0 | RB0 RB0 | RB1 RB1 | RB1 RB1 ]
  __m256i v0_epi16 = _mm256_permute2f128_si256(rb0_epi16, rb1_epi16, 0x20);
  __m256i v2_epi16 = _mm256_permute2f128_si256(rb0_epi16, rb1_epi16, 0x31);
  __m256i v1_epi16 = rb01_epi16;


  find_rbs_abs_min_max_values<_mm256_min_epi16, 1>(abs_min_values, v0_epi16, v1_epi16, v2_epi16);
  find_rbs_abs_min_max_values<_mm256_max_epi16, 0>(abs_max_values, v0_epi16, v1_epi16, v2_epi16);


  max_abs[0] = std::max<unsigned>(abs_max_values[0], abs_min_values[0]);
  max_abs[1] = std::max<unsigned>(abs_max_values[1], abs_min_values[1]);
}


} // namespace mm256
} // namespace ofh
} // namespace ocudu
