// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_low/o_du_low_config.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/du/du_low/du_low_config.h"
#include "ocudu/fapi_adaptor/phy/phy_fapi_fastpath_adaptor_config.h"


namespace ocudu {
namespace odu {


using cell_prach_ports_entry = std::vector<uint8_t>;

/// O-RAN DU low configuration.

/// O-RAN DU low configuration.
struct o_du_low_config {
  du_low_config du_low_cfg;
  /// FAPI adaptor configuration.
  /// FAPI adaptor configuration.
  fapi_adaptor::phy_fapi_fastpath_adaptor_config fapi_cfg;
  /// Metrics configuration. Set to \c true to enable the DU low metrics.
  /// Metrics configuration. Set to \c true to enable the DU low metrics.
  bool enable_metrics;
};

/// O-RAN DU low dependencies.

/// O-RAN DU low dependencies.
struct o_du_low_dependencies {
  /// DU Low dependencies.
  /// DU Low dependencies.
  du_low_dependencies du_low_deps;
  /// FAPI P5 executor.
  /// FAPI P5 executor.
  task_executor& fapi_p5_executor;
};


} // namespace odu
} // namespace ocudu
