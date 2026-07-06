// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/rrc/rrc_du_factory.cpp  (15 lines)
//
// LIBRARY: lib/rrc
// Radio Resource Control (RRC, TS 38.331): manages the UE's radio state (RRC_IDLE, RRC_INACTIVE, RRC_CONNECTED), cell (re)selection, measurement configuration, handover preparation, SIB generation, security context handling, and system information updates. Implemented entirely in the CU-CP.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/rrc/rrc_du_factory.h"
#include "rrc_du_impl.h"
#include "ocudu/rrc/rrc_config.h"


using namespace ocudu;
using namespace ocucp;


std::unique_ptr<rrc_du> ocudu::ocucp::create_rrc_du(const rrc_cfg_t& cfg)
{
  return std::make_unique<rrc_du_impl>(cfg);
}
