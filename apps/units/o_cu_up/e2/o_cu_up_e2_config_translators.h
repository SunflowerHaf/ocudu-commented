// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_up/e2/o_cu_up_e2_config_translators.h  (25 lines)
//
// Purpose (plain English):
//   Translates CU-UP E2 config to e2ap_configuration; declares fill_o_cu_up_e2_worker_manager_config().
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/e2/e2ap_configuration.h"
#include "ocudu/ran/gnb_cu_up_id.h"


namespace ocudu {


struct e2_config;
struct o_cu_up_e2_config;
struct worker_manager_config;

/// Generate E2AP configuration from the given E2 configuration.

/// Generate E2AP configuration from the given E2 configuration.
e2ap_configuration generate_e2_config(const e2_config&              config,
                                      gnb_id_t                      gnb_id,
                                      const std::string&            plmn,
                                      std::optional<gnb_cu_up_id_t> gnb_cu_up_id);

/// Fills the O-RAN CU UP E2 worker manager parameters of the given worker manager configuration.

/// Fills the O-RAN CU UP E2 worker manager parameters of the given worker manager configuration.
void fill_o_cu_up_e2_worker_manager_config(worker_manager_config& config, const o_cu_up_e2_config& unit_cfg);


} // namespace ocudu
