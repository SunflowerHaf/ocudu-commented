// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ntn/ntn_math_helpers.h  (26 lines)
//
// LIBRARY: lib/ntn
// Non-Terrestrial Network (NTN) support library (3GPP Release 17+): satellite orbit propagation (RK4 and Keplerian propagators), Doppler shift computation, NTN assistance information encoding for SIB19, K-offset application to timing relationships, and feeder-link Doppler correction.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/span.h"
#include <array>


namespace ocudu {
namespace ocudu_ntn {

/// \brief Fit a quadratic curve y = c0 + c1*x + c2*x^2 to the given (x, y) data points,
///        with c0 fixed to the provided value.
///
/// This function performs a least-squares fit to determine the coefficients c1 and c2 such that
/// the sum of squared residuals between y and (c0 + c1*x + c2*x^2) is minimized, for a fixed c0.
/// The input vectors x and y must have the same length (at least 2).
/// \param x  The independent variable values.
/// \param y  The dependent variable values.
/// \param c0 The fixed coefficient for the constant term (offset).
/// \returns  An array {c0, c1, c2} of the fitted coefficients.

/// \brief Fit a quadratic curve y = c0 + c1*x + c2*x^2 to the given (x, y) data points,
///        with c0 fixed to the provided value.
///
/// This function performs a least-squares fit to determine the coefficients c1 and c2 such that
/// the sum of squared residuals between y and (c0 + c1*x + c2*x^2) is minimized, for a fixed c0.
/// The input vectors x and y must have the same length (at least 2).
/// \param x  The independent variable values.
/// \param y  The dependent variable values.
/// \param c0 The fixed coefficient for the constant term (offset).
/// \returns  An array {c0, c1, c2} of the fitted coefficients.
std::array<double, 3> fit_quadratic(span<const double> x, span<const double> y, double c0);


} // namespace ocudu_ntn
} // namespace ocudu
