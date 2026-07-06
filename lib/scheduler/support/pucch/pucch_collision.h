// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/support/pucch/pucch_collision.h  (19 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/pucch/pucch_configuration.h"


namespace ocudu {

/// \brief Returns the multiplexing index of the PUCCH resource.
///
/// Used to determine orthogonality between resources sharing the same time-frequency allocation.

/// \brief Returns the multiplexing index of the PUCCH resource.
///
/// Used to determine orthogonality between resources sharing the same time-frequency allocation.
unsigned pucch_mux_idx(const pucch_resource& res);

/// Checks whether two PUCCH resources collide, i.e., they interfere with each other if allocated in the same slot.

/// Checks whether two PUCCH resources collide, i.e., they interfere with each other if allocated in the same slot.
bool pucch_resources_collide(const pucch_resource& res1, const pucch_resource& res2);


} // namespace ocudu
