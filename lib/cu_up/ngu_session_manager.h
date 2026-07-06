// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_up/ngu_session_manager.h  (18 lines)
//
// LIBRARY: lib/cu_up
// O-RAN Central Unit User Plane core: the PDCP layer (ciphering, integrity, header compression), SDAP (QoS flow to DRB mapping), F1-U endpoint management, N3 GTP-U endpoint, and the O-CU-UP factory. One CU-UP instance handles all UEs' user-plane data.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/gtpu/gtpu_gateway.h"


namespace ocudu::ocuup {


class ngu_session_manager
{
public:
  virtual ~ngu_session_manager()                       = default;
  virtual gtpu_tnl_pdu_session& get_next_ngu_gateway() = 0;
};


} // namespace ocudu::ocuup
