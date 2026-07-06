// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/e2/e2_messages.h  (69 lines)
//
// INTERFACE HEADER — include/ocudu/e2
// E2AP interface headers: e2_connection_client (SCTP connection to the near-RT RIC), e2ap_configuration, E2SM-KPM/RC/CCC interfaces, and the per-unit metric notifier/connector interfaces (e2_du_metrics_notifier, e2_cu_metrics_notifier, etc.).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/e2ap/e2ap.h"


namespace ocudu {


struct e2_message {
  asn1::e2ap::e2ap_pdu_c pdu;
};

/// \brief CU initiated E2 setup request.

/// \brief CU initiated E2 setup request.
struct e2_setup_request_message {
  asn1::e2ap::e2setup_request_s request;
  unsigned                      max_setup_retries = 5;
};

/// \brief Response to CU initiated E2 setup request.

/// \brief Response to CU initiated E2 setup request.
struct e2_setup_response_message {
  asn1::e2ap::e2setup_resp_s response;
  asn1::e2ap::e2setup_fail_s failure;
  bool                       success;
};


struct e2_subscribe_request_message {
  asn1::e2ap::ric_request_id_s  request_id;
  asn1::e2ap::ric_sub_details_s subscription;
};


struct e2_subscribe_reponse_message {
  asn1::e2ap::ric_request_id_s               request_id;
  uint16_t                                   ran_function_id;
  asn1::e2ap::cause_c                        cause;
  asn1::e2ap::ric_action_admitted_list_l     admitted_list;
  asn1::e2ap::ric_action_not_admitted_list_l not_admitted_list;
  bool                                       success;
};


struct e2_subscribe_delete_request_message {
  asn1::e2ap::ric_request_id_s         request_id;
  asn1::e2ap::ric_sub_delete_request_s subscription;
};


struct e2_subscribe_delete_response_message {
  asn1::e2ap::ric_request_id_s      request_id;
  asn1::e2ap::ric_sub_delete_resp_s response;
  asn1::e2ap::ric_sub_delete_fail_s failure;
  bool                              success;
};


struct e2_indication_message {
  asn1::e2ap::ric_request_id_s request_id;
  asn1::e2ap::ric_ind_s        indication;
};


struct e2_ric_control_request {
  asn1::e2ap::ric_ctrl_request_s request;
};


struct e2_ric_control_response {
  asn1::e2ap::ric_ctrl_ack_s  ack;
  asn1::e2ap::ric_ctrl_fail_s failure;
  bool                        success;
};


} // namespace ocudu
