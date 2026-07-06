// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ntn/orbit_propagator_type.h  (14 lines)
//
// INTERFACE HEADER — include/ocudu/ntn
// NTN interface headers: orbit_propagator (interface for computing satellite positions at future times), the propagator factory, and the ephemeris data types used by the NTN Doppler compensation subsystem.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace ocudu_ntn {

/// Orbit propagator type for NTN ephemeris propagation.

/// Orbit propagator type for NTN ephemeris propagation.
enum class orbit_propagator_type { rk4, keplerian };


} // namespace ocudu_ntn
} // namespace ocudu
