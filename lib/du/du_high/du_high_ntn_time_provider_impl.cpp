// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_high_ntn_time_provider_impl.cpp  (28 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "du_high_ntn_time_provider_impl.h"


using namespace ocudu;
using namespace odu;


du_high_ntn_time_provider_impl::du_high_ntn_time_provider_impl(mac_subframe_time_mapper& time_mapper_) :
  subframe_time_mapper(time_mapper_)
{
}


std::optional<ocudu_ntn::ntn_time_slot_mapping> du_high_ntn_time_provider_impl::get_last_mapping(subcarrier_spacing scs)
{
  auto mac_mapping = subframe_time_mapper.get_last_mapping(scs);


  if (!mac_mapping.has_value()) {
    return std::nullopt;
  }


  ocudu_ntn::ntn_time_slot_mapping ntn_mapping;
  ntn_mapping.slot_tx    = mac_mapping->sl_tx;
  ntn_mapping.time_point = mac_mapping->time_point;


  return ntn_mapping;
}
