// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/common/e1ap_common.h  (39 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct e1ap_message;

/// This interface is used to push the received E1AP PDUs to the CU-CP or CU-UP.

/// This interface is used to push the received E1AP PDUs to the CU-CP or CU-UP.
class e1ap_message_handler
{
public:
  virtual ~e1ap_message_handler() = default;

  /// Handle the incoming E1AP message.

  /// Handle the incoming E1AP message.
  virtual void handle_message(const e1ap_message& msg) = 0;
};

/// Interface used by E1AP to inform about events.

/// Interface used by E1AP to inform about events.
class e1ap_event_handler
{
public:
  virtual ~e1ap_event_handler()         = default;
  virtual void handle_connection_loss() = 0;
};

/// This interface notifies the reception of new E1AP messages over the E1AP interface.

/// This interface notifies the reception of new E1AP messages over the E1AP interface.
class e1ap_message_notifier
{
public:
  virtual ~e1ap_message_notifier() = default;

  /// This callback is invoked on each received E1AP message.

  /// This callback is invoked on each received E1AP message.
  virtual void on_new_message(const e1ap_message& msg) = 0;
};


} // namespace ocudu
