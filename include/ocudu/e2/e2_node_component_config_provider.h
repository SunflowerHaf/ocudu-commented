// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2_node_component_config_provider.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/e2_node_component_config.h"
#include "ocudu/support/async/async_task.h"
#include <vector>


namespace ocudu {

/// Interface exposed to e2_impl: provides an awaitable task and a timeout hook.
/// The aggregator implements this; e2_impl holds a non-owning reference to it.

/// Interface exposed to e2_impl: provides an awaitable task and a timeout hook.
/// The aggregator implements this; e2_impl holds a non-owning reference to it.
class e2_node_component_config_provider
{
public:
  virtual ~e2_node_component_config_provider() = default;

  /// \brief Returns an async task that resolves once all expected node-component-config pairs
  ///        have been collected, or on_timeout() is called (whichever comes first).

  /// \brief Returns an async task that resolves once all expected node-component-config pairs
  ///        have been collected, or on_timeout() is called (whichever comes first).
  virtual async_task<std::vector<e2_node_component_config>> get_configs() = 0;

  /// Called by e2_entity's timeout timer (on the E2 executor) when the deadline fires
  /// before all expected pairs have arrived.  Fires the event with whatever was collected.

  /// Called by e2_entity's timeout timer (on the E2 executor) when the deadline fires
  /// before all expected pairs have arrived.  Fires the event with whatever was collected.
  virtual void on_timeout() = 0;
};


} // namespace ocudu
