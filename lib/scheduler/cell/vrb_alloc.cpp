// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/cell/vrb_alloc.cpp  (27 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/scheduler/result/vrb_alloc.h"


using namespace ocudu;


prb_bitmap ocudu::convert_rbgs_to_prbs(const rbg_bitmap& rbgs, crb_interval bwp_rbs, nominal_rbg_size P)
{
  int      idx            = 0;
  unsigned first_rbg_size = get_rbg_size(bwp_rbs, P, 0);


  prb_bitmap prbs(bwp_rbs.length());
  do {
    idx = rbgs.find_lowest(idx, rbgs.size(), true);
    if (idx < 0) {
      break;
    }
    uint32_t prb_idx = (idx - 1) * to_nominal_rbg_size_value(P) + first_rbg_size;
    uint32_t prb_end = std::min(prb_idx + ((idx == 0) ? first_rbg_size : to_nominal_rbg_size_value(P)),
                                static_cast<uint32_t>(prbs.size()));
    prbs.fill(prb_idx, prb_end);
    idx++;
  } while (idx != static_cast<int>(prbs.size()));
  return prbs;
}
