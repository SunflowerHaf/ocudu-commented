// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/gateways/f1c_network_client_factory.h  (30 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/f1ap/gateways/f1c_connection_client.h"
#include "ocudu/gateways/sctp_network_gateway.h"


namespace ocudu {


class dlt_pcap;
class io_broker;
class task_executor;


struct f1c_du_sctp_gateway_config {
  /// SCTP configuration.
  /// SCTP configuration.
  sctp_network_connector_config sctp;
  /// IO broker responsible for handling SCTP Rx data and notifications.
  /// IO broker responsible for handling SCTP Rx data and notifications.
  io_broker& broker;
  /// Execution context used to process received SCTP packets.
  /// Execution context used to process received SCTP packets.
  task_executor& io_rx_executor;
  /// PCAP writer for the F1AP messages.
  /// PCAP writer for the F1AP messages.
  dlt_pcap& pcap;
};

/// \brief Create an F1-C gateway connector that the DU can use to connect to the CU-CP.

/// \brief Create an F1-C gateway connector that the DU can use to connect to the CU-CP.
std::unique_ptr<odu::f1c_connection_client> create_f1c_gateway_client(const f1c_du_sctp_gateway_config& params);


} // namespace ocudu
