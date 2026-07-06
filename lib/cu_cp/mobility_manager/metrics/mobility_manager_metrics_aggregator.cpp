// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/mobility_manager/metrics/mobility_manager_metrics_aggregator.cpp  (35 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "mobility_manager_metrics_aggregator.h"


using namespace ocudu;
using namespace ocucp;


void mobility_manager_metrics_aggregator::aggregate_requested_handover_preparation()
{
  ++aggregated_mobility_manager_metrics.nof_handover_preparations_requested;
}


void mobility_manager_metrics_aggregator::aggregate_successful_handover_preparation()
{
  ++aggregated_mobility_manager_metrics.nof_successful_handover_preparations;
}

/// \brief Aggregates the metrics for the requested handover execution.

/// \brief Aggregates the metrics for the requested handover execution.
void mobility_manager_metrics_aggregator::aggregate_requested_handover_execution()
{
  ++aggregated_mobility_manager_metrics.nof_handover_executions_requested;
}

/// \brief Aggregates the metrics for the successful handover execution.

/// \brief Aggregates the metrics for the successful handover execution.
void mobility_manager_metrics_aggregator::aggregate_successful_handover_execution()
{
  ++aggregated_mobility_manager_metrics.nof_successful_handover_executions;
}


mobility_management_metrics mobility_manager_metrics_aggregator::request_metrics_report() const
{
  return aggregated_mobility_manager_metrics;
}
