// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Sum of two vectors.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/add.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Sum of two vectors.

#pragma once


#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

///@{
/// \brief Sum of two vectors.
/// \param[out]  z Output vector.
/// \param[in]   x First input vector.
/// \param[in]   y Second input vector.
/// \warning An assertion is triggered if input and output vectors have different sizes.

///@{
/// \brief Sum of two vectors.
/// \param[out]  z Output vector.
/// \param[in]   x First input vector.
/// \param[in]   y Second input vector.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void add(span<cf_t> z, span<const cf_t> x, span<const cf_t> y);
void add(span<cf_t> z, span<const cf_t> x, span<const cbf16_t> y);
void add(span<float> z, span<const float> x, span<const float> y);
void add(span<int16_t> z, span<const int16_t> x, span<const int16_t> y);
void add(span<int8_t> z, span<const int8_t> x, span<const int8_t> y);
///@}

///@}

} // namespace ocuduvec
} // namespace ocudu
