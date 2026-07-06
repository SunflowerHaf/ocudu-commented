// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rrc/rrc_config.h  (35 lines)
//
// INTERFACE HEADER — include/ocudu/rrc
// RRC interface headers: the rrc_ue (per-UE RRC state machine interface), rrc_cell_manager, rrc_measurement_config types, rrc_pdu_handler, and the RRC↔NGAP and RRC↔PDCP notifier interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_cp_types.h"
#include "ocudu/ran/gnb_id.h"
#include "ocudu/ran/qos/five_qi.h"
#include "ocudu/rrc/rrc_ue_config.h"
#include "ocudu/security/security.h"
#include <map>


namespace ocudu::ocucp {


struct rrc_cfg_t {
  /// The gNodeB identifier to use for measurement configs.
  /// The gNodeB identifier to use for measurement configs.
  gnb_id_t gnb_id;
  /// PDCP config to use when UE SRB2 are configured.
  /// PDCP config to use when UE SRB2 are configured.
  srb_pdcp_config srb2_cfg;
  /// Configuration for available 5QI.
  /// Configuration for available 5QI.
  std::map<five_qi_t, cu_cp_qos_config> drb_config;
  /// Integrity protection algorithms preference list
  /// Integrity protection algorithms preference list
  security::preferred_integrity_algorithms int_algo_pref_list{security::integrity_algorithm::nia0};
  /// Encryption algorithms preference list
  /// Encryption algorithms preference list
  security::preferred_ciphering_algorithms enc_algo_pref_list{security::ciphering_algorithm::nea0};
  /// Force re-establishment fallback.
  /// Force re-establishment fallback.
  bool force_reestablishment_fallback = false;
  /// Force resume fallback.
  /// Force resume fallback.
  bool force_resume_fallback = false;
  /// Guard time for RRC procedures.
  /// Guard time for RRC procedures.
  std::chrono::milliseconds rrc_procedure_guard_time_ms{500};
};


} // namespace ocudu::ocucp
