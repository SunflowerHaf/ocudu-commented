// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ngap/procedures/ngap_dl_ran_status_transfer_procedure.h  (36 lines)
//
// LIBRARY: lib/ngap
// NG Application Protocol (NGAP, TS 38.413): the N2 control-plane between the gNB and the 5G Core AMF. Handles UE registration, PDU session setup, handover, paging, NAS message transport, and NG Setup. Implements full ASN.1 encode/decode + all NGAP elementary procedures.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ue_context/ngap_ue_logger.h"
#include "ue_context/ngap_ue_transaction_manager.h"
#include "ocudu/cu_cp/inter_cu_handover_messages.h"
#include "ocudu/support/async/async_task.h"


namespace ocudu::ocucp {

/// Procedure used to await for the DL status

/// Procedure used to await for the DL status
class ngap_dl_ran_status_transfer_procedure
{
public:
  ngap_dl_ran_status_transfer_procedure(ngap_ue_transaction_manager& ev_mng, ngap_ue_logger& logger_);


  void operator()(coro_context<async_task<expected<cu_cp_status_transfer>>>& ctx);


private:
  static const char* name() { return "DL RAN Status Transfer Procedure"; }
  bool               fill_ngap_dl_ran_status_transfer();


  ngap_ue_transaction_manager& ev_mng;
  ngap_ue_logger&              logger;


  cu_cp_ue_index_t      ue_index;
  cu_cp_status_transfer dl_ran_status_transfer;


  protocol_transaction_outcome_observer<asn1::ngap::dl_ran_status_transfer_s> transaction_sink;
  protocol_transaction_outcome_observer<asn1::ngap::ho_cancel_ack_s> dl_status_transfer_cancel_transaction_sink;
};


} // namespace ocudu::ocucp
