// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gateways/sctp_network_server_factory.cpp  (13 lines)
//
// LIBRARY: lib/gateways
// Network transport gateway implementations: the SCTP-based control-plane socket (used for F1AP, NGAP, XNAP, E1AP, E2AP) and the UDP-based user-plane socket (GTP-U). Wraps the OS socket API behind clean interfaces so the protocol stacks above never touch raw sockets.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#include "ocudu/gateways/sctp_network_server_factory.h"
#include "sctp_network_server_impl.h"


using namespace ocudu;


std::unique_ptr<sctp_network_server> ocudu::create_sctp_network_server(const sctp_network_server_config& config)
{
  return sctp_network_server_impl::create(
      config.sctp, config.broker, config.io_rx_executor, config.app_exec, config.association_handler_factory);
}
