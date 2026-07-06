// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Cumulative sum of sequences.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/accumulate.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Cumulative sum of sequences.

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"
#include <numeric>


namespace ocudu {
namespace ocuduvec {

///@{
/// \brief Cumulative sum of a sequence.
/// \param[in] x  Input sequence.
/// \return The sum of all elements of the input sequence.

///@{
/// \brief Cumulative sum of a sequence.
/// \param[in] x  Input sequence.
/// \return The sum of all elements of the input sequence.
float accumulate(span<const float> x);


inline cf_t accumulate(span<const cf_t> x)
{
  return std::accumulate(x.begin(), x.end(), cf_t());
}
///@}

///@}

} // namespace ocuduvec
} // namespace ocudu
