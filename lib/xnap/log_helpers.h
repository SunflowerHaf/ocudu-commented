// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/xnap/log_helpers.h  (14 lines)
//
// LIBRARY: lib/xnap
// Xn Application Protocol (XnAP, TS 38.423): the interface between peer gNBs for handover preparation, data forwarding setup, and interference coordination. Implements ASN.1 encode/decode + handover and Xn setup procedures.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/xnap/xnap.h"


namespace ocudu::ocucp {

/// \brief Log Received/Transmitted NGAP PDU.

/// \brief Log Received/Transmitted NGAP PDU.
void log_xnap_pdu(ocudulog::basic_logger& logger, bool json_log, bool is_rx, const asn1::xnap::xn_ap_pdu_c& pdu);


} // namespace ocudu::ocucp
