// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/xnap/xnap_message_notifier.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/xnap
// XnAP interface headers: xnc_connection_gateway (the Xn socket connection interface), XnAP message handler interfaces for the handover and Xn Setup procedures.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu::ocucp {


struct xnap_message;

/// Notifier interface used to notify outgoing XNAP messages.

/// Notifier interface used to notify outgoing XNAP messages.
class xnap_message_notifier
{
public:
  virtual ~xnap_message_notifier() = default;

  /// This callback is invoked on each outgoing XNAP message aside the XN Setup request.

  /// This callback is invoked on each outgoing XNAP message aside the XN Setup request.
  virtual bool on_new_message(const xnap_message& msg) = 0;
};


} // namespace ocudu::ocucp
