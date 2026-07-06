// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ngap/ngap_configuration_helpers.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/ngap
// NGAP interface headers: n2_connection_client (manages the SCTP connection to the AMF), ngap_message_handler interfaces for all NGAP procedures, and the NGAP-to-RRC message passing interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ngap/ngap_configuration.h"
#include "ocudu/ran/s_nssai.h"


namespace ocudu {
namespace config_helpers {


std::map<uint8_t, ocucp::cu_cp_qos_config> make_default_ngap_qos_config_list();

/// Returns true if the given CU-CP configuration is valid, otherwise false.

/// Returns true if the given CU-CP configuration is valid, otherwise false.
inline bool is_valid_configuration(const ocucp::ngap_configuration& config)
{
  if (config.ran_node_name.empty()) {
    fmt::print("RAN node name is empty\n");
    return false;
  }
  return true;
}


} // namespace config_helpers
} // namespace ocudu
