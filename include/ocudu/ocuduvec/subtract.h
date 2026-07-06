// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Difference of two vectors.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/subtract.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Difference of two vectors.

#pragma once


#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

///@{
/// \brief Difference of two vectors.
/// \param[out]  z Output vector.
/// \param[in]   x Minuend input vector.
/// \param[in]   y Subtrahend input vector.
/// \warning An assertion is triggered if input and output vectors have different sizes.

///@{
/// \brief Difference of two vectors.
/// \param[out]  z Output vector.
/// \param[in]   x Minuend input vector.
/// \param[in]   y Subtrahend input vector.
/// \warning An assertion is triggered if input and output vectors have different sizes.
void subtract(span<cf_t> z, span<const cf_t> x, span<const cf_t> y);
void subtract(span<float> z, span<const float> x, span<const float> y);
void subtract(span<int16_t> z, span<const int16_t> x, span<const int16_t> y);
void subtract(span<int8_t> z, span<const int8_t> x, span<const int8_t> y);
///@}

///@}

} // namespace ocuduvec
} // namespace ocudu
