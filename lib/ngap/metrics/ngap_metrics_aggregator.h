// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ngap/metrics/ngap_metrics_aggregator.h  (34 lines)
//
// LIBRARY: lib/ngap
// NG Application Protocol (NGAP, TS 38.413): the N2 control-plane between the gNB and the 5G Core AMF. Handles UE registration, PDU session setup, handover, paging, NAS message transport, and NG Setup. Implements full ASN.1 encode/decode + all NGAP elementary procedures.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ngap/ngap_metrics.h"
#include "ocudu/ran/s_nssai.h"
#include <cmath>


namespace ocudu::ocucp {


class ngap_metrics_aggregator
{
public:
  void aggregate_requested_pdu_session(s_nssai_t s_nssai);


  void aggregate_successful_pdu_session_setup(s_nssai_t s_nssai);


  void aggregate_failed_pdu_session_setup(s_nssai_t s_nssai, ngap_cause_t cause);


  void aggregate_cn_initiated_paging_request();


  void aggregate_ue_associated_logical_ng_connection_establishment_attempt();


  void aggregate_ue_associated_logical_ng_connection_establishment_success();


  ngap_metrics request_metrics_report() const;


private:
  ngap_metrics aggregated_ngap_metrics;
};


} // namespace ocudu::ocucp
