// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/f1ap/du/f1ap_du_factory.cpp  (21 lines)
//
// LIBRARY: lib/f1ap
// F1 Application Protocol (F1AP, TS 38.473): the control-plane between the DU and the CU-CP. Handles cell configuration (F1 Setup), UE context setup/modification/release, and handover. Separate sub-libraries for CU-side, DU-side, helpers, procedures, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/f1ap/du/f1ap_du_factory.h"
#include "f1ap_du_impl.h"


using namespace ocudu;
using namespace odu;


std::unique_ptr<f1ap_du> odu::create_f1ap(f1c_connection_client&   f1c_client_handler,
                                          f1ap_du_configurator&    du_mng,
                                          task_executor&           ctrl_exec,
                                          f1ap_ue_executor_mapper& ue_exec_mapper,
                                          f1ap_du_paging_notifier& paging_notifier,
                                          timer_manager&           timers)
{
  auto f1ap_du =
      std::make_unique<f1ap_du_impl>(f1c_client_handler, du_mng, ctrl_exec, ue_exec_mapper, paging_notifier, timers);
  return f1ap_du;
}
