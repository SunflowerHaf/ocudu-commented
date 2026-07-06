// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1u/du/split_connector/f1u_split_connector_factory.cpp  (14 lines)
//
// LIBRARY: lib/f1u
// F1-U user-plane interface: the GTP-U-based data path between the DU and the CU-UP. Implements the DU-side and CU-UP-side endpoints, TEID management, flow mapping, and the connector that links F1-U sockets to the PDCP and RLC layers.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/f1u/du/split_connector/f1u_split_connector_factory.h"
#include "f1u_split_connector.h"


using namespace ocudu;
using namespace odu;


std::unique_ptr<f1u_du_udp_gateway> ocudu::odu::create_split_f1u_gw(f1u_du_split_gateway_creation_msg msg)
{
  return std::make_unique<f1u_split_connector>(msg.udp_gw_maps, msg.demux, msg.gtpu_pcap, msg.peer_port);
}
