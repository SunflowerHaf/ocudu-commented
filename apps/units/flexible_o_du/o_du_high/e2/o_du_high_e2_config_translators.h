// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config_translators.h
//
// Purpose (plain English):
//   Declares two translator functions that convert the user-facing E2 config
//   into representations used by the E2 agent and the worker manager.
//
//     generate_e2_config — builds the internal e2ap_configuration struct
//       that the E2 agent library expects. Takes the user config plus the
//       gNB identity fields (gNB ID, PLMN, DU ID) that are not part of the
//       E2 config section but are needed for the E2 Setup Request message.
//
//     fill_o_du_high_e2_worker_manager_config — if the E2AP PCAP is enabled,
//       tells the worker manager to create an E2AP PCAP executor. Without
//       this call, writing PCAP records would happen on the E2 processing
//       thread, risking real-time violations.
// =============================================================================

#pragma once


#include "ocudu/e2/e2ap_configuration.h"


namespace ocudu {


struct o_du_high_e2_config;
struct worker_manager_config;

/// Converts and returns the given gnb application configuration to a E2 configuration.

/// \brief Translates the user E2 config + gNB identity into the internal
///        e2ap_configuration consumed by the E2 agent library.
/// \param config    Parsed E2 config (RIC address, E2SM modules).
/// \param gnb_id    The gNB identifier (from the top-level gnb config).
/// \param plmn      The PLMN string of the first configured cell.
/// \param gnb_du_id The DU identifier within the gNB (for multi-DU setups).
e2ap_configuration generate_e2_config(const o_du_high_e2_config& config,
                                      gnb_id_t                   gnb_id,
                                      const std::string&         plmn,
                                      std::optional<gnb_du_id_t> gnb_du_id);

/// Fills the O-RAN DU high E2 worker manager parameters of the given worker manager configuration.

/// \brief Declares the E2AP PCAP executor need to the worker manager.
///        No-op if E2AP PCAP is disabled in the config.
void fill_o_du_high_e2_worker_manager_config(worker_manager_config& config, const o_du_high_e2_config& unit_cfg);


} // namespace ocudu
