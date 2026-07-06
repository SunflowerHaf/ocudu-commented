// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ntn/ntn_time_provider.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/ntn
// NTN interface headers: orbit_propagator (interface for computing satellite positions at future times), the propagator factory, and the ephemeris data types used by the NTN Doppler compensation subsystem.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/slot_point.h"
#include <chrono>
#include <optional>


namespace ocudu {
namespace ocudu_ntn {

/// Time slot mapping information for NTN context.

/// Time slot mapping information for NTN context.
struct ntn_time_slot_mapping {
  /// Slot point for transmission.
  /// Slot point for transmission.
  slot_point slot_tx;
  /// Corresponding time point.
  /// Corresponding time point.
  std::chrono::time_point<std::chrono::system_clock> time_point;
};

/// Interface for providing time information in NTN context.

/// Interface for providing time information in NTN context.
class ntn_time_provider
{
public:
  virtual ~ntn_time_provider() = default;

  /// \brief Get the last time slot mapping.
  ///
  /// This function provides access to the most recent time slot mapping for time synchronization operations in NTN
  /// context.
  /// \return Optional containing the time slot mapping if available.

  /// \brief Get the last time slot mapping.
  ///
  /// This function provides access to the most recent time slot mapping for time synchronization operations in NTN
  /// context.
  /// \return Optional containing the time slot mapping if available.
  virtual std::optional<ntn_time_slot_mapping> get_last_mapping(subcarrier_spacing scs) = 0;
};


} // namespace ocudu_ntn
} // namespace ocudu
