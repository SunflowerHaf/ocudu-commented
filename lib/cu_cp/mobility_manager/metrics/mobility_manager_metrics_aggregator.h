// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/mobility_manager/metrics/mobility_manager_metrics_aggregator.h  (32 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ngap/mobility_management_metrics.h"


namespace ocudu::ocucp {


class mobility_manager_metrics_aggregator
{
public:
  /// \brief Aggregates the metrics for the requested handover preparation.
  /// \brief Aggregates the metrics for the requested handover preparation.
  void aggregate_requested_handover_preparation();

  /// \brief Aggregates the metrics for the successful handover preparation.

  /// \brief Aggregates the metrics for the successful handover preparation.
  void aggregate_successful_handover_preparation();

  /// \brief Aggregates the metrics for the requested handover execution.

  /// \brief Aggregates the metrics for the requested handover execution.
  void aggregate_requested_handover_execution();

  /// \brief Aggregates the metrics for the successful handover execution.

  /// \brief Aggregates the metrics for the successful handover execution.
  void aggregate_successful_handover_execution();


  mobility_management_metrics request_metrics_report() const;


private:
  mobility_management_metrics aggregated_mobility_manager_metrics;
};


} // namespace ocudu::ocucp
