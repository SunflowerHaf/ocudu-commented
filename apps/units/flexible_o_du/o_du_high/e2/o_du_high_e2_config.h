// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config.h
//
// Purpose (plain English):
//   Configuration structs for the O-RAN E2 interface on the DU High side.
//
//   The E2 interface connects the gNB to a RAN Intelligent Controller (RIC).
//   The RIC can observe per-UE KPIs (via E2SM-KPM) and push RRM control
//   actions (via E2SM-RC, E2SM-CCC). This file defines what the user can
//   configure for that interface at the DU High level.
//
//   Two structs:
//     o_du_high_e2_pcap_config — controls whether E2AP (the E2 Application
//       Protocol) messages are captured to a PCAP file. Useful for debugging
//       the RIC↔DU interaction in Wireshark. The default filename is
//       /tmp/du_e2ap.pcap.
//
//     o_du_high_e2_config — the full E2 config for the DU High: wraps the
//       shared base e2_config (IP address of the near-RT RIC, port, E2SM
//       module enables) plus the PCAP toggle above.
// =============================================================================

#pragma once


#include "apps/helpers/e2/e2_appconfig.h"


namespace ocudu {

/// O-RAN DU high E2 PCAP configuration.

/// PCAP capture settings for E2AP messages on the DU side.
struct o_du_high_e2_pcap_config {
  /// Output file path for the E2AP packet capture.
  std::string filename = "/tmp/du_e2ap.pcap";
  /// Set true to start capturing E2AP messages to the file above.
  bool        enabled  = false;
};

/// O-RAN DU high configuration.

/// Full E2 configuration for the O-DU High unit.
struct o_du_high_e2_config {
  /// E2 configuration.
  /// Base E2 config: enable toggle, near-RT RIC address, E2SM module flags
  /// (e2sm_kpm_enabled, e2sm_rc_enabled, e2sm_ccc_enabled).
  e2_config base_cfg;
  /// PCAPs.
  /// E2AP packet-capture settings.
  o_du_high_e2_pcap_config pcaps;
};


} // namespace ocudu
