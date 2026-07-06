// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config_translators.cpp
//
// Purpose (plain English):
//   Implements the two translator functions declared in the header.
//
//   generate_e2_config():
//     Starts from a default e2ap_configuration (produced by the shared
//     config_helpers::make_default_e2ap_config() helper), then overlays the
//     user's choices: gNB ID, PLMN, optional DU ID, and the three E2SM
//     module enable flags:
//       e2sm_kpm_enabled — Key Performance Measurements (per-UE KPIs).
//       e2sm_rc_enabled  — RAN Control (the RIC pushes RRM decisions down).
//       e2sm_ccc_enabled — Cell Configuration Control.
//
//   fill_o_du_high_e2_worker_manager_config():
//     If E2AP PCAP capture is enabled, sets is_e2ap_enabled in the worker
//     manager's PCAP config block. The worker manager then creates a dedicated
//     executor for PCAP writes so they don't block the E2 processing thread.
// =============================================================================

#include "o_du_high_e2_config_translators.h"
#include "apps/services/worker_manager/worker_manager_config.h"
#include "o_du_high_e2_config.h"
#include "ocudu/e2/e2ap_configuration_helpers.h"


using namespace ocudu;


e2ap_configuration ocudu::generate_e2_config(const o_du_high_e2_config& config,
                                             gnb_id_t                   gnb_id,
                                             const std::string&         plmn,
                                             std::optional<gnb_du_id_t> gnb_du_id)
{
  // Start from the library's defaults (RIC port 36421, reasonable timeouts).
  e2ap_configuration out_cfg = config_helpers::make_default_e2ap_config();

  // Identity fields — needed by the E2 Setup Request sent to the near-RT RIC.
  out_cfg.gnb_id             = gnb_id;
  out_cfg.plmn               = plmn;
  out_cfg.gnb_du_id          = gnb_du_id;

  // E2 Service Model enable flags. Each flag causes the E2 Setup Request to
  // include the corresponding E2SM in the list of supported service models.
  out_cfg.e2sm_kpm_enabled   = config.base_cfg.e2sm_kpm_enabled; // KPI measurement reports.
  out_cfg.e2sm_rc_enabled    = config.base_cfg.e2sm_rc_enabled; // RAN control (RIC pushes RRM).
  out_cfg.e2sm_ccc_enabled   = config.base_cfg.e2sm_ccc_enabled; // Cell config control.


  return out_cfg;
}

void ocudu::fill_o_du_high_e2_worker_manager_config(worker_manager_config& config, const o_du_high_e2_config& unit_cfg)

{
  // Only create the E2AP PCAP executor if the user enabled E2AP capture.
  // (The autoderive step already forced pcaps.enabled=false if E2 is off.)
  auto& pcap_cfg = config.pcap_cfg;
  if (unit_cfg.pcaps.enabled) {
    pcap_cfg.is_e2ap_enabled = true;
  }
}
