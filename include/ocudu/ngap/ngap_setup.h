// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ngap/ngap_setup.h  (60 lines)
//
// INTERFACE HEADER — include/ocudu/ngap
// NGAP interface headers: n2_connection_client (manages the SCTP connection to the AMF), ngap_message_handler interfaces for all NGAP procedures, and the NGAP-to-RRC message passing interface.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/ran/cause/ngap_cause.h"
#include "ocudu/ran/crit_diagnostics.h"
#include "ocudu/ran/cu_types.h"
#include "ocudu/ran/guami.h"
#include "ocudu/ran/tac.h"
#include <variant>


namespace ocudu::ocucp {

// enum class ngap_handov_type { intra5gs = 0, fivegs_to_eps, eps_to_5gs, fivegs_to_utran };


// enum class ngap_handov_type { intra5gs = 0, fivegs_to_eps, eps_to_5gs, fivegs_to_utran };

struct ngap_broadcast_plmn_item {
  plmn_identity                     plmn_id = plmn_identity::test_value();
  std::vector<slice_support_item_t> tai_slice_support_list;
};


struct ngap_supported_ta_item {
  tac_t                                 tac;
  std::vector<ngap_broadcast_plmn_item> broadcast_plmn_list;
};


struct ngap_served_guami_item {
  guami_t                    guami;
  std::optional<std::string> backup_amf_name;
};


struct ngap_plmn_support_item {
  std::string                       plmn_id;
  std::vector<slice_support_item_t> slice_support_list;
};


struct ngap_ng_setup_response {
  std::string                         amf_name;
  std::vector<ngap_served_guami_item> served_guami_list;
  uint16_t                            relative_amf_capacity;
  std::vector<ngap_plmn_support_item> plmn_support_list;
  std::optional<crit_diagnostics_t>   crit_diagnostics;
  // TODO: Add optional ue_retention_info;
  // TODO: Add optional iab_supported;
  // TODO: Add optional extended_amf_name;
  /// Packed NGAP PDUs captured during the setup exchange.
  // TODO: Add optional ue_retention_info;
  // TODO: Add optional iab_supported;
  // TODO: Add optional extended_amf_name;
  /// Packed NGAP PDUs captured during the setup exchange.
  byte_buffer packed_ng_setup_request;
  byte_buffer packed_ng_setup_response;
};


struct ngap_ng_setup_failure {
  ngap_cause_t                      cause;
  std::optional<crit_diagnostics_t> crit_diagnostics;
};


using ngap_ng_setup_result = std::variant<ngap_ng_setup_response, ngap_ng_setup_failure>;


} // namespace ocudu::ocucp
