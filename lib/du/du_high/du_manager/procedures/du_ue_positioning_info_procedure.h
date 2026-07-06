// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/procedures/du_ue_positioning_info_procedure.h  (32 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../du_cell_manager.h"
#include "../du_ue/du_ue_manager.h"
#include "ocudu/f1ap/du/f1ap_du_positioning_handler.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::odu {


class du_ue_positioning_info_procedure
{
public:
  du_ue_positioning_info_procedure(const du_positioning_info_request& req_,
                                   du_cell_manager&                   du_cells_,
                                   du_ue_manager&                     ue_mng_);


  void operator()(coro_context<async_task<du_positioning_info_response>>& ctx);


private:
  du_positioning_info_response create_response(bool success);


  const du_positioning_info_request req;
  du_cell_manager&                  du_cells;
  du_ue_manager&                    ue_mng;
  du_ue&                            ue;
};


} // namespace ocudu::odu
