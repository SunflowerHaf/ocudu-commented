// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/rohc/rohc_lib/rohc_lib_factory.h  (21 lines)
//
// LIBRARY: lib/rohc
// Robust Header Compression (ROHC, RFC 5795/3095): compresses repetitive IP/UDP/RTP headers on DL PDUs before PDCP transmits them over the air. Reduces overhead on low-bitrate or constrained links. Implemented in the CU-UP PDCP path.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/rohc/rohc_factory.h"


namespace ocudu::rohc {


class rohc_lib_factory : public rohc_factory
{
public:
  rohc_lib_factory()  = default;
  ~rohc_lib_factory() = default;


  std::unique_ptr<rohc_compressor>   create_rohc_compressor(const rohc_config& cfg) const override;
  std::unique_ptr<rohc_decompressor> create_rohc_decompressor(const rohc_config& cfg) const override;
};


} // namespace ocudu::rohc
