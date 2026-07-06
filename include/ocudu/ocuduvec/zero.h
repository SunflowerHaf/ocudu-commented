// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/zero.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/ocuduvec/type_traits.h"
#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

/// \brief Sets all elements of a sequence to zero.
///
/// \tparam T Type of the sequence container, must be span-compatible.
/// \param  x Sequence container.

/// \brief Sets all elements of a sequence to zero.
///
/// \tparam T Type of the sequence container, must be span-compatible.
/// \param  x Sequence container.
template <typename T>
void zero(T&& x)
{
  static_assert(is_span_compatible<T>::value, "Template type is not compatible with a span.");
  std::fill(x.begin(), x.end(), 0);
}


} // namespace ocuduvec
} // namespace ocudu
