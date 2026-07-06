// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gtpu/gtpu_echo_factory.cpp  (15 lines)
//
// LIBRARY: lib/gtpu
// GTP-U (GPRS Tunnelling Protocol for User Plane, TS 29.281) implementation. Creates and demultiplexes GTP-U tunnels on F1-U (DU↔CU-UP) and N3 (CU-UP↔UPF). Manages TEID (Tunnel Endpoint Identifier) allocation and per-tunnel routing tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/gtpu/gtpu_echo_factory.h"
#include "gtpu_echo_impl.h"

/// Notice this would be the only place were we include concrete class implementation files.


/// Notice this would be the only place were we include concrete class implementation files.

using namespace ocudu;


std::unique_ptr<gtpu_echo> ocudu::create_gtpu_echo(gtpu_echo_creation_message& msg)
{
  return std::make_unique<gtpu_echo_impl>(*msg.gtpu_pcap, *msg.tx_upper);
}
