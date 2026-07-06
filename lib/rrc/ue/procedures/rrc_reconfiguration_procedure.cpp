// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/rrc/ue/procedures/rrc_reconfiguration_procedure.cpp  (75 lines)
//
// LIBRARY: lib/rrc
// Radio Resource Control (RRC, TS 38.331): manages the UE's radio state (RRC_IDLE, RRC_INACTIVE, RRC_CONNECTED), cell (re)selection, measurement configuration, handover preparation, SIB generation, security context handling, and system information updates. Implemented entirely in the CU-CP.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "rrc_reconfiguration_procedure.h"
#include "../rrc_asn1_helpers.h"
#include "ocudu/ran/cause/ngap_cause.h"


using namespace ocudu;
using namespace ocudu::ocucp;
using namespace asn1::rrc_nr;


rrc_reconfiguration_procedure::rrc_reconfiguration_procedure(rrc_ue_context_t&                            context_,
                                                             const rrc_reconfiguration_procedure_request& args_,
                                                             rrc_ue_reconfiguration_proc_notifier& rrc_ue_notifier_,
                                                             rrc_ue_event_manager&                 event_mng_,
                                                             rrc_ue_control_message_handler&       srb_notifier_,
                                                             rrc_ue_logger&                        logger_) :
  context(context_),
  args(args_),
  rrc_ue(rrc_ue_notifier_),
  event_mng(event_mng_),
  srb_notifier(srb_notifier_),
  logger(logger_)
{
  procedure_timeout = context.cell.timers.t311 + context.cfg.rrc_procedure_guard_time_ms;
}


void rrc_reconfiguration_procedure::operator()(coro_context<async_task<bool>>& ctx)
{
  CORO_BEGIN(ctx);


  if (context.state != rrc_state::connected) {
    logger.log_error("\"{}\" failed. UE is not RRC connected", name());
    CORO_EARLY_RETURN(false);
  }


  logger.log_debug("\"{}\" initialized", name());
  // create new transaction for RRC Reconfiguration procedure
  // create new transaction for RRC Reconfiguration procedure
  transaction = event_mng.transactions.create_transaction(procedure_timeout);


  if (args.radio_bearer_cfg.has_value()) {
    for (const rrc_srb_to_add_mod& srb_to_add_mod : args.radio_bearer_cfg->srb_to_add_mod_list) {
      srb_creation_message srb = {};
      srb.ue_index             = context.ue_index;
      srb.srb_id               = srb_to_add_mod.srb_id;
      srb_notifier.create_srb(srb);
    }
  }


  send_rrc_reconfiguration();
  CORO_AWAIT(transaction);


  if (transaction.has_response()) {
    logger.log_debug("\"{}\" finished successfully", name());
    procedure_result = true;
  } else {
    if (transaction.failure_cause() == protocol_transaction_failure::timeout) {
      logger.log_warning("\"{}\" timed out after {}ms", name(), procedure_timeout.count());
    } else {
      logger.log_info("\"{}\" cancelled", name());
    }
  }


  CORO_RETURN(procedure_result);
}


void rrc_reconfiguration_procedure::send_rrc_reconfiguration()
{
  dl_dcch_msg_s dl_dcch_msg;
  dl_dcch_msg.msg.set_c1().set_rrc_recfg();
  rrc_recfg_s& rrc_reconfig = dl_dcch_msg.msg.c1().rrc_recfg();
  fill_asn1_rrc_reconfiguration_msg(rrc_reconfig, transaction.id(), args);
  rrc_ue.on_new_dl_dcch(srb_id_t::srb1, dl_dcch_msg);
}
