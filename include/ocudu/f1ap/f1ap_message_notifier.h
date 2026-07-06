// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1ap/f1ap_message_notifier.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/f1ap
// F1AP interface headers: abstract classes for the F1AP gateway (CU-CP side and DU side), the F1-C connection client interface, F1AP message handler interfaces, and cell/UE context setup/modification/release types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {


struct f1ap_message;

/// Notifier interface used to notify outgoing F1AP messages.

/// Notifier interface used to notify outgoing F1AP messages.
class f1ap_message_notifier
{
public:
  virtual ~f1ap_message_notifier() = default;

  /// This callback is invoked on each outgoing F1AP message.

  /// This callback is invoked on each outgoing F1AP message.
  virtual void on_new_message(const f1ap_message& msg) = 0;
};


} // namespace ocudu
