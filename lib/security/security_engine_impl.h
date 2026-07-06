// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/security/security_engine_impl.h  (35 lines)
//
// LIBRARY: lib/security
// 5G NAS and AS security: implements NIA (integrity) and NEA (ciphering) algorithms — NIA1/NEA1 (SNOW 3G), NIA2/NEA2 (AES-128), NIA3/NEA3 (ZUC). Uses MbedTLS for the underlying cipher primitives. Called by PDCP (AS security) and the CU-CP (NAS security).
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/security/ciphering_engine.h"
#include "ocudu/security/integrity_engine.h"
#include "ocudu/security/security.h"
#include "ocudu/security/security_engine.h"


namespace ocudu::security {


class security_engine_impl final : public security_engine_tx, public security_engine_rx
{
public:
  security_engine_impl(sec_128_as_config  sec_cfg,
                       uint8_t            bearer_id,
                       security_direction direction,
                       integrity_enabled  integrity_enabled,
                       ciphering_enabled  ciphering_enabled);
  ~security_engine_impl() override = default;


  security_status encrypt_and_protect_integrity(byte_buffer& buf, size_t offset, uint32_t count) override;
  security_status decrypt_and_verify_integrity(byte_buffer& buf, size_t offset, uint32_t count) override;


private:
  std::unique_ptr<integrity_engine> integ_eng;
  std::unique_ptr<ciphering_engine> cipher_eng;


  ocudulog::basic_logger& logger;
  bool                    allow_unprotected = false;
};


} // namespace ocudu::security
