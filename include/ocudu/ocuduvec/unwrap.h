// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Phase angle unwrapping declarations.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/unwrap.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Phase angle unwrapping declarations.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"


namespace ocudu {
namespace ocuduvec {

/// \brief Computes the unwrapped arguments (phase angles) of a list of complex numbers.
///
/// \param[out] arguments     Output list of unwrapped arguments.
/// \param[in]  cplx_numbers  Input list of complex numbers.
///
/// \warning The input and output lists should have the same length.
/// \warning The memory allocated for input and output should be disjoint.

/// \brief Computes the unwrapped arguments (phase angles) of a list of complex numbers.
///
/// \param[out] arguments     Output list of unwrapped arguments.
/// \param[in]  cplx_numbers  Input list of complex numbers.
///
/// \warning The input and output lists should have the same length.
/// \warning The memory allocated for input and output should be disjoint.
void unwrap_arguments(span<float> arguments, span<const cf_t> cplx_numbers);


} // namespace ocuduvec
} // namespace ocudu
