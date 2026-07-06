// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/scheduler/support/pusch/pusch_dmrs_symbol_mask.cpp  (44 lines)
//
// LIBRARY: lib/scheduler
// NR downlink/uplink scheduler (~200 files, ~44k lines). Implements: per-UE DL/UL grant allocation, PDCCH aggregation-level selection, PUCCH resource assignment, HARQ process tracking, time-domain resource allocation, proportional-fair and round-robin policies, slice-aware scheduling, and the inter-slot scheduling pipeline.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "pusch_dmrs_symbol_mask.h"


using namespace ocudu;


dmrs_symbol_mask ocudu::pusch_dmrs_symbol_mask_mapping_type_A_single_get(
    const pusch_dmrs_symbol_mask_mapping_type_A_single_configuration& config)
{
  unsigned l0 = static_cast<unsigned>(config.typeA_pos);


  dmrs_symbol_mask mask(14);
  mask.set(l0);


  if (config.last_symbol < 8 || config.additional_position == dmrs_additional_positions::pos0) {
    return mask;
  }


  if (config.last_symbol < 10) {
    mask.set(7);
    return mask;
  }


  if (config.last_symbol < 13 &&
      (config.last_symbol != 12 || config.additional_position < dmrs_additional_positions::pos3)) {
    mask.set(9);
    if (config.additional_position >= dmrs_additional_positions::pos2) {
      mask.set(6);
    }
    return mask;
  }


  mask.set(11);
  if (config.additional_position == dmrs_additional_positions::pos2) {
    mask.set(7);
  } else if (config.additional_position == dmrs_additional_positions::pos3) {
    mask.set(5);
    mask.set(8);
  }


  return mask;
}
