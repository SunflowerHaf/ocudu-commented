// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/du_positioning_handler_factory.cpp  (17 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "du_positioning_handler_factory.h"
#include "du_positioning_manager_impl.h"


using namespace ocudu;
using namespace odu;


std::unique_ptr<f1ap_du_positioning_handler> odu::create_du_positioning_handler(const du_manager_params& du_params,
                                                                                du_cell_manager&         cell_mng,
                                                                                du_ue_manager&           ue_mng,
                                                                                ocudulog::basic_logger&  logger)
{
  return std::make_unique<du_positioning_manager_impl>(du_params, cell_mng, ue_mng, logger);
}
