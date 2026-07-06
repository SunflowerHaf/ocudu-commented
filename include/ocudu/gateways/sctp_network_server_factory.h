// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gateways/sctp_network_server_factory.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/gateways
// Generic network gateway interfaces: sctp_network_gateway (for control-plane connections), udp_network_gateway (for user-plane), io_broker (non-blocking I/O event dispatch), network_gateway_config types, and the timer-driven reconnection framework.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/gateways/sctp_network_gateway.h"
#include "ocudu/gateways/sctp_network_server.h"


namespace ocudu {


class task_executor;

/// Configuration of an SCTP server.

/// Configuration of an SCTP server.
struct sctp_network_server_config {
  sctp_network_gateway_config       sctp;
  io_broker&                        broker;
  task_executor&                    io_rx_executor;
  task_executor&                    app_exec;
  sctp_network_association_factory& association_handler_factory;
};

/// Creates and starts an SCTP network node that can operate both as a server and client and create new SCTP
/// associations.

/// Creates and starts an SCTP network node that can operate both as a server and client and create new SCTP
/// associations.
std::unique_ptr<sctp_network_server> create_sctp_network_server(const sctp_network_server_config& config);


} // namespace ocudu
