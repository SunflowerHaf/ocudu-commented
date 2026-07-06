// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ocuduvec/division.cpp  (41 lines)
//
// LIBRARY: lib/ocuduvec
// Custom SIMD-accelerated vector types and compile-time utilities. Provides ocuduvec types (aligned buffers, SIMD intrinsic wrappers) used throughout the PHY for DSP operations (FFT, channel estimation, modulation). Eliminates dependency on external SIMD libraries for basic operations.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/ocuduvec/division.h"
#include "ocudu/ocuduvec/simd.h"


using namespace ocudu;
using namespace ocuduvec;


static void divide_fff_simd(float* result, const float* num, const float* den, std::size_t len)
{
  std::size_t i = 0;


#if OCUDU_SIMD_F_SIZE
  for (; i + OCUDU_SIMD_F_SIZE < len + 1; i += OCUDU_SIMD_F_SIZE) {
    simd_f_t num_simd = ocudu_simd_f_loadu(num + i);
    simd_f_t den_simd = ocudu_simd_f_loadu(den + i);


    simd_f_t r = ocudu_simd_f_mul(num_simd, ocudu_simd_f_rcp(den_simd));


    ocudu_simd_f_storeu(result + i, r);
  }
#endif


  for (; i != len; ++i) {
    if (!std::isnormal(num[i]) || !std::isnormal(den[i])) {
      result[i] = 0.0F;
      continue;
    }


    result[i] = num[i] / den[i];
  }
}


void ocudu::ocuduvec::divide(span<float> result, span<const float> numerator, span<const float> denominator)
{
  ocudu_ocuduvec_assert_size(result, numerator);
  ocudu_ocuduvec_assert_size(result, denominator);


  divide_fff_simd(result.data(), numerator.data(), denominator.data(), result.size());
}
