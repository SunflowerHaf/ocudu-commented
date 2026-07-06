// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/f1u/split_connector/f1u_session_manager_factory.h  (14 lines)
//
// INTERFACE HEADER — include/ocudu/f1u
// F1-U interface headers: the DU-side and CU-UP-side F1-U gateway abstractions, the f1u_du_gateway and f1u_cu_up_gateway interfaces, and the TEID (tunnel endpoint) pool interface used to allocate unique tunnel identifiers.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/f1u/split_connector/f1u_session_manager.h"


namespace ocudu {

/// \brief Creates an F1-U bearer for the CU-UP.

/// \brief Creates an F1-U bearer for the CU-UP.
std::unique_ptr<f1u_session_manager> create_f1u_cu_up_session_manager(const f1u_session_maps& f1u_sessions);


} // namespace ocudu
