// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_cp/cu_cp_operation_controller.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/cu_cp
// CU-CP public interfaces: the abstract classes that the CU-CP exposes to the rest of the system. Key interfaces: cu_cp (the top-level factory and lifecycle), cu_cp_operation_controller (start/stop), n2_connection_client (NGAP socket management), cu_configurator (SSB/RRM/SIB remote changes), and the UE management interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace ocucp {

/// CU-CP operation controller interface that allows to start/stop a CU-CP.

/// CU-CP operation controller interface that allows to start/stop a CU-CP.
class cu_cp_operation_controller
{
public:
  virtual ~cu_cp_operation_controller() = default;

  /// Starts the CU-CP.

  /// Starts the CU-CP.
  virtual void start() = 0;

  /// Stops the CU-CP.

  /// Stops the CU-CP.
  virtual void stop() = 0;
};


} // namespace ocucp
} // namespace ocudu
