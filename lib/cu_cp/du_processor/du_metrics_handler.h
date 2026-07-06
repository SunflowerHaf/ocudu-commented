// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/du_processor/du_metrics_handler.h  (33 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_cp_metrics_handler.h"


namespace ocudu {
namespace ocucp {

/// Interface used to capture the DU metrics from a single CU-CP DU.

/// Interface used to capture the DU metrics from a single CU-CP DU.
class du_metrics_handler
{
public:
  virtual ~du_metrics_handler() = default;

  /// \brief Handle new request for metrics relative to a connected DU.

  /// \brief Handle new request for metrics relative to a connected DU.
  virtual cu_cp_metrics_report::du_info handle_du_metrics_report_request() const = 0;
};

/// Interface used to capture the DU metrics from all the connected DUs to the CU-CP.

/// Interface used to capture the DU metrics from all the connected DUs to the CU-CP.
class du_repository_metrics_handler
{
public:
  virtual ~du_repository_metrics_handler() = default;

  /// \brief Handle new metrics request for all the DU nodes connected to the CU-CP.

  /// \brief Handle new metrics request for all the DU nodes connected to the CU-CP.
  virtual std::vector<cu_cp_metrics_report::du_info> handle_du_metrics_report_request() const = 0;
};


} // namespace ocucp
} // namespace ocudu
