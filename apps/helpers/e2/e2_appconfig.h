// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: helpers/e2/e2_appconfig.h
//
// Purpose (plain English):
//   Defines the shared e2_config struct used by every unit that has an E2
//   agent (DU, CU-CP, CU-UP). The E2 interface connects the gNB to a
//   near-RT RAN Intelligent Controller (RIC) over SCTP. The RIC can:
//     * Read performance metrics from the gNB (via E2SM-KPM).
//     * Push RRM control decisions down (via E2SM-RC).
//     * Change cell configuration (via E2SM-CCC).
//
//   Fields:
//     enable_unit_e2  — master on/off for this unit's E2 agent.
//     ip_addrs        — IP address(es) of the near-RT RIC.
//     port            — RIC SCTP port (IANA default: 36421).
//     bind_addrs      — local address(es) to bind the SCTP socket.
//     sctp            — fine-grained SCTP socket tuning (RTO, heartbeat, etc.).
//     e2sm_kpm_enabled — advertise E2SM-KPM in the E2 Setup Request.
//     e2sm_rc_enabled  — advertise E2SM-RC.
//     e2sm_ccc_enabled — advertise E2SM-CCC.
// =============================================================================

#pragma once


#include "apps/helpers/network/sctp_appconfig.h"
#include <cstdint>
#include <string>
#include <vector>


namespace ocudu {

/// E2 Agent configuration.

/// Shared E2 interface configuration, reused by DU, CU-CP, and CU-UP units.
struct e2_config {
  /// Whether to enable E2 agent.
  /// Master toggle: set true to start the E2 agent for this unit.
  bool enable_unit_e2 = false;
  /// RIC IP addresses.
  /// IP address(es) of the near-RT RIC to connect to.
  std::vector<std::string> ip_addrs = {"127.0.0.1"};
  /// RIC port.
  /// SCTP port on the near-RT RIC (IANA standardised at 36421).
  uint16_t port = 36421;
  /// Local IP addresses to bind for RIC connection.
  /// Local IP address(es) to bind the SCTP association from.
  std::vector<std::string> bind_addrs = {"127.0.0.1"};
  /// Configuration for SCTP socket parameters.
  /// Fine-grained SCTP socket parameters (RTO timers, heartbeat, max retransmissions).
  sctp_appconfig sctp;
  /// Whether to enable KPM service module.
  /// If true, include E2SM-KPM in the E2 Setup Request — enables per-UE KPI reporting.
  bool e2sm_kpm_enabled = false;
  /// Whether to enable RC service module.
  /// If true, include E2SM-RC — allows the RIC to push RRM control actions.
  bool e2sm_rc_enabled = false;
  /// Whether to enable CCC service module.
  /// If true, include E2SM-CCC — allows the RIC to change cell configuration.
  bool e2sm_ccc_enabled = false;
};


} // namespace ocudu
