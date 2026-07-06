// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e1ap/cu_cp/inactivity_notification.h  (19 lines)
//
// INTERFACE HEADER — include/ocudu/e1ap
// E1AP interface headers: abstract classes for the E1AP gateway (CU-CP side and CU-UP side), E1AP message handler interfaces, bearer context setup/modification/release request/response types.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/ran/cu_types.h"


namespace ocudu::ocucp {


struct e1ap_inactivity_notification {
  cu_cp_ue_index_t              ue_index    = cu_cp_ue_index_t::invalid;
  bool                          ue_inactive = false;
  std::vector<drb_id_t>         inactive_drbs;
  std::vector<pdu_session_id_t> inactive_pdu_sessions;
};


} // namespace ocudu::ocucp
