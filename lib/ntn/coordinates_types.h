// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ntn/coordinates_types.h  (131 lines)
//
// LIBRARY: lib/ntn
// Non-Terrestrial Network (NTN) support library (3GPP Release 17+): satellite orbit propagation (RK4 and Keplerian propagators), Doppler shift computation, NTN assistance information encoding for SIB19, K-offset application to timing relationships, and feeder-link Doppler correction.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <array>
#include <cmath>


namespace ocudu {
namespace ocudu_ntn {

/// 3D Cartesian coordinate structure.

/// 3D Cartesian coordinate structure.
struct coord_3d {
  /// X coordinate.
  /// X coordinate.
  double x;
  /// Y coordinate.
  /// Y coordinate.
  double y;
  /// Z coordinate.
  /// Z coordinate.
  double z;
};

/// \brief Computes the Euclidean norm (magnitude) of a 3D point.
///
/// \param a input 3D coordinates.
/// \return The Euclidean norm of the vector.

/// \brief Computes the Euclidean norm (magnitude) of a 3D point.
///
/// \param a input 3D coordinates.
/// \return The Euclidean norm of the vector.
inline double norm(const coord_3d& a)
{
  return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

/// \brief Computes the dot product of two 3D vectors.
///
/// \param a First input vector.
/// \param b Second input vector.
/// \return The scalar dot product of the vectors.

/// \brief Computes the dot product of two 3D vectors.
///
/// \param a First input vector.
/// \param b Second input vector.
/// \return The scalar dot product of the vectors.
inline double dot(const coord_3d& a, const coord_3d& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

/// State vector containing position and velocity.

/// State vector containing position and velocity.
struct state_vector {
  /// Position coordinates in meters.
  /// Position coordinates in meters.
  coord_3d position;
  /// Velocity coordinates in meter/second.
  /// Velocity coordinates in meter/second.
  coord_3d velocity;
};

/// \brief Divides a coord_3d vector by a scalar value.
///
/// \param a The coord_3d to scale.
/// \param scalar The scalar value.
/// \return The result of scaling state vector by scalar.

/// \brief Divides a coord_3d vector by a scalar value.
///
/// \param a The coord_3d to scale.
/// \param scalar The scalar value.
/// \return The result of scaling state vector by scalar.
inline coord_3d operator/(const coord_3d& a, double scalar)
{
  return {a.x / scalar, a.y / scalar, a.z / scalar};
}

/// \brief Adds two state vectors.
///
/// \param a First state_vector.
/// \param b Second state_vector.
/// \return The result of a + b.

/// \brief Adds two state vectors.
///
/// \param a First state_vector.
/// \param b Second state_vector.
/// \return The result of a + b.
inline state_vector operator+(const state_vector& a, const state_vector& b)
{
  return {{a.position.x + b.position.x, a.position.y + b.position.y, a.position.z + b.position.z},
          {a.velocity.x + b.velocity.x, a.velocity.y + b.velocity.y, a.velocity.z + b.velocity.z}};
}

/// \brief Subtracts one state vector from another one.
///
/// \param a Minuend state_vector.
/// \param b Subtrahend state_vector.
/// \return The result of a - b.

/// \brief Subtracts one state vector from another one.
///
/// \param a Minuend state_vector.
/// \param b Subtrahend state_vector.
/// \return The result of a - b.
inline state_vector operator-(const state_vector& a, const state_vector& b)
{
  return {{a.position.x - b.position.x, a.position.y - b.position.y, a.position.z - b.position.z},
          {a.velocity.x - b.velocity.x, a.velocity.y - b.velocity.y, a.velocity.z - b.velocity.z}};
}

/// \brief Multiplies a state vector by a scalar value.
///
/// \param a The state_vector to scale.
/// \param scalar The scalar value.
/// \return The result of scaling state vector by scalar.

/// \brief Multiplies a state vector by a scalar value.
///
/// \param a The state_vector to scale.
/// \param scalar The scalar value.
/// \return The result of scaling state vector by scalar.
inline state_vector operator*(const state_vector& a, double scalar)
{
  return {{a.position.x * scalar, a.position.y * scalar, a.position.z * scalar},
          {a.velocity.x * scalar, a.velocity.y * scalar, a.velocity.z * scalar}};
}

/// \brief Divides a state vector by a scalar value.
///
/// \param a The state_vector to scale.
/// \param scalar The scalar value.
/// \return The result of scaling state vector by scalar.

/// \brief Divides a state vector by a scalar value.
///
/// \param a The state_vector to scale.
/// \param scalar The scalar value.
/// \return The result of scaling state vector by scalar.
inline state_vector operator/(const state_vector& a, double scalar)
{
  return {{a.position.x / scalar, a.position.y / scalar, a.position.z / scalar},
          {a.velocity.x / scalar, a.velocity.y / scalar, a.velocity.z / scalar}};
}

/// Orbital elements for a satellite orbit (all angles in radians, distances in meters).

/// Orbital elements for a satellite orbit (all angles in radians, distances in meters).
struct orbital_elements {
  /// Semi-major axis [m]
  /// Semi-major axis [m]
  double semi_major_axis;
  /// Eccentricity (dimensionless)
  /// Eccentricity (dimensionless)
  double eccentricity;
  /// Inclination [rad]
  /// Inclination [rad]
  double inclination;
  /// Longitude of ascending node [rad]
  /// Longitude of ascending node [rad]
  double longitude;
  /// Argument of periapsis [rad]
  /// Argument of periapsis [rad]
  double periapsis;
  /// Mean anomaly [rad]
  /// Mean anomaly [rad]
  double mean_anomaly;
};

/// Geodetic coordinates (latitude, longitude in degrees, altitude in meters).

/// Geodetic coordinates (latitude, longitude in degrees, altitude in meters).
struct geodetic_coordinates {
  /// Latitude [deg]
  /// Latitude [deg]
  double latitude_deg;
  /// Longitude [deg]
  /// Longitude [deg]
  double longitude_deg;
  /// Altitude [m]
  /// Altitude [m]
  double altitude_m;
};


} // namespace ocudu_ntn
} // namespace ocudu
