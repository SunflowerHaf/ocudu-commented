// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: helpers/network/sctp_appconfig.h
//
// Purpose (plain English):
//   Configuration knobs for SCTP (Stream Control Transmission Protocol)
//   sockets. SCTP is the transport layer used for all 3GPP control-plane
//   interfaces: F1AP, NGAP, E2AP, XnAP, E1AP. Unlike TCP it supports
//   multi-homing (binding to multiple IPs) and multi-streaming.
//
//   Every field has -1 as "use the operating system default". In practice:
//     rto_initial_ms / rto_min_ms / rto_max_ms — Retransmission TimeOut
//       bounds. Lower values detect link failures faster but cause more
//       spurious retransmissions on lossy links.
//     init_max_attempts / max_init_timeo_ms — how hard to try during the
//       SCTP association setup (INIT / INIT-ACK handshake).
//     hb_interval_ms — how often SCTP sends HEARTBEAT chunks to verify the
//       path is still alive. Default 30 s; reduce for faster failure detection.
//     assoc_max_retx — max retransmissions before declaring the association
//       dead and closing the socket.
//     nodelay — disables Nagle-like bundling; set true for latency-sensitive
//       interfaces like E2AP.
// =============================================================================
#pragma once

namespace ocudu {

/// Common SCTP socket option parameters shared across application configurations.
struct sctp_appconfig {
  /// SCTP initial RTO value in milliseconds (-1 to use system default).
  int rto_initial_ms = 120; ///< SCTP initial RTO (ms); -1 = OS default.
  /// SCTP RTO min in milliseconds (-1 to use system default).
  int rto_min_ms = 120; ///< SCTP minimum RTO (ms).
  /// SCTP RTO max in milliseconds (-1 to use system default).
  int rto_max_ms = 500; ///< SCTP maximum RTO (ms).
  /// SCTP init max attempts (-1 to use system default).
  int init_max_attempts = 3; ///< Max INIT retransmissions during setup.
  /// SCTP max init timeout in milliseconds (-1 to use system default).
  int max_init_timeo_ms = 500; ///< Max INIT wait (ms).
  /// SCTP heartbeat interval in milliseconds (-1 to use system default).
  int hb_interval_ms = 30000; ///< HEARTBEAT interval (ms).
  /// SCTP association max retransmissions (-1 to use system default).
  int assoc_max_retx = 10; ///< Max retransmissions before closing.
  /// Send SCTP messages as soon as possible without any Nagle-like algorithm.
  bool nodelay = false; ///< Disable Nagle bundling when true.
};

} // namespace ocudu
