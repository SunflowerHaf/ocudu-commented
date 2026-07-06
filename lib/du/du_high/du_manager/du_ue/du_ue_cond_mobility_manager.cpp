// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/du_ue/du_ue_cond_mobility_manager.cpp  (27 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "du_ue_cond_mobility_manager.h"


using namespace ocudu;
using namespace ocudu::odu;


void du_ue_cond_mobility_manager::set_success_access_required()
{
  success_access_required = true;
}


bool du_ue_cond_mobility_manager::is_success_access_required() const
{
  return success_access_required;
}


bool du_ue_cond_mobility_manager::handle_crnti_ce_indication()
{
  if (!success_access_required) {
    return false;
  }
  success_access_required = false;
  return true;
}
