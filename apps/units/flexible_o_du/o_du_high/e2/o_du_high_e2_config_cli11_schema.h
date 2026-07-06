// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: e2/o_du_high_e2_config_cli11_schema.h
//
// Purpose (plain English):
//   Declares the two entry points for plugging the DU High E2 configuration
//   into the CLI11 YAML/CLI parser:
//
//     configure_cli11_with_o_du_high_e2_config_schema — registers E2 fields
//       under the [e2] and [pcap] YAML sub-sections. The E2 fields include:
//       enable_du_e2, the near-RT RIC address and port, and the E2SM module
//       toggles (KPM, RC, CCC). The PCAP fields are e2ap_du_filename and
//       e2ap_enable.
//
//     autoderive_o_du_high_e2_parameters_after_parsing — post-parse clean-up:
//       if the E2 agent is disabled, the E2AP PCAP is also forced off (no
//       point capturing messages that won't exist).
// =============================================================================

#pragma once


#include "CLI/CLI11.hpp"


namespace ocudu {


struct o_du_high_e2_config;

/// Configures the given CLI11 application with the O-RAN DU high E2 configuration schema.

/// Registers the DU High E2 config schema (E2 connection + PCAP) with CLI11.
void configure_cli11_with_o_du_high_e2_config_schema(CLI::App& app, o_du_high_e2_config& config);

/// Auto derive O-RAN DU high E2 parameters after the parsing.

/// Post-parse derivation: disable E2AP PCAP if the E2 agent itself is off.
void autoderive_o_du_high_e2_parameters_after_parsing(o_du_high_e2_config& unit_cfg);


} // namespace ocudu
