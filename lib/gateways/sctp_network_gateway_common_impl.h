// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/gateways/sctp_network_gateway_common_impl.h  (60 lines)
//
// LIBRARY: lib/gateways
// Network transport gateway implementations: the SCTP-based control-plane socket (used for F1AP, NGAP, XNAP, E1AP, E2AP) and the UDP-based user-plane socket (GTP-U). Wraps the OS socket API behind clean interfaces so the protocol stacks above never touch raw sockets.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include "ocudu/gateways/sctp_network_gateway.h"
#include "ocudu/gateways/sctp_socket.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/support/io/io_broker.h"


struct addrinfo;


namespace ocudu {

/// Helper generator class that traverses a list of SCTP sockaddr param candidates (ipv4, ipv6, hostnames).

/// Helper generator class that traverses a list of SCTP sockaddr param candidates (ipv4, ipv6, hostnames).
class sockaddr_searcher
{
public:
  sockaddr_searcher(const std::string& address, int port, ocudulog::basic_logger& logger);
  sockaddr_searcher(const sockaddr_searcher&) = delete;
  sockaddr_searcher(sockaddr_searcher&&)      = delete;
  ~sockaddr_searcher();

  /// Get next candidate or nullptr of search has ended.

  /// Get next candidate or nullptr of search has ended.
  struct addrinfo* next();


private:
  struct addrinfo* results     = nullptr;
  struct addrinfo* next_result = nullptr;
};

/// This class holds common functionality to the SCTP network server and client implementations.

/// This class holds common functionality to the SCTP network server and client implementations.
class sctp_network_gateway_common_impl
{
public:
  sctp_network_gateway_common_impl(const sctp_network_gateway_config& cfg);
  ~sctp_network_gateway_common_impl();


protected:
  static constexpr uint32_t network_gateway_sctp_max_len = 9100;

  // Close socket and unsubscribe it from the io_broker.

  // Close socket and unsubscribe it from the io_broker.
  bool close_socket();

  // Creates an SCTP socket with the provided protocol.

  // Creates an SCTP socket with the provided protocol.
  [[nodiscard]] expected<sctp_socket> create_socket(int ai_family, int ai_socktype) const;


  bool create_and_bind_common();


  [[nodiscard]] bool validate_and_log_sctp_notification(span<const uint8_t> payload) const;


  const sctp_network_gateway_config node_cfg;
  ocudulog::basic_logger&           logger;


  sctp_socket socket;


  io_broker::subscriber io_sub;
};


} // namespace ocudu
