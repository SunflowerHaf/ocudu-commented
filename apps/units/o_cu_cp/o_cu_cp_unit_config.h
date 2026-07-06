// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_cp/o_cu_cp_unit_config.h  (18 lines)
//
// Purpose (plain English):
//   Top-level config for the O-RAN CU-CP unit: aggregates cu_cp_unit_config (AMF connection, measurement/handover config, RRC, PDCP, PCAPs, logging, metrics) and o_cu_cp_e2_config (E2 agent for the CU-CP).
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "cu_cp/cu_cp_unit_config.h"
#include "e2/o_cu_cp_e2_config.h"


namespace ocudu {

/// O-RAN CU-CP application unit configuration.

/// O-RAN CU-CP application unit configuration.
struct o_cu_cp_unit_config {
  cu_cp_unit_config cucp_cfg;
  o_cu_cp_e2_config e2_cfg;
};


} // namespace ocudu
