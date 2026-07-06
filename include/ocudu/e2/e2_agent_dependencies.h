// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2_agent_dependencies.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/e2ap_configuration.h"
#include "ocudu/e2/e2sm/e2sm.h"
#include "ocudu/support/timers.h"
#include <memory>
#include <vector>


namespace ocudu {


class e2_connection_client;
class e2_node_component_config_provider;

/// E2SM Service Module to be added into E2 agent.

/// E2SM Service Module to be added into E2 agent.
struct e2sm_module {
  uint32_t                        ran_func_id;
  std::string                     oid;
  std::unique_ptr<e2sm_handler>   e2sm_packer;
  std::unique_ptr<e2sm_interface> e2sm_iface;
};

/// O-RAN E2 Agent dependencies.

/// O-RAN E2 Agent dependencies.
struct e2_agent_dependencies {
  ocudulog::basic_logger*                            logger;
  e2ap_configuration                                 cfg;
  e2_connection_client*                              e2_client;
  timer_factory*                                     timers;
  task_executor*                                     task_exec;
  std::unique_ptr<e2_node_component_config_provider> node_component_config_provider;
  std::vector<e2sm_module>                           e2sm_modules;
};


} // namespace ocudu
