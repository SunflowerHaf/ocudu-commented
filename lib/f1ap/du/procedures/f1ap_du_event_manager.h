// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/procedures/f1ap_du_event_manager.h  (38 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/asn1/f1ap/f1ap.h"
#include "ocudu/support/async/event_signal.h"
#include "ocudu/support/async/protocol_transaction_manager.h"


namespace ocudu {
namespace odu {

/// Response type of a F1AP DU transaction.

/// Response type of a F1AP DU transaction.
using f1ap_transaction_response = expected<asn1::f1ap::successful_outcome_s, asn1::f1ap::unsuccessful_outcome_s>;

/// F1AP protocol transaction type.

/// F1AP protocol transaction type.
using f1ap_transaction = protocol_transaction<f1ap_transaction_response>;


class f1ap_event_manager
{
  /// Transaction Response Container, which gets indexed by transaction_id.
  /// Transaction Response Container, which gets indexed by transaction_id.
  static constexpr size_t MAX_NOF_TRANSACTIONS = 256;


public:
  protocol_transaction_manager<f1ap_transaction_response> transactions;

  /// F1 UE Context Modification Outcome

  /// F1 UE Context Modification Outcome
  using f1ap_ue_context_modification_outcome_t =
      expected<const asn1::f1ap::ue_context_mod_confirm_s*, const asn1::f1ap::ue_context_mod_refuse_s*>;
  event_signal<f1ap_ue_context_modification_outcome_t> f1ap_ue_context_modification_outcome;


  explicit f1ap_event_manager(timer_factory timer_service) : transactions(MAX_NOF_TRANSACTIONS, timer_service) {}
};


} // namespace odu
} // namespace ocudu
