// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/gateways/e1_network_server_factory.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e1ap/gateways/e1_connection_server.h"
#include "ocudu/gateways/sctp_network_gateway.h"


namespace ocudu {


class dlt_pcap;
class io_broker;
class task_executor;

/// Configuration of an SCTP-based E1 Gateway in the CU-CP.

/// Configuration of an SCTP-based E1 Gateway in the CU-CP.
struct e1_cu_cp_sctp_gateway_config {
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
  /// PCAP writer for the E1AP messages.
  /// PCAP writer for the E1AP messages.
  dlt_pcap& pcap;
};

/// Creates an E1 Gateway server that listens for incoming SCTP connections, packs/unpacks E1AP PDUs and forwards
/// them to the GW/CU-CP E1AP handler.

/// Creates an E1 Gateway server that listens for incoming SCTP connections, packs/unpacks E1AP PDUs and forwards
/// them to the GW/CU-CP E1AP handler.
std::unique_ptr<ocucp::e1_connection_server> create_e1_gateway_server(const e1_cu_cp_sctp_gateway_config& cfg);


} // namespace ocudu
