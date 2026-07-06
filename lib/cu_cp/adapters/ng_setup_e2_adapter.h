// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/adapters/ng_setup_e2_adapter.h  (30 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/cu_cp/cu_cp_ng_setup_notifier.h"
#include "ocudu/e2/e2_node_component_config_collector.h"


namespace ocudu::ocucp {

/// Adapter that forwards NG setup completion to the E2 node-component-config collector.

/// Adapter that forwards NG setup completion to the E2 node-component-config collector.
class ng_setup_e2_adapter final : public cu_cp_ng_setup_complete_notifier
{
public:
  explicit ng_setup_e2_adapter(e2_node_component_config_collector& collector_) : collector(collector_) {}


  void on_ng_setup_complete(byte_buffer req, byte_buffer resp, std::string amf_name) override
  {
    collector.deliver(e2_node_component_interface_type::ng,
                      std::move(req),
                      std::move(resp),
                      e2_node_component_id{std::move(amf_name)});
  }


private:
  e2_node_component_config_collector& collector;
};


} // namespace ocudu::ocucp
