// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gateways/udp_network_gateway_factory.cpp  (13 lines)
//
// LIBRARY: lib/gateways
// Network transport gateway implementations: the SCTP-based control-plane socket (used for F1AP, NGAP, XNAP, E1AP, E2AP) and the UDP-based user-plane socket (GTP-U). Wraps the OS socket API behind clean interfaces so the protocol stacks above never touch raw sockets.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/gateways/udp_network_gateway_factory.h"
#include "udp_network_gateway_impl.h"


using namespace ocudu;


std::unique_ptr<udp_network_gateway> ocudu::create_udp_network_gateway(const udp_network_gateway_creation_message& msg)
{
  return std::make_unique<udp_network_gateway_impl>(
      msg.config, msg.data_notifier, msg.io_tx_executor, msg.io_rx_executor);
}
