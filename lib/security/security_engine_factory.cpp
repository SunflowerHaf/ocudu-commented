// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/security/security_engine_factory.cpp  (20 lines)
//
// LIBRARY: lib/security
// 5G NAS and AS security: implements NIA (integrity) and NEA (ciphering) algorithms — NIA1/NEA1 (SNOW 3G), NIA2/NEA2 (AES-128), NIA3/NEA3 (ZUC). Uses MbedTLS for the underlying cipher primitives. Called by PDCP (AS security) and the CU-CP (NAS security).
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/security/security_engine_factory.h"
#include "security_engine_impl.h"


std::unique_ptr<ocudu::security::security_engine_tx>
ocudu::create_security_engine_tx(const security_engine_creation_message& msg)
{
  return std::make_unique<security::security_engine_impl>(
      msg.sec_cfg, msg.bearer_id, msg.direction, msg.integrity_enabled, msg.ciphering_enabled);
}


std::unique_ptr<ocudu::security::security_engine_rx>
ocudu::create_security_engine_rx(const security_engine_creation_message& msg)
{
  return std::make_unique<security::security_engine_impl>(
      msg.sec_cfg, msg.bearer_id, msg.direction, msg.integrity_enabled, msg.ciphering_enabled);
}
