// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/cu_cp/cu_cp_ue_messages.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/cu_cp
// CU-CP public interfaces: the abstract classes that the CU-CP exposes to the rest of the system. Key interfaces: cu_cp (the top-level factory and lifecycle), cu_cp_operation_controller (start/stop), n2_connection_client (NGAP socket management), cu_configurator (SSB/RRM/SIB remote changes), and the UE management interfaces.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/cu_cp/up_context.h"
#include "ocudu/rrc/meas_types.h"
#include "ocudu/security/security.h"
#include <optional>


namespace ocudu::ocucp {

/// \brief RRC context transfered from one UE object to the other during mobility.

/// \brief RRC context transfered from one UE object to the other during mobility.
struct rrc_ue_transfer_context {
  security::security_context            sec_context;
  std::optional<rrc_meas_cfg>           meas_cfg;
  up_context                            up_ctx;
  static_vector<srb_id_t, MAX_NOF_SRBS> srbs; // List of active SRBs (TODO: add PDCP config).
  byte_buffer                           handover_preparation_info;
  byte_buffer                           ue_cap_rat_container_list;
  bool                                  is_inter_cu_handover = false;
};


} // namespace ocudu::ocucp
