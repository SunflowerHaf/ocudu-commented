// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Element-wise product of two vectors.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/prod.h  (64 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Element-wise product of two vectors.

#pragma once


#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

///@{
/// \brief Element-wise product of two vectors.
/// \param[out]  z Output vector.
/// \param[in]   x First input vector.
/// \param[in]   y Second input vector.
/// \warning An assertion is triggered if input and output vectors have different sizes.

///@{
/// \brief Element-wise product of two vectors.
/// \param[out]  z Output vector.
/// \param[in]   x First input vector.
/// \param[in]   y Second input vector.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void prod(span<cf_t> z, span<const cf_t> x, span<const cf_t> y);
void prod(span<cf_t> z, span<const cf_t> x, span<const float> y);
void prod(span<cf_t> z, span<const float> x, span<const cf_t> y);
void prod(span<cbf16_t> z, span<const cf_t> x, span<const cf_t> y);
void prod(span<float> z, span<const float> x, span<const float> y);
void prod(span<int16_t> z, span<const int16_t> x, span<const int16_t> y);
///@}

/// \brief Element-wise product of two vectors, after taking the complex conjugate of the second one.
///
/// \param[out]  z Output vector.
/// \param[in]   x First input vector.
/// \param[in]   y Second input vector - conjugated before multiplication.
/// \warning An assertion is triggered if input and output vectors have different sizes.
///@}

/// \brief Element-wise product of two vectors, after taking the complex conjugate of the second one.
///
/// \param[out]  z Output vector.
/// \param[in]   x First input vector.
/// \param[in]   y Second input vector - conjugated before multiplication.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void prod_conj(span<cf_t> z, span<const cf_t> x, span<const cf_t> y);

/// \brief Multiplies a given signal by a complex exponential.
///
/// \param[out] out           Resultant complex samples.
/// \param[in]  in            Input complex samples.
/// \param[in]  norm_freq     Normalized frequency.
/// \param[in]  initial_phase Initial phase in radians.
/// \warning An assertion is triggered if input and output vectors have different sizes.

/// \brief Multiplies a given signal by a complex exponential.
///
/// \param[out] out           Resultant complex samples.
/// \param[in]  in            Input complex samples.
/// \param[in]  norm_freq     Normalized frequency.
/// \param[in]  initial_phase Initial phase in radians.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void prod_cexp(span<cf_t> out, span<const cf_t> in, float norm_freq, float initial_phase = 0.0F);

/// \brief Multiplies a given signal by a complex exponential.
///
/// \param[out] out           Resultant complex samples.
/// \param[in]  in            Input complex samples.
/// \param[in]  norm_freq     Normalized frequency.
/// \param[in]  initial_phase Initial phase in radians.
/// \warning An assertion is triggered if input and output vectors have different sizes.

/// \brief Multiplies a given signal by a complex exponential.
///
/// \param[out] out           Resultant complex samples.
/// \param[in]  in            Input complex samples.
/// \param[in]  norm_freq     Normalized frequency.
/// \param[in]  initial_phase Initial phase in radians.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void prod_cexp(span<cbf16_t> out, span<const cbf16_t> in, float norm_freq, float initial_phase = 0.0F);

/// \brief Multiplies a given signal by a complex exponential.
///
/// \param[out] out           Resultant complex samples.
/// \param[in]  in            Input complex samples.
/// \param[in]  norm_freq     Normalized frequency.
/// \param[in]  initial_phase Initial phase in radians.
/// \warning An assertion is triggered if input and output vectors have different sizes.

/// \brief Multiplies a given signal by a complex exponential.
///
/// \param[out] out           Resultant complex samples.
/// \param[in]  in            Input complex samples.
/// \param[in]  norm_freq     Normalized frequency.
/// \param[in]  initial_phase Initial phase in radians.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void prod_cexp(span<cbf16_t> out, span<const cf_t> in, float norm_freq, float initial_phase = 0.0F);


} // namespace ocuduvec
} // namespace ocudu
