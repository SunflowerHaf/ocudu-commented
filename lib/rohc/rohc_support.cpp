// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/rohc/rohc_support.cpp  (17 lines)
//
// LIBRARY: lib/rohc
// Robust Header Compression (ROHC, RFC 5795/3095): compresses repetitive IP/UDP/RTP headers on DL PDUs before PDCP transmits them over the air. Reduces overhead on low-bitrate or constrained links. Implemented in the CU-UP PDCP path.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/rohc/rohc_support.h"


using namespace ocudu;
using namespace ocudu::rohc;


bool ocudu::rohc::rohc_supported()
{
#ifdef ENABLE_ROHC_LIB
  return true;
#else
  return false;
#endif
}
