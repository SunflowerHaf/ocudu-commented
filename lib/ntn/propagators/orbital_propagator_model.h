// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ntn/propagators/orbital_propagator_model.h  (28 lines)
//
// LIBRARY: lib/ntn
// Non-Terrestrial Network (NTN) support library (3GPP Release 17+): satellite orbit propagation (RK4 and Keplerian propagators), Doppler shift computation, NTN assistance information encoding for SIB19, K-offset application to timing relationships, and feeder-link Doppler correction.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <chrono>


namespace ocudu {
namespace ocudu_ntn {


class orbit_ephemeris_info;

/// Orbital propagation model.

/// Orbital propagation model.
class orbital_propagation_model
{
public:
  virtual ~orbital_propagation_model() = default;

  /// \brief Propagate orbit.
  ///
  /// \param initial_orbit_state Initial orbit state to be propagated.
  /// \param propagation_time Propagate the ephemeris info for a given duration.

  /// \brief Propagate orbit.
  ///
  /// \param initial_orbit_state Initial orbit state to be propagated.
  /// \param propagation_time Propagate the ephemeris info for a given duration.
  virtual void propagate(orbit_ephemeris_info& initial_orbit_state, std::chrono::duration<double> propagation_time) = 0;
};


} // namespace ocudu_ntn
} // namespace ocudu
