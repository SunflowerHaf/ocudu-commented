// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/xnap/gateways/xnc_network_gateway_factory.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/xnap
// XnAP interface headers: xnc_connection_gateway (the Xn socket connection interface), XnAP message handler interfaces for the handover and Xn Setup procedures.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gateways/sctp_network_gateway.h"
#include "ocudu/xnap/gateways/xnc_connection_gateway.h"


namespace ocudu {


class dlt_pcap;
class io_broker;
class task_executor;

/// Configuration of an SCTP-based XN-C Gateway.

/// Configuration of an SCTP-based XN-C Gateway.
struct xnc_sctp_gateway_config {
  /// SCTP configuration.
  /// SCTP configuration.
  sctp_network_gateway_config sctp;
  /// IO broker responsible for handling SCTP Rx data and notifications.
  /// IO broker responsible for handling SCTP Rx data and notifications.
  io_broker& broker;
  /// Execution context used to process received SCTP packets.
  /// Execution context used to process received SCTP packets.
  task_executor& io_rx_executor;
  /// CU-CP control executor to process SCTP notifications deffered back from io_broker executor.
  /// CU-CP control executor to process SCTP notifications deffered back from io_broker executor.
  task_executor& ctrl_exec;
  /// PCAP writer for the XNAP messages.
  /// PCAP writer for the XNAP messages.
  dlt_pcap& pcap;
};

/// Creates an XN-C Gateway server that listens for incoming SCTP connections, packs/unpacks XNAP PDUs and forwards
/// them to the GW/CU-CP XNAP handler.

/// Creates an XN-C Gateway server that listens for incoming SCTP connections, packs/unpacks XNAP PDUs and forwards
/// them to the GW/CU-CP XNAP handler.
std::unique_ptr<ocucp::xnc_connection_gateway> create_xnc_connection_gateway(const xnc_sctp_gateway_config& cfg);


} // namespace ocudu
