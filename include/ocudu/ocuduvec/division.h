// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/division.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

/// \brief Element-wise division between two sequences.
///
/// The result of the division is zero if the numerator or the denominator is abnormal.
///
/// \param[out] result      Division result.
/// \param[in]  numerator   Division numerator.
/// \param[in]  denominator Division denominator.
/// \remark An assertion is triggered if \c numerator, \c denominator, and \c result do not have the same number of
/// elements.

/// \brief Element-wise division between two sequences.
///
/// The result of the division is zero if the numerator or the denominator is abnormal.
///
/// \param[out] result      Division result.
/// \param[in]  numerator   Division numerator.
/// \param[in]  denominator Division denominator.
/// \remark An assertion is triggered if \c numerator, \c denominator, and \c result do not have the same number of
/// elements.
void divide(span<float> result, span<const float> numerator, span<const float> denominator);


} // namespace ocuduvec
} // namespace ocudu
