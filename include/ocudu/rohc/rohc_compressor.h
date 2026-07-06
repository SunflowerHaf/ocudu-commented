// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/rohc/rohc_compressor.h  (19 lines)
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


class rohc_compressor
{
public:
  virtual ~rohc_compressor()                                = default;
  virtual byte_buffer compress(byte_buffer packet)          = 0;
  virtual bool        handle_feedback(byte_buffer feedback) = 0;
};


} // namespace ocudu::rohc
