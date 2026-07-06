// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/ue_context/f1ap_du_ue.cpp  (18 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "f1ap_du_ue.h"
#include "du/procedures/f1ap_du_ue_context_modification_procedure.h"
#include "du/procedures/f1ap_du_ue_context_setup_procedure.h"
#include "ocudu/f1ap/du/f1ap_du_ue_config.h"


using namespace ocudu;
using namespace ocudu::odu;


void f1ap_du_ue::handle_ue_context_modification_request(const asn1::f1ap::ue_context_mod_request_s& msg,
                                                        const f1ap_du_context&                      ctxt_)
{
  du_handler.get_ue_handler(context.ue_index)
      .schedule_async_task(launch_async<f1ap_du_ue_context_modification_procedure>(msg, *this, ctxt_));
}
