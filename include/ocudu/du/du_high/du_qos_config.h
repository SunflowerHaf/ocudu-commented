// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/du/du_high/du_qos_config.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/du
// DU public interfaces: o_du_high (top-level DU High factory and lifecycle), du_high_configuration, the scheduler-DU interface, the O-DU Low factory, and the DU configurator interface for live SSB/RRM/SIB updates. Also contains du_cell_config (per-cell low-level parameters) and du_metrics_report.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/f1u/du/f1u_config.h"
#include "ocudu/mac/mac_lc_config.h"
#include "ocudu/rlc/rlc_config.h"


namespace ocudu {
namespace odu {

/// \brief QoS Configuration, i.e. 5QI and the associated RLC configuration for DRBs

/// \brief QoS Configuration, i.e. 5QI and the associated RLC configuration for DRBs
struct du_qos_config {
  rlc_config                                           rlc;
  f1u_config                                           f1u;
  std::optional<mac_lc_config::triggered_ul_grant_cfg> triggered_ul_grant;
};


} // namespace odu
} // namespace ocudu
