// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/network/udp_appconfig.h
//
// Purpose (plain English):
//   Configuration for UDP gateways (used by F1-U GTP-U sockets).
//
//   rx_max_msgs / tx_max_msgs — how many UDP datagrams to process per
//     syscall (recvmmsg / sendmmsg). Higher = more efficient, more latency.
//   tx_qsize — outbound queue depth. Increase if bursts cause drops.
//   tx_max_segments — max scatter-gather segments per TX SDU.
//   pool_threshold — the fraction [0..1] of the buffer pool that must be
//     free before a packet is accepted. Packets arriving when the pool is
//     too full are dropped to prevent head-of-line blocking.
//   dscp — Differentiated Services Code Point to set on outgoing packets
//     for QoS prioritisation in the network.
//   reuse_addr — allows multiple sockets to bind the same port (SO_REUSEADDR).
//   ext_addr — the external IP address advertised to the peer (for NAT
//     traversal). "auto" derives it from the local bind address.
// =============================================================================
#pragma once

#include <optional>
#include <string>


namespace ocudu {

/// UDP specific configuration of an UDP gateway.
struct udp_appconfig {
  /// Maximum amount of messages RX in a single syscall.
  unsigned rx_max_msgs = 256; ///< Max datagrams per recvmmsg syscall.
  /// Batched queue size.
  unsigned tx_qsize = 4096; ///< Outbound queue depth.
  /// Maximum amount of messages TX in a single syscall.
  unsigned tx_max_msgs = 256; ///< Max datagrams per sendmmsg syscall.
  /// Maximum amount of segments in a single TX SDU.
  unsigned tx_max_segments = 256; ///< Max scatter-gather segments per TX SDU.
  /// Pool accupancy threshold after which packets are dropped.
  float pool_threshold = 0.9;
  /// Differentiated Services Code Point value.
  std::optional<unsigned> dscp; ///< DSCP value for outgoing packets (optional).
  /// Allow multiple sockets to re-use the bind port.
  bool reuse_addr = false; ///< Allow port reuse (SO_REUSEADDR).
  /// External address advertised by the UDP-GW.
  std::string ext_addr = "auto"; ///< External address advertised to peer.
};

} // namespace ocudu
