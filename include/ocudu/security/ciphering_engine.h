// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/security/ciphering_engine.h  (21 lines)
//
// INTERFACE HEADER — include/ocudu/security
// Security interface headers: security_engine (applies/verifies NIA and NEA algorithms to PDUs), key_set (128-bit AS/NAS keys), security_context types, and the ciphering/integrity algorithm selection enum.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/security/security_engine.h"


namespace ocudu {
namespace security {


class ciphering_engine
{
public:
  virtual ~ciphering_engine() = default;


  virtual security_status apply_ciphering(byte_buffer& buf, size_t offset, uint32_t count) = 0;
};


} // namespace security
} // namespace ocudu
