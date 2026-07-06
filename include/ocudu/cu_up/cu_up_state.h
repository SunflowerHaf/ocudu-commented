// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_up/cu_up_state.h  (18 lines)
//
// INTERFACE HEADER — include/ocudu/cu_up
// CU-UP public interfaces: o_cu_up (top-level), cu_up_operation_controller, the GTP-U tunnel management interface, and the N3 endpoint interface. These are the seams between the CU-UP library and the application layer above it.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_up/cu_up_types.h"
#include <map>
#include <set>


namespace ocudu::ocuup {

/// Useful typedef's to get the current state of the CU-UP.

/// Useful typedef's to get the current state of the CU-UP.
using drb_state_t         = std::map<drb_id_t, std::set<qos_flow_id_t>>;
using pdu_session_state_t = std::map<pdu_session_id_t, drb_state_t>;
using up_state_t          = std::map<cu_up_ue_index_t, pdu_session_state_t>;


} // namespace ocudu::ocuup
