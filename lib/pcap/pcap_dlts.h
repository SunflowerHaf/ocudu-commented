// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/pcap/pcap_dlts.h  (13 lines)
//
// LIBRARY: lib/pcap
// Creates and writes PCAP capture files for every protocol interface: NGAP, F1AP, E1AP, XNAP, E2AP, MAC, RLC, GTP-U (F1-U, N3). Each function returns a unique_ptr to a dlt_pcap or specialised pcap writer. Null PCAP objects (silently discard) are returned when the interface is disabled.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

#pragma once


#include <cstdint>


namespace ocudu {

// DLT for EXPORT PDU pcaps.

// DLT for EXPORT PDU pcaps.
constexpr uint16_t PCAP_EXPORT_PDU_DLT = 252;


} // namespace ocudu
