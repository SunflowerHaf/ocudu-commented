// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/support/csi_report_helpers.h  (18 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/csi_rs/csi_meas_config.h"
#include "ocudu/ran/slot_point.h"
#include "ocudu/scheduler/config/ue_bwp_config.h"


namespace ocudu::csi_helper {

/// \brief Checks if the slot is a candidate for periodic CSI reporting on PUCCH for a given user.

/// \brief Checks if the slot is a candidate for periodic CSI reporting on PUCCH for a given user.
bool is_csi_reporting_slot(const ue_periodic_csi_config& periodic_csi,
                           csi_resource_periodicity      csi_period,
                           slot_point                    sl_tx);


} // namespace ocudu::csi_helper
