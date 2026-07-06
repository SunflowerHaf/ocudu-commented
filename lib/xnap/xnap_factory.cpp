// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/xnap/xnap_factory.cpp  (21 lines)
//
// LIBRARY: lib/xnap
// Xn Application Protocol (XnAP, TS 38.423): the interface between peer gNBs for handover preparation, data forwarding setup, and interference coordination. Implements ASN.1 encode/decode + handover and Xn setup procedures.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/xnap/xnap_factory.h"
#include "xnap_impl.h"

/// Notice this would be the only place were we include concrete class implementation files.


/// Notice this would be the only place were we include concrete class implementation files.

using namespace ocudu;
using namespace ocucp;


std::unique_ptr<xnap_interface> ocudu::ocucp::create_xnap(xnc_peer_index_t          xnc_index,
                                                          const xnap_configuration& xnap_cfg_,
                                                          xnap_cu_cp_notifier&      cu_cp_notifier_,
                                                          timer_manager&            timers_,
                                                          task_executor&            ctrl_exec_)
{
  auto xnap = std::make_unique<xnap_impl>(xnc_index, xnap_cfg_, cu_cp_notifier_, timers_, ctrl_exec_);
  return xnap;
}
