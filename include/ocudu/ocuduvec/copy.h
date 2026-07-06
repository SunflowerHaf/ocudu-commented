// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Sequence copy.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/copy.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Sequence copy.

#pragma once


#include "ocudu/ocuduvec/type_traits.h"
#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

/// \brief Copies a sequence into a different object.
///
/// \tparam     T    Type of the destination sequence. (must be compatible with a span).
/// \tparam     U    Type of the original sequence (must be compatible with a span).
/// \param[out] dst  Copied sequence.
/// \param[in]  src  Original sequence.

/// \brief Copies a sequence into a different object.
///
/// \tparam     T    Type of the destination sequence. (must be compatible with a span).
/// \tparam     U    Type of the original sequence (must be compatible with a span).
/// \param[out] dst  Copied sequence.
/// \param[in]  src  Original sequence.
template <typename T, typename U>
void copy(T&& dst, const U& src)
{
  static_assert(is_span_compatible<T>::value, "Template type is not compatible with a span");
  static_assert(is_span_compatible<U>::value, "Template type is not compatible with a span");
  ocudu_ocuduvec_assert_size(dst, src);


  std::copy(src.begin(), src.end(), dst.begin());
}


} // namespace ocuduvec
} // namespace ocudu
