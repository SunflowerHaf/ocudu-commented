// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/nrppa/nrppa_helper.h  (19 lines)
//
// LIBRARY: lib/nrppa
// NR Positioning Protocol A (NRPPa, TS 38.455): the interface between the gNB and the 5GC Location Management Function (LMF). Used for UE positioning (OTDOA, ECID measurements). Implements ASN.1 encode/decode + procedure state machines.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/nrppa/nrppa.h"


namespace ocudu::ocucp {

// Logging

// Logging
typedef enum { Rx = 0, Tx } direction_t;


void log_nrppa_message(ocudulog::basic_logger&          logger,
                       const direction_t                dir,
                       byte_buffer_view                 pdu,
                       const asn1::nrppa::nr_ppa_pdu_c& nrppa_pdu);


} // namespace ocudu::ocucp
