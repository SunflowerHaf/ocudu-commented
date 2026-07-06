// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/policy/scheduler_policy_factory.cpp  (21 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "scheduler_policy_factory.h"
#include "scheduler_time_qos.h"
#include "scheduler_time_rr.h"


using namespace ocudu;


std::unique_ptr<scheduler_policy> ocudu::create_scheduler_strategy(const scheduler_policy_config& policy_cfg,
                                                                   const cell_configuration&      cell_cfg)
{
  if (std::holds_alternative<time_rr_scheduler_config>(policy_cfg)) {
    return std::make_unique<scheduler_time_rr>();
  }
  if (std::holds_alternative<time_qos_scheduler_config>(policy_cfg)) {
    return std::make_unique<scheduler_time_qos>(std::get<time_qos_scheduler_config>(policy_cfg), cell_cfg);
  }
  return nullptr;
}
