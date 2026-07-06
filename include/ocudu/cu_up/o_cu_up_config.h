// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_up/o_cu_up_config.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/cu_up
// CU-UP public interfaces: o_cu_up (top-level), cu_up_operation_controller, the GTP-U tunnel management interface, and the N3 endpoint interface. These are the seams between the CU-UP library and the application layer above it.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_up/cu_up_config.h"
#include "ocudu/e2/e2_cu.h"
#include "ocudu/e2/e2ap_configuration.h"
#include "ocudu/e2/gateways/e2_connection_client.h"


namespace ocudu {
namespace ocuup {

/// O-RAN CU-UP configuration.

/// O-RAN CU-UP configuration.
struct o_cu_up_config {
  /// CU-UP configuration.
  /// CU-UP configuration.
  cu_up_config cu_up_cfg;
  /// E2AP configuration.
  /// E2AP configuration.
  e2ap_configuration e2ap_cfg;
};

/// O-RAN CU-UP dependencies.

/// O-RAN CU-UP dependencies.
struct o_cu_up_dependencies {
  /// CU-UP dependencies.
  /// CU-UP dependencies.
  cu_up_dependencies cu_dependencies;
  /// E2 CU metrics interface.
  /// E2 CU metrics interface.
  e2_cu_metrics_interface* e2_cu_metric_iface = nullptr;
  /// E2 connection client.
  /// E2 connection client.
  e2_connection_client* e2_client = nullptr;
};


} // namespace ocuup
} // namespace ocudu
