// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/procedures/du_ue_ric_configuration_procedure.h  (42 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../du_ue/du_ue_manager_repository.h"
#include "ocudu/du/du_high/du_manager/du_configurator.h"
#include "ocudu/mac/mac_ue_configurator.h"
#include "ocudu/support/async/manual_event.h"


namespace ocudu {
namespace odu {


class du_ue_ric_configuration_procedure
{
public:
  du_ue_ric_configuration_procedure(const du_mac_sched_control_config& request_,
                                    du_ue_manager_repository&          ue_mng_,
                                    const du_manager_params&           du_params_);


  void operator()(coro_context<async_task<du_mac_sched_control_config_response>>& ctx);


  const char* name() const { return "UE RIC configuration"; }


private:
  manual_event<du_mac_sched_control_config_response>& dispatch_ue_config_task();

  // Task run from within the UE task loop.

  // Task run from within the UE task loop.
  async_task<mac_ue_reconfiguration_response> handle_mac_config();


  const du_mac_sched_control_config request;
  du_ue_manager_repository&         ue_mng;
  const du_manager_params&          du_params;


  du_ue* ue = nullptr;


  manual_event<du_mac_sched_control_config_response> ue_config_completed;
};


} // namespace odu
} // namespace ocudu
