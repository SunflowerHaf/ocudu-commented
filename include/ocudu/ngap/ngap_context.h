// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ngap/ngap_context.h  (44 lines)
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
#include "ocudu/ran/guami.h"
#include "ocudu/ran/plmn_identity.h"
#include "ocudu/ran/supported_tracking_area.h"
#include <chrono>
#include <string>
#include <vector>


namespace ocudu::ocucp {

/// \brief NGAP context

/// \brief NGAP context
struct ngap_context_t {
  gnb_id_t                             gnb_id = {0, 22};
  std::string                          ran_node_name;
  std::string                          amf_name;
  cu_cp_amf_index_t                    amf_index;
  std::vector<supported_tracking_area> supported_tas;
  std::vector<guami_t>                 served_guami_list;
  uint16_t                             default_paging_drx = 256; // default paging drx
  std::chrono::milliseconds procedure_timeout; // Time that the NGAP waits for a response from the AMF in milliseconds
  std::chrono::seconds      request_pdu_session_timeout; // timeout for requesting a PDU session in seconds
  byte_buffer               lmf_routing_id;


  std::vector<plmn_identity> get_supported_plmns() const
  {
    std::vector<plmn_identity> supported_plmns;
    for (const auto& ta : supported_tas) {
      for (const auto& plmn : ta.plmn_list) {
        supported_plmns.push_back(plmn.plmn_id);
      }
    }


    return supported_plmns;
  }
};


} // namespace ocudu::ocucp
