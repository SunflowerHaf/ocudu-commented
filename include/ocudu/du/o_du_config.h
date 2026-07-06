// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/o_du_config.h  (24 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/du/du_high/o_du_high.h"
#include "ocudu/du/du_low/o_du_low.h"
#include <memory>


namespace ocudu {
namespace odu {


class o_du_metrics_notifier;

/// O-RAN Distributed Unit dependencies.

/// O-RAN Distributed Unit dependencies.
struct o_du_dependencies {
  o_du_metrics_notifier*     metrics_notifier = nullptr;
  std::unique_ptr<o_du_high> odu_hi;
  std::unique_ptr<o_du_low>  odu_lo;
};


} // namespace odu
} // namespace ocudu
