// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/o_du.h  (36 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/du/du.h"


namespace ocudu {


class du_operation_controller;


namespace odu {


class o_du_high;
class o_du_low;

/// O-RAN Distributed Unit interface. Includes the O-RAN DU high, O-RAN DU low and a DU operation controller in an
/// object.

/// O-RAN Distributed Unit interface. Includes the O-RAN DU high, O-RAN DU low and a DU operation controller in an
/// object.
class o_du
{
public:
  virtual ~o_du() = default;

  /// Returns the operation controller of this O-RAN DU.

  /// Returns the operation controller of this O-RAN DU.
  virtual du_operation_controller& get_operation_controller() = 0;

  /// Returns the O-RAN DU high of this O-RAN DU.

  /// Returns the O-RAN DU high of this O-RAN DU.
  virtual o_du_high& get_o_du_high() = 0;

  /// Returns the O-RAN DU low of this O-RAN DU.

  /// Returns the O-RAN DU low of this O-RAN DU.
  virtual o_du_low& get_o_du_low() = 0;
};


} // namespace odu
} // namespace ocudu
