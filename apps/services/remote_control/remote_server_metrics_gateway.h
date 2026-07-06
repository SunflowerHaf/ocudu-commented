// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: services/remote_control/remote_server_metrics_gateway.h
//
// Purpose (plain English):
//   Abstract interface for pushing metric JSON strings to the HTTP remote-control clients. Implemented by the remote_server. Consumers call send(json_string) to emit metrics over HTTP.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <string>


namespace ocudu {
namespace app_services {

/// Remote server metrics gateway.

/// Remote server metrics gateway.
class remote_server_metrics_gateway
{
public:
  virtual ~remote_server_metrics_gateway() = default;

  /// Sends the given metrics through the gateway.

  /// Sends the given metrics through the gateway.
  virtual void send(std::string metrics) = 0;
};


} // namespace app_services
} // namespace ocudu
