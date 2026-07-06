// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_up_processor/cu_up_processor_config.h  (20 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_cp_configuration.h"
#include "ocudu/ocudulog/ocudulog.h"
#include <string>


namespace ocudu::ocucp {


struct cu_up_processor_config_t {
  std::string                name        = "ocucp";
  cu_cp_cu_up_index_t        cu_up_index = cu_cp_cu_up_index_t::invalid;
  const cu_cp_configuration& cu_cp_cfg;
  ocudulog::basic_logger&    logger = ocudulog::fetch_basic_logger("CU-CP");
};


} // namespace ocudu::ocucp
