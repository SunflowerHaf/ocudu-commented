// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/du_manager_context.h  (20 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace odu {

/// General operational state of the DU.

/// General operational state of the DU.
struct du_manager_context {
  /// Whether the DU is in operational mode.
  /// Whether the DU is in operational mode.
  bool running = false;
  /// Flag used to signal that the DU was commanded to stop.
  /// \note This may serve as a cancellation signal to other long on-going procedures.
  /// Flag used to signal that the DU was commanded to stop.
  /// \note This may serve as a cancellation signal to other long on-going procedures.
  bool stop_command_received = false;
};


} // namespace odu
} // namespace ocudu
