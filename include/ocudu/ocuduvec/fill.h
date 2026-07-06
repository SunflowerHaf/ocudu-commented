// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/fill.h  (25 lines)
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

/// \brief Sets all elements of a sequence to a given value.
///
/// \tparam T      Type of the sequence container, must be span-compatible.
/// \param  x      Sequence container.
/// \param  value  Value the sequence is set to. Must be compatible with the element type of the sequence.

/// \brief Sets all elements of a sequence to a given value.
///
/// \tparam T      Type of the sequence container, must be span-compatible.
/// \param  x      Sequence container.
/// \param  value  Value the sequence is set to. Must be compatible with the element type of the sequence.
template <typename T>
void fill(T&& x, detail::value_type_of_t<T> value)
{
  static_assert(is_span_compatible<T>::value, "Template type is not compatible with a span");
  std::fill(x.begin(), x.end(), value);
}


} // namespace ocuduvec
} // namespace ocudu
