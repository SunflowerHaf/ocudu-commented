// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_up/o_cu_up.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/cu_up
// CU-UP public interfaces: o_cu_up (top-level), cu_up_operation_controller, the GTP-U tunnel management interface, and the N3 endpoint interface. These are the seams between the CU-UP library and the application layer above it.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace ocuup {


class cu_up_interface;
class cu_up_operation_controller;

/// O-RAN CU-UP interface.

/// O-RAN CU-UP interface.
class o_cu_up
{
public:
  virtual ~o_cu_up() = default;

  /// Returns the CU-UP of this O-RAN CU-UP.

  /// Returns the CU-UP of this O-RAN CU-UP.
  virtual cu_up_interface& get_cu_up() = 0;

  /// Returns the operation controller of this O-RAN CU-UP.

  /// Returns the operation controller of this O-RAN CU-UP.
  virtual cu_up_operation_controller& get_operation_controller() = 0;
};


} // namespace ocuup
} // namespace ocudu
