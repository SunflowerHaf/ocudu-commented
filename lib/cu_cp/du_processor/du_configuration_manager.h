// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/cu_cp/du_processor/du_configuration_manager.h  (48 lines)
//
// LIBRARY: lib/cu_cp
// O-RAN Central Unit Control Plane core (~160 files, ~23k lines): full CU-CP implementation. Contains: CU-CP manager and UE manager, NGAP procedures (UE registration, PDU session, handover), F1AP CU-side procedures, E1AP CU-CP side, RRC procedures (setup, reconfiguration, measurement, handover), security context management, mobility manager, cell measurement manager, UE location manager, and the O-CU-CP factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "du_configuration_handler.h"
#include "ocudu/f1ap/cu_cp/f1ap_cu_configuration_update.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/ran/plmn_identity.h"


namespace ocudu::ocucp {

/// Validator and repository of configurations for DUs handled by the CU-CP.

/// Validator and repository of configurations for DUs handled by the CU-CP.
class du_configuration_manager
{
public:
  du_configuration_manager(const gnb_id_t& gnb_id_, const std::vector<plmn_identity>& plmns_);

  /// Create a new DU configuration handler.

  /// Create a new DU configuration handler.
  std::unique_ptr<du_configuration_handler> create_du_handler();


  size_t nof_dus() const { return dus.size(); }


private:
  class du_configuration_handler_impl;


  using validation_result = error_type<du_setup_result::rejected>;


  expected<const du_configuration_context*, du_setup_result::rejected> add_du_config(const du_setup_request& req);
  expected<const du_configuration_context*, du_setup_result::rejected>
       handle_du_config_update(const du_configuration_context& current_ctxt, const du_config_update_request& req);
  void rem_du(gnb_du_id_t du_id);


  void handle_gnb_cu_configuration_update(const f1ap_gnb_cu_configuration_update& req, gnb_du_id_t du_id);


  validation_result validate_new_du_config(const du_setup_request& req) const;
  validation_result validate_du_config_update(const du_config_update_request& req) const;
  validation_result validate_cell_config_request(const cu_cp_du_served_cells_item& served_cell) const;


  const gnb_id_t                   gnb_id;
  const std::vector<plmn_identity> plmns;
  ocudulog::basic_logger&          logger;


  std::unordered_map<gnb_du_id_t, du_configuration_context> dus;
};


} // namespace ocudu::ocucp
