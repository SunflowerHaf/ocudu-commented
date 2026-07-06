// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// =============================================================================
// FILE: ntn/du_high_ntn_config_translators.h
//
// Purpose (plain English):
//   Declares two NTN-specific translator functions that adjust the DU SRB and
//   QoS configs when a cell is NTN-enabled:
//
//     ntn_augment_du_srb_config — increases SRB RLC timers (T-PollRetransmit,
//       T-Reassembly, T-StatusProhibit) to account for the round-trip delay.
//       Without this, RLC would time out and retransmit before the ACK arrives.
//
//     ntn_augment_du_qos_config — adjusts DRB QoS parameters similarly
//       (PDCP discard timers, reordering windows, etc.).
// =============================================================================

#pragma once
#include "ocudu/ran/qos/five_qi.h"
#include "ocudu/ran/rb_id.h"
#include <map>


namespace ocudu {


namespace odu {
struct du_qos_config;
struct du_srb_config;
} // namespace odu


struct du_high_unit_cell_ntn_config;

/// Applies NTN-specific overrides to DU SRB configuration based on \c ntn_cfg.

/// Applies NTN-specific RLC timer overrides to all SRB configurations.
void ntn_augment_du_srb_config(const du_high_unit_cell_ntn_config&     ntn_cfg,
                               std::map<srb_id_t, odu::du_srb_config>& srb_cfgs);

/// Applies NTN-specific overrides to DU QoS configuration based on \c ntn_cfg.

/// Applies NTN-specific QoS/timer overrides to all DRB configurations.
void ntn_augment_du_qos_config(const du_high_unit_cell_ntn_config&      ntn_cfg,
                               std::map<five_qi_t, odu::du_qos_config>& qos_cfgs);


} // namespace ocudu
