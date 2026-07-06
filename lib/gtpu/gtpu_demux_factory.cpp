// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gtpu/gtpu_demux_factory.cpp  (15 lines)
//
// LIBRARY: lib/gtpu
// GTP-U (GPRS Tunnelling Protocol for User Plane, TS 29.281) implementation. Creates and demultiplexes GTP-U tunnels on F1-U (DU↔CU-UP) and N3 (CU-UP↔UPF). Manages TEID (Tunnel Endpoint Identifier) allocation and per-tunnel routing tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/gtpu/gtpu_demux_factory.h"
#include "gtpu_demux_impl.h"


using namespace ocudu;


std::unique_ptr<gtpu_demux> ocudu::create_gtpu_demux(const gtpu_demux_creation_request& msg)
{
  report_fatal_error_if_not(msg.teid_linger_checker, "TEID linger checker is uninitialized");
  report_fatal_error_if_not(msg.gtpu_pcap, "CU-UP pcap is uninitialized");
  return std::make_unique<gtpu_demux_impl>(msg.cfg, *msg.teid_linger_checker, *msg.gtpu_pcap);
}
