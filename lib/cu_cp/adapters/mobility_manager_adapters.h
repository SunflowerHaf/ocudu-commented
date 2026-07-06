// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/adapters/mobility_manager_adapters.h  (38 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../cu_cp_impl_interface.h"


namespace ocudu::ocucp {

/// Adapter between mobility manager and CU-CP to trigger handover.

/// Adapter between mobility manager and CU-CP to trigger handover.
class mobility_manager_adapter : public mobility_manager_cu_cp_notifier
{
public:
  mobility_manager_adapter() = default;


  void connect_cu_cp(cu_cp_mobility_manager_handler& cu_cp_handler_) { cu_cp_handler = &cu_cp_handler_; }


  async_task<cu_cp_intra_cu_handover_response>
  on_intra_cu_handover_required(const cu_cp_intra_cu_handover_request& request,
                                cu_cp_du_index_t                       source_du_index,
                                cu_cp_du_index_t                       target_du_index) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    return cu_cp_handler->handle_intra_cu_handover_request(request, source_du_index, target_du_index);
  }


  async_task<cu_cp_intra_cu_cho_response> on_intra_cu_cho_required(const cu_cp_intra_cu_cho_request& request) override
  {
    ocudu_assert(cu_cp_handler != nullptr, "CU-CP handler must not be nullptr");
    return cu_cp_handler->handle_intra_cu_cho_request(request);
  }


private:
  cu_cp_mobility_manager_handler* cu_cp_handler = nullptr;
};


} // namespace ocudu::ocucp
