// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/cu_cp/f1ap_configuration.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <chrono>


namespace ocudu {
namespace ocucp {

/// Configuration for F1AP CU-CP.

/// Configuration for F1AP CU-CP.
struct f1ap_configuration {
  /// Timeout for waiting for the DU response during F1AP procedures (Implementation-defined).
  /// Timeout for waiting for the DU response during F1AP procedures (Implementation-defined).
  std::chrono::milliseconds proc_timeout{1000};
  /// Whether to enable JSON logging of F1AP Tx and Rx messages.
  /// Whether to enable JSON logging of F1AP Tx and Rx messages.
  bool json_log_enabled = false;
};


} // namespace ocucp
} // namespace ocudu
