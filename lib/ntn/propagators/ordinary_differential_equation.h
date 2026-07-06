// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ntn/propagators/ordinary_differential_equation.h  (67 lines)
//
// LIBRARY: lib/ntn
// Non-Terrestrial Network (NTN) support library (3GPP Release 17+): satellite orbit propagation (RK4 and Keplerian propagators), Doppler shift computation, NTN assistance information encoding for SIB19, K-offset application to timing relationships, and feeder-link Doppler correction.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <array>


namespace ocudu {
namespace ocudu_ntn {

/// \brief Base class for Ordinary Differential Equation solvers.

/// \brief Base class for Ordinary Differential Equation solvers.
class ordinary_differential_equation
{
public:
  /// Type alias for ODE state vector.
  /// Type alias for ODE state vector.
  using ode_state_vector = std::array<double, 6>;

  /// \brief Constructor.
  ///
  /// \param time_step_s Time step in seconds.

  /// \brief Constructor.
  ///
  /// \param time_step_s Time step in seconds.
  explicit ordinary_differential_equation(double time_step_s);


  virtual ~ordinary_differential_equation() = default;

  /// \brief Set the ODE solver with initial conditions.
  ///
  /// \param initial_time_s Initial time in seconds.
  /// \param initial_state Initial state vector.

  /// \brief Set the ODE solver with initial conditions.
  ///
  /// \param initial_time_s Initial time in seconds.
  /// \param initial_state Initial state vector.
  void set_initial_state(double initial_time_s, const ode_state_vector& initial_state);

  /// \brief Set the step width for integration.
  ///
  /// \param step_width_s Step width in seconds.

  /// \brief Set the step width for integration.
  ///
  /// \param step_width_s Step width in seconds.
  void set_step_width(double step_width_s);

  /// \brief Get the current state vector.
  ///
  /// \return Current state vector.

  /// \brief Get the current state vector.
  ///
  /// \return Current state vector.
  const ode_state_vector& get_state() const { return state; }

  /// \brief Update the state using the integration method.

  /// \brief Update the state using the integration method.
  void update();


protected:
  /// \brief Calculate the derivative of the state vector.
  ///
  /// \param t Current time.
  /// \param state Current state vector.
  /// \return Derivative of the state vector.
  /// \brief Calculate the derivative of the state vector.
  ///
  /// \param t Current time.
  /// \param state Current state vector.
  /// \return Derivative of the state vector.
  virtual ode_state_vector derivative_function(double t, const ode_state_vector& state) const = 0;

  /// Current time in seconds.

  /// Current time in seconds.
  double time;

  /// Current state vector.

  /// Current state vector.
  ode_state_vector state;

  /// Initial step width in seconds.

  /// Initial step width in seconds.
  double default_step_width_s;

  /// Current step width in seconds.

  /// Current step width in seconds.
  double step_width_s;
};


} // namespace ocudu_ntn
} // namespace ocudu
