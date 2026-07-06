// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/cu_cp/f1ap_nrppa_msg_handling.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/positioning/positioning_messages.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// Handles incoming NRPPa messages to be transmitted over the F1 interface.

/// Handles incoming NRPPa messages to be transmitted over the F1 interface.
class f1ap_nrppa_message_handler
{
public:
  virtual ~f1ap_nrppa_message_handler() = default;

  /// Handles the given TRP information request message.

  /// Handles the given TRP information request message.
  virtual async_task<expected<trp_information_response_t, trp_information_failure_t>>
  handle_trp_information_request(const trp_information_request_t& request) = 0;

  /// Handles the given positioning information request message.

  /// Handles the given positioning information request message.
  virtual async_task<expected<positioning_information_response_t, positioning_information_failure_t>>
  handle_positioning_information_request(const positioning_information_request_t& request) = 0;

  /// Handles the given positioning activation request message.

  /// Handles the given positioning activation request message.
  virtual async_task<expected<positioning_activation_response_t, positioning_activation_failure_t>>
  handle_positioning_activation_request(const positioning_activation_request_t& request) = 0;

  /// Handles the given positioning measurement request message.

  /// Handles the given positioning measurement request message.
  virtual async_task<expected<measurement_response_t, measurement_failure_t>>
  handle_positioning_measurement_request(const measurement_request_t& request) = 0;
};


} // namespace ocudu::ocucp
