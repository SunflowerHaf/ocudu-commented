// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/f1u/f1u_appconfig.h
//
// Purpose (plain English):
//   Configuration structs for the F1-U interface — the user-plane (data) link
//   between the DU and the CU-UP. F1-U carries GTP-U tunnels over UDP:
//   downlink packets flow from the CU-UP → DU, uplink from DU → CU-UP.
//
//   f1u_socket_appconfig — one UDP socket configuration. A single DU can run
//     multiple F1-U sockets, each bound to a different local address or
//     dedicated to a specific network slice (S-NSSAI) or QoS class (5QI).
//     If sst/sd/five_qi are absent, that socket is the default for everything.
//
//   f1u_sockets_appconfig — the full F1-U config: a shared bind/peer port plus
//     the list of socket configs above.
// =============================================================================
#pragma once

#include "apps/helpers/network/udp_appconfig.h"
#include "ocudu/gtpu/gtpu_config.h"
#include "ocudu/ran/qos/five_qi.h"
#include "ocudu/ran/s_nssai.h"
#include <vector>


namespace ocudu {

/// F1-U sockets configuration.

/// Per-socket F1-U configuration (one UDP socket).
struct f1u_socket_appconfig {
  /// Bind address used by the F1-U interface.
  std::string bind_addr = "127.0.10.1"; ///< Local address to bind this socket.
  /// If the S-NSSAI is not present, the socket will be used by default.
  /// Optional S-NSSAI slice specifier. If absent, this socket is the default.
  std::optional<uint8_t>  sst;
  std::optional<uint32_t> sd;
  /// If the 5QI is not present, the socket will be used by default.
  /// Optional 5QI for a QoS-specific socket. If absent, default socket.
  std::optional<five_qi_t> five_qi;
  udp_appconfig            udp_config; ///< UDP-level tuning (batch sizes, DSCP, pool threshold).
};

/// F1-U configuration.

/// Full F1-U socket configuration.
struct f1u_sockets_appconfig {
  /// Bind port used by the F1-U interface.
  uint16_t bind_port = GTPU_PORT; ///< Local port to receive DL GTP-U from CU-UP.
  /// Peer port used by the F1-U interface.
  uint16_t                          peer_port = GTPU_PORT; ///< Remote port on the CU-UP to send UL GTP-U to.
  std::vector<f1u_socket_appconfig> f1u_socket_cfg; ///< One entry per F1-U socket.
};


} // namespace ocudu
