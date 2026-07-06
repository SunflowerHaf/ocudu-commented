// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/procedures/ue_deletion_procedure.h  (45 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../du_ue/du_ue.h"
#include "../du_ue/du_ue_manager_repository.h"
#include "procedure_logger.h"
#include "ocudu/mac/mac_ue_configurator.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu {
namespace odu {


class ue_deletion_procedure
{
public:
  ue_deletion_procedure(du_ue_index_t             ue_index_,
                        du_ue_manager_repository& ue_mng_,
                        const du_manager_params&  du_params,
                        std::chrono::milliseconds ran_res_release_timeout = std::chrono::milliseconds{0});


  void operator()(coro_context<async_task<void>>& ctx);


  static const char* name() { return "UE Delete"; }


private:
  async_task<mac_ue_delete_response> launch_mac_ue_delete();

  // Disconnects all the DRBs and SRBs associated with the UE. After the bearers have been disconnected, it is safe
  // to start the deletion of the associated bearer contexts.

  // Disconnects all the DRBs and SRBs associated with the UE. After the bearers have been disconnected, it is safe
  // to start the deletion of the associated bearer contexts.
  async_task<void> stop_ue_bearer_traffic();


  const du_ue_index_t             ue_index;
  du_ue_manager_repository&       ue_mng;
  const du_manager_params&        du_params;
  const std::chrono::milliseconds ran_res_release_timeout;
  ue_procedure_logger             proc_logger;


  du_ue* ue = nullptr;
};


} // namespace odu
} // namespace ocudu
