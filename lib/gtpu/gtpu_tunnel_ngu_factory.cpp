// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gtpu/gtpu_tunnel_ngu_factory.cpp  (16 lines)
//
// LIBRARY: lib/gtpu
// GTP-U (GPRS Tunnelling Protocol for User Plane, TS 29.281) implementation. Creates and demultiplexes GTP-U tunnels on F1-U (DU↔CU-UP) and N3 (CU-UP↔UPF). Manages TEID (Tunnel Endpoint Identifier) allocation and per-tunnel routing tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/gtpu/gtpu_tunnel_ngu_factory.h"
#include "gtpu_tunnel_impl_ngu.h"

/// Notice this would be the only place were we include concrete class implementation files.


/// Notice this would be the only place were we include concrete class implementation files.

using namespace ocudu;


std::unique_ptr<gtpu_tunnel_ngu> ocudu::create_gtpu_tunnel_ngu(gtpu_tunnel_ngu_creation_message& msg)
{
  return std::make_unique<gtpu_tunnel_ngu_impl>(
      msg.ue_index, msg.cfg, *msg.gtpu_pcap, *msg.rx_lower, *msg.tx_upper, msg.ue_ctrl_timer_factory);
}
