// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

/// \file
/// \brief Clipping functions.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ocuduvec/clip.h  (72 lines)
//
// INTERFACE HEADER — include/ocudu/ocuduvec
// SIMD vector type public interfaces: the ocuduvec types used for aligned memory, SIMD intrinsic wrappers, and compile-time type traits for PHY DSP code. Exposes the interface layer so upper-PHY code can be written portably and the implementation selects AVX-512/AVX2/NEON/generic at link time.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

/// \file
/// \brief Clipping functions.

#pragma once


#include "ocudu/ocuduvec/types.h"


namespace ocudu {
namespace ocuduvec {

/// \brief Clips a span of floats.
///
/// Limits the amplitude of the samples to the specified clipping threshold. The clipping process is defined as
/// \f[
/// y[n] =
/// \begin{cases}
/// x[n],&  \lvert x[n] \rvert  \leq T_c \\ T_c,& x[n] > T_c \\ -T_c,& x[n] < -T_c
/// \end{cases}
/// \f]
/// Where \f$ T_c \f$ is the clipping threshold.
///
/// \param [out] y Output Span.
/// \param [in]  x Input Span.
/// \param [in]  threshold Clipping threshold.
/// \return The number of clipped samples.

/// \brief Clips a span of floats.
///
/// Limits the amplitude of the samples to the specified clipping threshold. The clipping process is defined as
/// \f[
/// y[n] =
/// \begin{cases}
/// x[n],&  \lvert x[n] \rvert  \leq T_c \\ T_c,& x[n] > T_c \\ -T_c,& x[n] < -T_c
/// \end{cases}
/// \f]
/// Where \f$ T_c \f$ is the clipping threshold.
///
/// \param [out] y Output Span.
/// \param [in]  x Input Span.
/// \param [in]  threshold Clipping threshold.
/// \return The number of clipped samples.
unsigned clip(span<float> y, span<const float> x, float threshold);

/// \brief Clips the real and imaginary components of a complex span.
///
/// Limits the amplitude of the real and imaginary components of the input samples to the specified clipping threshold.
/// The clipping process is defined as
/// \f[
/// \Re(y[n]) =
/// \begin{cases}
/// \Re \{x[n]\},&  \lvert \Re\{x[n]\} \rvert  \leq T_c \\ T_c,& \Re\{x[n]\} > T_c \\ -T_c,& \Re \{x[n]\} < -T_c
/// \end{cases}
/// \Im(y[n]) =
/// \begin{cases}
/// \Im \{x[n]\},&  \lvert \Im\{x[n]\} \rvert  \leq T_c \\ T_c,& \Im\{x[n]\} > T_c \\ -T_c,& \Im \{x[n]\} < -T_c
/// \end{cases}
/// \f]
///
/// Where \f$ T_c \f$ is the clipping threshold.
///
/// \param [out] y Output Span.
/// \param [in]  x Input Span.
/// \param [in]  threshold Clipping threshold.
/// \return The number of clipped samples.

/// \brief Clips the real and imaginary components of a complex span.
///
/// Limits the amplitude of the real and imaginary components of the input samples to the specified clipping threshold.
/// The clipping process is defined as
/// \f[
/// \Re(y[n]) =
/// \begin{cases}
/// \Re \{x[n]\},&  \lvert \Re\{x[n]\} \rvert  \leq T_c \\ T_c,& \Re\{x[n]\} > T_c \\ -T_c,& \Re \{x[n]\} < -T_c
/// \end{cases}
/// \Im(y[n]) =
/// \begin{cases}
/// \Im \{x[n]\},&  \lvert \Im\{x[n]\} \rvert  \leq T_c \\ T_c,& \Im\{x[n]\} > T_c \\ -T_c,& \Im \{x[n]\} < -T_c
/// \end{cases}
/// \f]
///
/// Where \f$ T_c \f$ is the clipping threshold.
///
/// \param [out] y Output Span.
/// \param [in]  x Input Span.
/// \param [in]  threshold Clipping threshold.
/// \return The number of clipped samples.
unsigned clip_iq(span<cf_t> y, span<const cf_t> x, float threshold);

/// \brief Clips the magnitude of a complex span.
///
/// Limits the magnitude of the samples to the specified clipping threshold. The clipping process is defined as
/// \f[
/// y[n] =
/// \begin{cases}
/// x[n],&  \lvert x[n] \rvert  \leq T_c \\ T_c e^{j\arg(x[n])},&  \lvert x[n] \rvert > T_c
/// \end{cases}
/// \f]
/// Where \f$ T_c \f$ is the clipping threshold.
///
/// \param [out] y Output Span.
/// \param [in]  x Input Span.
/// \param [in]  threshold Clipping threshold.
/// \return The number of clipped samples.

/// \brief Clips the magnitude of a complex span.
///
/// Limits the magnitude of the samples to the specified clipping threshold. The clipping process is defined as
/// \f[
/// y[n] =
/// \begin{cases}
/// x[n],&  \lvert x[n] \rvert  \leq T_c \\ T_c e^{j\arg(x[n])},&  \lvert x[n] \rvert > T_c
/// \end{cases}
/// \f]
/// Where \f$ T_c \f$ is the clipping threshold.
///
/// \param [out] y Output Span.
/// \param [in]  x Input Span.
/// \param [in]  threshold Clipping threshold.
/// \return The number of clipped samples.
unsigned clip_magnitude(span<cf_t> y, span<const cf_t> x, float threshold);


} // namespace ocuduvec
} // namespace ocudu
