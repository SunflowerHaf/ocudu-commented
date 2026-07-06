// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/ue_manager/ue_metrics_handler.h  (23 lines)
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

/// Interface used to capture the UE metrics from the CU-CP UE manager.

/// Interface used to capture the UE metrics from the CU-CP UE manager.
class ue_metrics_handler
{
public:
  virtual ~ue_metrics_handler() = default;

  /// \brief Handle new request for UE metrics.

  /// \brief Handle new request for UE metrics.
  virtual std::vector<cu_cp_metrics_report::ue_info> handle_ue_metrics_report_request() const = 0;
};


} // namespace ocucp
} // namespace ocudu
