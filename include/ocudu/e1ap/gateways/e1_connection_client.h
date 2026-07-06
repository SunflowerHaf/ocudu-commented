// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/gateways/e1_connection_client.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e1ap/common/e1ap_common.h"
#include <memory>


namespace ocudu {
namespace ocuup {

/// Interface used by the CU-UP to establish a new connection with a CU-CP via the E1 interface.

/// Interface used by the CU-UP to establish a new connection with a CU-CP via the E1 interface.
class e1_connection_client
{
public:
  virtual ~e1_connection_client() = default;

  /// Establish a new connection with a CU-CP.
  ///
  /// \param cu_up_rx_pdu_notifier Notifier that will be used to forward the E1AP PDUs sent by the CU-CP to the CU-UP.
  /// \return Notifier that the CU-UP can use to send E1AP Tx PDUs to the CU-CP it connected to.

  /// Establish a new connection with a CU-CP.
  ///
  /// \param cu_up_rx_pdu_notifier Notifier that will be used to forward the E1AP PDUs sent by the CU-CP to the CU-UP.
  /// \return Notifier that the CU-UP can use to send E1AP Tx PDUs to the CU-CP it connected to.
  virtual std::unique_ptr<e1ap_message_notifier>
  handle_cu_up_connection_request(std::unique_ptr<e1ap_message_notifier> cu_up_rx_pdu_notifier) = 0;
};


} // namespace ocuup
} // namespace ocudu
