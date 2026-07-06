// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_cp/o_cu_cp.h  (27 lines)
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


class cu_cp;
class cu_cp_operation_controller;

/// O-RAN CU-CP interface.

/// O-RAN CU-CP interface.
class o_cu_cp
{
public:
  virtual ~o_cu_cp() = default;

  /// Returns the CU-CP of this O-RAN CU-CP.

  /// Returns the CU-CP of this O-RAN CU-CP.
  virtual cu_cp& get_cu_cp() = 0;

  /// Returns the operation controller of this O-RAN CU-CP.

  /// Returns the operation controller of this O-RAN CU-CP.
  virtual cu_cp_operation_controller& get_operation_controller() = 0;
};


} // namespace ocucp
} // namespace ocudu
