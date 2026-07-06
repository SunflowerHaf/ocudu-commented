// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/o_cu_cp_impl.cpp  (44 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "o_cu_cp_impl.h"


using namespace ocudu;
using namespace ocucp;


o_cu_cp_impl::o_cu_cp_impl(std::unique_ptr<cu_cp> cu_cp_) : cu_impl(std::move(cu_cp_))
{
  ocudu_assert(cu_impl, "Invalid CU-CP");
}


void o_cu_cp_impl::start()
{
  cu_impl->start();
}


void o_cu_cp_impl::stop()
{
  cu_impl->stop();
}


o_cu_cp_with_e2_impl::o_cu_cp_with_e2_impl(std::unique_ptr<e2_agent>                         e2agent_,
                                           std::unique_ptr<cu_cp>                            cu_cp_,
                                           std::unique_ptr<cu_cp_ng_setup_complete_notifier> ng_setup_adapter_) :
  o_cu_cp_impl(std::move(cu_cp_)), ng_setup_e2_adapter(std::move(ng_setup_adapter_)), e2agent(std::move(e2agent_))
{
  ocudu_assert(e2agent, "Invalid E2 agent");
  ocudu_assert(ng_setup_e2_adapter, "Invalid NG setup E2 adapter");
}


void o_cu_cp_with_e2_impl::start()
{
  o_cu_cp_impl::start();
  e2agent->start();
}


void o_cu_cp_with_e2_impl::stop()
{
  e2agent->stop();
  o_cu_cp_impl::stop();
}
