// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: apps/units/o_cu_cp/e2/o_cu_cp_e2_config.h  (23 lines)
//
// Purpose (plain English):
//   E2 config + E2AP PCAP config for the CU-CP E2 agent. Mirrors o_du_high_e2_config.h but for the CU-CP unit (--enable_cu_cp_e2 flag).
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "apps/helpers/e2/e2_appconfig.h"


namespace ocudu {

/// O-RAN CU-CP E2 PCAP configuration.

/// O-RAN CU-CP E2 PCAP configuration.
struct o_cu_cp_e2_pcap_config {
  std::string filename = "/tmp/cu_cp_e2ap.pcap";
  bool        enabled  = false;
};

/// O-RAN CU-CP E2 configuration.

/// O-RAN CU-CP E2 configuration.
struct o_cu_cp_e2_config {
  e2_config              base_config;
  o_cu_cp_e2_pcap_config pcaps;
};


} // namespace ocudu
