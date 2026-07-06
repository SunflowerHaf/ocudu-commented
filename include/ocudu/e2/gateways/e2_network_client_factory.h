// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/gateways/e2_network_client_factory.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/gateways/e2_connection_client.h"
#include "ocudu/gateways/sctp_network_gateway.h"


namespace ocudu {


class dlt_pcap;
class io_broker;
class task_executor;


struct e2_sctp_gateway_config {
  /// SCTP configuration.
  /// SCTP configuration.
  sctp_network_connector_config sctp;
  /// IO broker responsible for handling SCTP Rx data and notifications.
  /// IO broker responsible for handling SCTP Rx data and notifications.
  io_broker& broker;
  /// Execution context used to process received SCTP packets.
  /// Execution context used to process received SCTP packets.
  task_executor& io_rx_executor;
  /// PCAP writer for the E2AP messages.
  /// PCAP writer for the E2AP messages.
  dlt_pcap& pcap;
  /// Logger.
  /// Logger.
  ocudulog::basic_logger& logger;
};

/// \brief Create an E2AP gateway connector that the DU can use to connect to the Near-RT RIC.

/// \brief Create an E2AP gateway connector that the DU can use to connect to the Near-RT RIC.
std::unique_ptr<e2_connection_client> create_e2_gateway_client(const e2_sctp_gateway_config& params);


} // namespace ocudu
