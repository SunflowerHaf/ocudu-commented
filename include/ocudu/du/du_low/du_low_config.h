// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_low/du_low_config.h  (43 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/phy/upper/upper_phy_factories.h"


namespace ocudu {
namespace odu {

/// DU low cell configuration.

/// DU low cell configuration.
struct du_low_cell_config {
  /// Upper PHY configuration.
  /// Upper PHY configuration.
  upper_phy_configuration upper_phy_cfg;
};

/// DU low cell dependencies.

/// DU low cell dependencies.
struct du_low_cell_dependencies {
  /// Upper PHY dependencies.
  /// Upper PHY dependencies.
  upper_phy_dependencies upper_phy_deps;
};

/// Parameters used to instantiate the DU-low.

/// Parameters used to instantiate the DU-low.
struct du_low_config {
  /// Upper physical layer common configuration for all cells.
  /// Upper physical layer common configuration for all cells.
  upper_phy_factory_configuration upper_phy_common_config;
  /// Specific cell configuration.
  /// Specific cell configuration.
  std::vector<du_low_cell_config> cells;
};

/// Dependencies necessary to instantiate a DU-low.

/// Dependencies necessary to instantiate a DU-low.
struct du_low_dependencies {
  /// Logger used to report state of the DU-low.
  /// Logger used to report state of the DU-low.
  ocudulog::basic_logger* logger;
  /// Upper physical layer common dependencies for all cells.
  /// Upper physical layer common dependencies for all cells.
  upper_phy_factory_dependencies upper_phy_common_deps;
  /// Specific cell dependencies.
  /// Specific cell dependencies.
  std::vector<du_low_cell_dependencies> cells;
};


} // namespace odu
} // namespace ocudu
