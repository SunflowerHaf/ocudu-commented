// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rohc/rohc_decompressor.h  (25 lines)
//
// INTERFACE HEADER — include/ocudu/rohc
// ROHC interface headers: rohc_compressor and rohc_decompressor interfaces, the ROHC context configuration type (max_cid, profiles), and the result type for compression/decompression operations.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/byte_buffer.h"


namespace ocudu::rohc {


struct rohc_decromp_result {
  /// The decompressed packet. Empty in case of feedback-only or error.
  /// The decompressed packet. Empty in case of feedback-only or error.
  byte_buffer decomp_packet;
  /// Feedback packet for transmission to the peer. Empty in case of no feedback available.
  /// Feedback packet for transmission to the peer. Empty in case of no feedback available.
  byte_buffer feedback_packet;
};


class rohc_decompressor
{
public:
  virtual ~rohc_decompressor()                               = default;
  virtual rohc_decromp_result decompress(byte_buffer packet) = 0;
};


} // namespace ocudu::rohc
