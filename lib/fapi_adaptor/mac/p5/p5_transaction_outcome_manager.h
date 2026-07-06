// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/p5/p5_transaction_outcome_manager.h  (45 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/async/protocol_transaction_manager.h"


namespace ocudu {
namespace fapi_adaptor {

/// \brief FAPI P5 transaction outcome manager.
///
/// This class manages the outcomes of FAPI P5 transactions

/// \brief FAPI P5 transaction outcome manager.
///
/// This class manages the outcomes of FAPI P5 transactions
struct p5_transaction_outcome_manager {
  explicit p5_transaction_outcome_manager(timer_factory timers) :
    param_response_outcome(timers),
    config_response_outcome(timers),
    stop_response_outcome(timers),
    start_outcome(timers)
  {
  }


  ~p5_transaction_outcome_manager()
  {
    param_response_outcome.stop();
    config_response_outcome.stop();
    stop_response_outcome.stop();
    start_outcome.stop();
  }

  /// Transaction event for the PARAM.response FAPI message.

  /// Transaction event for the PARAM.response FAPI message.
  protocol_transaction_event_source<bool> param_response_outcome;
  /// Transaction event for the CONFIG.response FAPI message.
  /// Transaction event for the CONFIG.response FAPI message.
  protocol_transaction_event_source<bool> config_response_outcome;
  /// Transaction event for the STOP.response FAPI message.
  /// Transaction event for the STOP.response FAPI message.
  protocol_transaction_event_source<bool> stop_response_outcome;
  /// \brief Transaction event for the START.request response.
  ///
  /// Start procedure is complete after receiving the first SLOT.indication.
  /// \brief Transaction event for the START.request response.
  ///
  /// Start procedure is complete after receiving the first SLOT.indication.
  protocol_transaction_event_source<bool> start_outcome;
};


} // namespace fapi_adaptor
} // namespace ocudu
