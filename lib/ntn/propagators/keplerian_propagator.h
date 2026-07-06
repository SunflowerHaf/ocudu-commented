// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ntn/propagators/keplerian_propagator.h  (23 lines)
//
// LIBRARY: lib/ntn
// Non-Terrestrial Network (NTN) support library (3GPP Release 17+): satellite orbit propagation (RK4 and Keplerian propagators), Doppler shift computation, NTN assistance information encoding for SIB19, K-offset application to timing relationships, and feeder-link Doppler correction.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../orbit_ephemeris_info.h"
#include "orbital_propagator_model.h"


namespace ocudu {
namespace ocudu_ntn {

/// \brief Keplerian (two-body) orbit propagator.
/// \details Analytically advances mean anomaly using n = sqrt(mu/a^3).
///          No perturbations (J2, drag) are modelled.

/// \brief Keplerian (two-body) orbit propagator.
/// \details Analytically advances mean anomaly using n = sqrt(mu/a^3).
///          No perturbations (J2, drag) are modelled.
class keplerian_propagator : public orbital_propagation_model
{
public:
  void propagate(orbit_ephemeris_info& orbit, std::chrono::duration<double> propagation_time) override;
};


} // namespace ocudu_ntn
} // namespace ocudu
