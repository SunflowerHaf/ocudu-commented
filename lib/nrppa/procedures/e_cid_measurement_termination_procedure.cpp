// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/nrppa/procedures/e_cid_measurement_termination_procedure.cpp  (47 lines)
//
// LIBRARY: lib/nrppa
// NR Positioning Protocol A (NRPPa, TS 38.455): the interface between the gNB and the 5GC Location Management Function (LMF). Used for UE positioning (OTDOA, ECID measurements). Implements ASN.1 encode/decode + procedure state machines.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "e_cid_measurement_termination_procedure.h"
#include "ocudu/support/async/coroutine.h"


using namespace ocudu;
using namespace ocucp;


e_cid_measurement_termination_procedure::e_cid_measurement_termination_procedure(cu_cp_ue_index_t        ue_index_,
                                                                                 nrppa_ue_context_list&  ue_ctxt_list_,
                                                                                 ocudulog::basic_logger& logger_) :
  ue_index(ue_index_), ue_ctxt_list(ue_ctxt_list_), logger(logger_)
{
}


void e_cid_measurement_termination_procedure::operator()(coro_context<async_task<void>>& ctx)
{
  CORO_BEGIN(ctx);


  if (!ue_ctxt_list.contains(ue_index)) {
    logger.info("ue={}: Stopping \"{}\". UE was already removed", ue_index, name());
    CORO_EARLY_RETURN();
  }


  ue_ctxt = &ue_ctxt_list[ue_index];


  ue_ctxt->logger.log_debug("\"{}\" initialized", name());

  // Notify positioning manager about meas termination request.

  // Notify positioning manager about meas termination request.
  terminate_periodic_measurements();


  ue_ctxt->logger.log_debug("\"{}\" finished successfully", name());


  CORO_RETURN();
}


void e_cid_measurement_termination_procedure::terminate_periodic_measurements()
{
  // Remove stored information from UE context.
  // Remove stored information from UE context.
  ue_ctxt->meas_quantities.clear();
  ue_ctxt->meas_periodicity_ms = std::nullopt;

  // Stop timer for periodic reporting.

  // Stop timer for periodic reporting.
  ue_ctxt->meas_report_timer.stop();
}
