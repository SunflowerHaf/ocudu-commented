// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/mac/mac_dl/rar_pdu_assembler.h  (26 lines)
//
// LIBRARY: lib/mac
// Medium Access Control (MAC, TS 38.321): scheduler interface adaptor, HARQ process management, multiplexing/demultiplexing of logical channels into transport blocks, random-access (RACH) handling, and timing-advance control. Interfaces: MAC SDU to/from RLC, MAC PDU to/from the lower PHY via FAPI.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/mac/cell_configuration.h"
#include "ocudu/support/memory_pool/ring_buffer_pool.h"


namespace ocudu {


struct rar_information;

/// Encodes RAR PDUs based on RAR information provided by the scheduler.

/// Encodes RAR PDUs based on RAR information provided by the scheduler.
class rar_pdu_assembler
{
public:
  explicit rar_pdu_assembler(ticking_ring_buffer_pool& pdu_pool);


  span<const uint8_t> encode_rar_pdu(const rar_information& rar);


private:
  ticking_ring_buffer_pool& pdu_pool;
};


} // namespace ocudu
