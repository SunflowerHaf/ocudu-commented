// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/gateways/e2_connection_client.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/e2.h"
#include <memory>


namespace ocudu {

/// Interface used by the E2 agent to establish a new connection with a ORAN Near Real-Time RIC.

/// Interface used by the E2 agent to establish a new connection with a ORAN Near Real-Time RIC.
class e2_connection_client
{
public:
  virtual ~e2_connection_client() = default;

  /// Establish a new connection with a Near Real-Time RIC.
  ///
  /// \param e2ap_rx_pdu_notifier Notifier that will be used to forward the E2AP PDUs sent by the RIC to the E2 Agent.
  /// \return Notifier that the E2 Agent can use to send E2AP Tx PDUs to the RIC it connected to.

  /// Establish a new connection with a Near Real-Time RIC.
  ///
  /// \param e2ap_rx_pdu_notifier Notifier that will be used to forward the E2AP PDUs sent by the RIC to the E2 Agent.
  /// \return Notifier that the E2 Agent can use to send E2AP Tx PDUs to the RIC it connected to.
  virtual std::unique_ptr<e2_message_notifier>
  handle_e2_connection_request(std::unique_ptr<e2_message_notifier> e2_rx_pdu_notifier) = 0;
};


} // namespace ocudu
