// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_high_ntn_sib19_update_handler_factory.cpp  (15 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/du/du_high/du_high_ntn_sib19_update_handler_factory.h"
#include "du_high_ntn_sib19_update_handler_impl.h"


using namespace ocudu;


std::unique_ptr<ocudu_ntn::ntn_sib19_update_handler>
ocudu::create_ntn_sib19_update_handler(odu::du_configurator& du_cfgtr)
{
  auto sib19_msg_update_handler = std::make_unique<odu::du_high_ntn_sib19_update_handler_impl>(du_cfgtr);
  return sib19_msg_update_handler;
}
