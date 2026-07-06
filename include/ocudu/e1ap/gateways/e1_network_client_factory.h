// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/gateways/e1_network_client_factory.h  (31 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e1ap/gateways/e1_connection_client.h"
#include "ocudu/gateways/sctp_network_gateway.h"


namespace ocudu {


class dlt_pcap;
class io_broker;
class task_executor;

/// Configuration of an SCTP-based E1 Gateway in the CU-UP.

/// Configuration of an SCTP-based E1 Gateway in the CU-UP.
struct e1_cu_up_sctp_gateway_config {
  /// SCTP configuration.
  /// SCTP configuration.
  sctp_network_connector_config sctp;
  /// IO broker responsible for handling SCTP Rx data and notifications.
  /// IO broker responsible for handling SCTP Rx data and notifications.
  io_broker& broker;
  /// Execution context used to process received SCTP packets.
  /// Execution context used to process received SCTP packets.
  task_executor& io_rx_executor;
  /// PCAP writer for the E1AP messages.
  /// PCAP writer for the E1AP messages.
  dlt_pcap& pcap;
};

/// \brief Create an E1 gateway connector that the CU-UP can use to connect to the CU-CP.

/// \brief Create an E1 gateway connector that the CU-UP can use to connect to the CU-CP.
std::unique_ptr<ocuup::e1_connection_client> create_e1_gateway_client(const e1_cu_up_sctp_gateway_config& params);


} // namespace ocudu
