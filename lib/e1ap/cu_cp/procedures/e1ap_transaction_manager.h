// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/cu_cp/procedures/e1ap_transaction_manager.h  (30 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/expected.h"
#include "ocudu/asn1/e1ap/e1ap.h"
#include "ocudu/support/async/event_signal.h"
#include "ocudu/support/async/protocol_transaction_manager.h"
#include "ocudu/support/timers.h"


namespace ocudu {
namespace ocucp {


using e1ap_outcome     = expected<asn1::e1ap::successful_outcome_s, asn1::e1ap::unsuccessful_outcome_s>;
using e1ap_transaction = protocol_transaction<e1ap_outcome>;


class e1ap_transaction_manager
{
public:
  /// Transaction Response Container, which gets indexed by transaction_id.
  /// Transaction Response Container, which gets indexed by transaction_id.
  static constexpr size_t                    MAX_NOF_TRANSACTIONS = 256;
  protocol_transaction_manager<e1ap_outcome> transactions;


  explicit e1ap_transaction_manager(timer_factory timers) : transactions(MAX_NOF_TRANSACTIONS, timers) {}
};


} // namespace ocucp
} // namespace ocudu
