// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


class du_operation_controller;


namespace odu {

/// Public DU interface.

/// Public DU interface.
class du
{
public:
  virtual ~du() = default;

  /// Returns the operation controller of this DU.

  /// Returns the operation controller of this DU.
  virtual du_operation_controller& get_operation_controller() = 0;
};


} // namespace odu
} // namespace ocudu
