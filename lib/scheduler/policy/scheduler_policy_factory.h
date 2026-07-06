// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/policy/scheduler_policy_factory.h  (19 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "scheduler_policy.h"
#include "ocudu/scheduler/config/scheduler_expert_config.h"
#include <memory>


namespace ocudu {


class cell_configuration;

/// Creatre intra-cell, intra-slice scheduler policy.

/// Creatre intra-cell, intra-slice scheduler policy.
std::unique_ptr<scheduler_policy> create_scheduler_strategy(const scheduler_policy_config& policy_cfg,
                                                            const cell_configuration&      cell_cfg);


} // namespace ocudu
