// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/paging/paging_message_handler.h  (31 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/cu_cp_types.h"


namespace ocudu::ocucp {


class du_processor_repository;
struct cu_cp_paging_message;

/// Class responsible for handling incoming paging messages and forwarding them to the appropriate DUs.

/// Class responsible for handling incoming paging messages and forwarding them to the appropriate DUs.
class paging_message_handler
{
public:
  paging_message_handler(du_processor_repository& dus_);

  /// Handle Paging message sent by the core network and distribute across the served DU cells.

  /// Handle Paging message sent by the core network and distribute across the served DU cells.
  void handle_paging_message(const cu_cp_paging_message& msg);


private:
  bool handle_du_paging_message(cu_cp_du_index_t du_index, const cu_cp_paging_message& msg);


  du_processor_repository& dus;
  ocudulog::basic_logger&  logger;
};


} // namespace ocudu::ocucp
