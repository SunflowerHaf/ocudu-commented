// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rrc/rrc_du_factory.h  (22 lines)
//
// INTERFACE HEADER — include/ocudu/rrc
// RRC interface headers: the rrc_ue (per-UE RRC state machine interface), rrc_cell_manager, rrc_measurement_config types, rrc_pdu_handler, and the RRC↔NGAP and RRC↔PDCP notifier interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/rrc/rrc_config.h"
#include "ocudu/rrc/rrc_du.h"
#include "ocudu/rrc/rrc_ue.h"


namespace ocudu {


namespace ocucp {


struct ue_context;

/// Create an instance of an RRC entity

/// Create an instance of an RRC entity
std::unique_ptr<rrc_du> create_rrc_du(const rrc_cfg_t& cfg);


} // namespace ocucp


} // namespace ocudu
