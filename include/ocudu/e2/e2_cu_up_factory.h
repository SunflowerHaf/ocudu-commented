// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2_cu_up_factory.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_configurator.h"
#include "ocudu/e2/e2_cu.h"
#include "ocudu/e2/e2ap_configuration.h"
#include "ocudu/e2/gateways/e2_connection_client.h"
#include "ocudu/support/timers.h"
#include <memory>


namespace ocudu {


class e2_node_component_config_provider;

/// Creates a instance of an E2 interface (with subscription manager)

/// Creates a instance of an E2 interface (with subscription manager)
std::unique_ptr<e2_agent>
create_e2_cu_up_agent(const e2ap_configuration&                          e2ap_cfg_,
                      e2_connection_client&                              e2_client_,
                      e2_cu_metrics_interface*                           e2_metrics_,
                      cu_configurator*                                   cu_configurator_,
                      timer_factory                                      timers_,
                      task_executor&                                     e2_exec_,
                      std::unique_ptr<e2_node_component_config_provider> node_component_config_provider_);


} // namespace ocudu
