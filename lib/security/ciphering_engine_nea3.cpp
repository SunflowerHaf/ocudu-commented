// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/security/ciphering_engine_nea3.cpp  (29 lines)
//
// LIBRARY: lib/security
// 5G NAS and AS security: implements NIA (integrity) and NEA (ciphering) algorithms — NIA1/NEA1 (SNOW 3G), NIA2/NEA2 (AES-128), NIA3/NEA3 (ZUC). Uses MbedTLS for the underlying cipher primitives. Called by PDCP (AS security) and the CU-CP (NAS security).
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ciphering_engine_nea3.h"
#include "ocudu/security/ciphering.h"


using namespace ocudu;
using namespace security;


ciphering_engine_nea3::ciphering_engine_nea3(sec_128_key        k_128_enc_,
                                             uint8_t            bearer_id_,
                                             security_direction direction_) :
  k_128_enc(k_128_enc_), bearer_id(bearer_id_), direction(direction_), logger(ocudulog::fetch_basic_logger("SEC"))
{
}


security_status ciphering_engine_nea3::apply_ciphering(byte_buffer& buf, size_t offset, uint32_t count)
{
  byte_buffer_view msg{buf.begin() + offset, buf.end()};


  logger.debug("Applying ciphering. count={}", count);
  logger.debug("K_enc: {}", k_128_enc);
  logger.debug(msg.begin(), msg.end(), "Ciphering input:");
  security_nea3(k_128_enc, count, bearer_id, direction, msg);
  logger.debug(msg.begin(), msg.end(), "Ciphering output:");


  return security_status::success;
}
