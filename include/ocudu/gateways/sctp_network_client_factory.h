// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gateways/sctp_network_client_factory.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/gateways
// Generic network gateway interfaces: sctp_network_gateway (for control-plane connections), udp_network_gateway (for user-plane), io_broker (non-blocking I/O event dispatch), network_gateway_config types, and the timer-driven reconnection framework.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include "ocudu/gateways/sctp_network_client.h"
#include "ocudu/gateways/sctp_network_gateway.h"


namespace ocudu {


class task_executor;

/// Configuration of an SCTP client.

/// Configuration of an SCTP client.
struct sctp_network_client_config {
  sctp_network_connector_config sctp;
  io_broker&                    broker;
  task_executor&                io_rx_executor;
};

/// Creates an SCTP network client.

/// Creates an SCTP network client.
std::unique_ptr<sctp_network_client> create_sctp_network_client(const sctp_network_client_config& config);


} // namespace ocudu
