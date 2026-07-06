// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/cu_up/e1ap_cu_up_factory.cpp  (27 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/e1ap/cu_up/e1ap_cu_up_factory.h"
#include "e1ap_cu_up_impl.h"

/// Notice this would be the only place were we include concrete class implementation files.


/// Notice this would be the only place were we include concrete class implementation files.

using namespace ocudu;
using namespace ocuup;


std::unique_ptr<e1ap_interface> ocudu::ocuup::create_e1ap(cu_up_e1_index_t             e1_index_,
                                                          const e1ap_configuration&    e1ap_cfg_,
                                                          e1_connection_client&        e1_client_handler_,
                                                          e1ap_cu_up_manager_notifier& cu_up_notifier_,
                                                          timer_manager&               timers_,
                                                          task_executor&               cu_up_exec_)
{
  auto e1ap_cu_up = std::make_unique<e1ap_cu_up_impl>(e1_index_, // TODO: pass index through factory function.
                                                      e1ap_cfg_,
                                                      e1_client_handler_,
                                                      cu_up_notifier_,
                                                      timers_,
                                                      cu_up_exec_);
  return e1ap_cu_up;
}
