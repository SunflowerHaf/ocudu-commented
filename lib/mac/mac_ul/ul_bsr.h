// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/mac/mac_ul/ul_bsr.h  (48 lines)
//
// LIBRARY: lib/mac
// Medium Access Control (MAC, TS 38.321): scheduler interface adaptor, HARQ process management, multiplexing/demultiplexing of logical channels into transport blocks, random-access (RACH) handling, and timing-advance control. Interfaces: MAC SDU to/from RLC, MAC PDU to/from the lower PHY via FAPI.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"
#include "ocudu/adt/expected.h"
#include "ocudu/adt/span.h"
#include "ocudu/adt/static_vector.h"
#include "ocudu/adt/to_array.h"
#include "ocudu/mac/bsr_config.h"


namespace ocudu {

/// UL BSR Report for a single Logical Channel Group

/// UL BSR Report for a single Logical Channel Group
struct lcg_bsr_report {
  lcg_id_t lcg_id;
  uint8_t  buffer_size;
};

/// List of reported UL BSRs

/// List of reported UL BSRs
using lcg_bsr_report_list = static_vector<lcg_bsr_report, MAX_NOF_LCGS>;

/// Decode Short BSR

/// Decode Short BSR
inline lcg_bsr_report decode_sbsr(byte_buffer_view payload)
{
  ocudu_sanity_check(not payload.empty(), "Trying to decode SBSR but payload is empty.");
  lcg_bsr_report sbsr = {};
  sbsr.lcg_id         = uint_to_lcg_id((payload[0] & 0xe0U) >> 5U);
  sbsr.buffer_size    = payload[0] & 0x1fU;
  return sbsr;
}


struct long_bsr_report {
  lcg_bsr_report_list list; /// one entry for each reported LCG
};

/// Decode Long BSR

/// Decode Long BSR
expected<long_bsr_report> decode_lbsr(bsr_format format, byte_buffer_view payload);

/// Converts the buffer size field of a BSR (5 or 8-bit Buffer Size field) into Nof Bytes.
/// \param buff_size_index The buffer size field contained in the MAC PDU.
/// \param format The BSR format that determines the buffer size field length.
/// \return The actual buffer size level in Bytes.

/// Converts the buffer size field of a BSR (5 or 8-bit Buffer Size field) into Nof Bytes.
/// \param buff_size_index The buffer size field contained in the MAC PDU.
/// \param format The BSR format that determines the buffer size field length.
/// \return The actual buffer size level in Bytes.
uint32_t buff_size_field_to_bytes(size_t buff_size_index, bsr_format format);


} // namespace ocudu
