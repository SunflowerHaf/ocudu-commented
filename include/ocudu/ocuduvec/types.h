// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/types.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/adt/complex.h"
#include "ocudu/adt/span.h"
#include "ocudu/support/ocudu_assert.h"
#include <cstdint>

/// \brief The ocuduvec library provides optimized SIMD commonly used operations.
///
/// The supported vector data types are:
/// - ocudu::span<cf_t>: For complex float vectors
/// - ocudu::span<float>: For float vectors
/// - ocudu::span<int16_t>: For signed 16 bit integer vectors
/// - ocudu::span<int8_t>: For signed 8 bit integer vectors
/// - ocudu::span<uint8_t>: For unsigned 8 bit integer vectors
///
/// To make the span constant use ocudu::span<const T>.

/// Asserts that both objects have the same size.

/// \brief The ocuduvec library provides optimized SIMD commonly used operations.
///
/// The supported vector data types are:
/// - ocudu::span<cf_t>: For complex float vectors
/// - ocudu::span<float>: For float vectors
/// - ocudu::span<int16_t>: For signed 16 bit integer vectors
/// - ocudu::span<int8_t>: For signed 8 bit integer vectors
/// - ocudu::span<uint8_t>: For unsigned 8 bit integer vectors
///
/// To make the span constant use ocudu::span<const T>.

/// Asserts that both objects have the same size.
#define ocudu_ocuduvec_assert_size(X, Y)                                                                               \
  ocudu_assert(                                                                                                        \
      X.size() == Y.size(), "The size " #X " (i.e., {}) and " #Y " (i.e., {}) must be equal.", X.size(), Y.size())
