// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/gateways/addr_info.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/gateways
// Generic network gateway interfaces: sctp_network_gateway (for control-plane connections), udp_network_gateway (for user-plane), io_broker (non-blocking I/O event dispatch), network_gateway_config types, and the timer-driven reconnection framework.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

#pragma once


#include <netinet/in.h>


inline const char* ipproto_to_string(int protocol)
{
  switch (protocol) {
    case IPPROTO_SCTP:
      return "SCTP";
    case IPPROTO_UDP:
      return "UDP";
    case IPPROTO_IP:
      return "IP";
    case IPPROTO_IPV6:
      return "IPV6";
    case IPPROTO_ICMP:
      return "ICMP";
    case IPPROTO_TCP:
      return "TCP";
    default:
      break;
  }
  return "unknown protocol";
}
