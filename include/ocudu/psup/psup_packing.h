// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/psup/psup_packing.h  (29 lines)
//
// INTERFACE HEADER — include/ocudu/psup
// PSUP interface header: the PDU session user-plane header packing/unpacking interface for GTP-U extension headers on the N3 interface (carrying QFI and PDU session metadata).
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/adt/span.h"
#include "ocudu/ocudulog/logger.h"
#include "ocudu/psup/psup_message.h"


namespace ocudu {

/// Packing and unpacking of PDU Session Container
///
/// Ref: TS 38.415

/// Packing and unpacking of PDU Session Container
///
/// Ref: TS 38.415
class psup_packing
{
public:
  psup_packing(ocudulog::basic_logger& logger_) : logger(logger_) {}


  bool unpack(psup_dl_pdu_session_information& dl_pdu_session_information, byte_buffer_view container) const;
  bool pack(byte_buffer& out_buf, const psup_dl_pdu_session_information& dl_pdu_session_information) const;


private:
  ocudulog::basic_logger& logger;
};


} // namespace ocudu
