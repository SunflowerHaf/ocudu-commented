// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Product of a vector by a scalar.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/sc_prod.h  (30 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Product of a vector by a scalar.

#pragma once


#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

///@{
/// \brief Product of a vector by a scalar.
/// \param[out]  z Output vector.
/// \param[in]   x Input vector.
/// \param[in]   h Scalar factor.
/// \warning An assertion is triggered if the input and output vectors have different sizes.

///@{
/// \brief Product of a vector by a scalar.
/// \param[out]  z Output vector.
/// \param[in]   x Input vector.
/// \param[in]   h Scalar factor.
/// \warning An assertion is triggered if the input and output vectors have different sizes.
void sc_prod(span<cf_t> z, span<const cf_t> x, cf_t h);
void sc_prod(span<cbf16_t> z, span<const cbf16_t> x, cf_t h);
void sc_prod(span<cbf16_t> z, span<const cbf16_t> x, float h);
void sc_prod(span<cf_t> z, span<const cf_t> x, float h);
void sc_prod(span<float> z, span<const float> x, float h);
void sc_prod(span<int16_t> z, span<const int16_t> x, int16_t h);
void sc_prod(span<cbf16_t> z, span<const cf_t> x, float h);
///@}

///@}

} // namespace ocuduvec
} // namespace ocudu
