// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/cu_cp/e1ap_configuration.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <chrono>


namespace ocudu {
namespace ocucp {

/// Configuration for E1AP CU-CP.

/// Configuration for E1AP CU-CP.
struct e1ap_configuration {
  /// Timeout for waiting for the CU-UP response during E1AP procedures (Implementation-defined).
  /// Timeout for waiting for the CU-UP response during E1AP procedures (Implementation-defined).
  std::chrono::milliseconds proc_timeout{1000};
  /// Whether to enable JSON logging of E1AP Tx and Rx messages.
  /// Whether to enable JSON logging of E1AP Tx and Rx messages.
  bool json_log_enabled = false;
};


} // namespace ocucp
} // namespace ocudu
