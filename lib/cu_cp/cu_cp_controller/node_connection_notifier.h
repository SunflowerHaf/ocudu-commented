// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/cu_cp_controller/node_connection_notifier.h  (24 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/ran/plmn_identity.h"
#include <set>


namespace ocudu::ocucp {

/// \brief Class responsible for notifying the CU-CP about DU node connections.

/// \brief Class responsible for notifying the CU-CP about DU node connections.
class du_connection_notifier
{
public:
  virtual ~du_connection_notifier() = default;

  /// \brief Notifies the CU-CP about a DU setup request.
  /// \return True if CU-CP accepts the request.

  /// \brief Notifies the CU-CP about a DU setup request.
  /// \return True if CU-CP accepts the request.
  virtual bool on_du_setup_request(cu_cp_du_index_t du_index, const std::set<plmn_identity>& plmn_ids) = 0;
};


} // namespace ocudu::ocucp
