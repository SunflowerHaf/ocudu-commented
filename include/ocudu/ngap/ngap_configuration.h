// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ngap/ngap_configuration.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/ngap
// NGAP interface headers: n2_connection_client (manages the SCTP connection to the AMF), ngap_message_handler interfaces for all NGAP procedures, and the NGAP-to-RRC message passing interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/ran/gnb_id.h"
#include "ocudu/ran/supported_tracking_area.h"
#include <chrono>
#include <string>
#include <vector>


namespace ocudu::ocucp {

/// \brief NGAP configuration

/// \brief NGAP configuration
struct ngap_configuration {
  gnb_id_t                             gnb_id{0, 22};
  std::string                          ran_node_name;
  cu_cp_amf_index_t                    amf_index;
  std::vector<supported_tracking_area> supported_tas;
  std::chrono::milliseconds            procedure_timeout{5000};
  std::chrono::seconds                 request_pdu_session_timeout; // timeout for requesting a pdu session in seconds
};


} // namespace ocudu::ocucp
