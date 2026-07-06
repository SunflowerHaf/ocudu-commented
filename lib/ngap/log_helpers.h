// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ngap/log_helpers.h  (19 lines)
//
// LIBRARY: lib/ngap
// NG Application Protocol (NGAP, TS 38.413): the N2 control-plane between the gNB and the 5G Core AMF. Handles UE registration, PDU session setup, handover, paging, NAS message transport, and NG Setup. Implements full ASN.1 encode/decode + all NGAP elementary procedures.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/ngap/ngap.h"
#include "ocudu/ran/cu_cp_types.h"


namespace ocudu::ocucp {

/// \brief Log Received/Transmitted NGAP PDU.

/// \brief Log Received/Transmitted NGAP PDU.
void log_ngap_pdu(ocudulog::basic_logger&                logger,
                  bool                                   json_log,
                  bool                                   is_rx,
                  const std::optional<cu_cp_ue_index_t>& ue_idx,
                  const asn1::ngap::ngap_pdu_c&          pdu);


} // namespace ocudu::ocucp
