// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/remote_control/remote_control_appconfig.h
//
// Purpose (plain English):
//   Config for the HTTP remote-control server: enable toggle, bind address (default 127.0.0.1 — localhost only for security), port, and whether to expose JSON metrics over the same endpoint.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>
#include <string>


namespace ocudu {

/// Remote control application configuration.

/// Remote control application configuration.
struct remote_control_appconfig {
  bool        enabled                     = false;
  std::string bind_addr                   = "127.0.0.1";
  uint16_t    port                        = 8001;
  bool        enable_metrics_subscription = false;
};


} // namespace ocudu
