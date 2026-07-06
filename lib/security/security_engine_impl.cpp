// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/security/security_engine_impl.cpp  (111 lines)
//
// LIBRARY: lib/security
// 5G NAS and AS security: implements NIA (integrity) and NEA (ciphering) algorithms — NIA1/NEA1 (SNOW 3G), NIA2/NEA2 (AES-128), NIA3/NEA3 (ZUC). Uses MbedTLS for the underlying cipher primitives. Called by PDCP (AS security) and the CU-CP (NAS security).
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "security_engine_impl.h"
#include "ciphering_engine_nea1.h"
#include "ciphering_engine_nea2.h"
#include "ciphering_engine_nea3.h"
#include "integrity_engine_generic.h"
#include "integrity_engine_nia2_cmac.h"
#include "integrity_engine_nia2_non_cmac.h"


using namespace ocudu;
using namespace security;


security_engine_impl::security_engine_impl(security::sec_128_as_config sec_cfg,
                                           uint8_t                     bearer_id,
                                           security_direction          direction,
                                           security::integrity_enabled integrity_enabled,
                                           security::ciphering_enabled ciphering_enabled) :
  logger(ocudulog::fetch_basic_logger("SEC")),
  allow_unprotected(integrity_enabled == security::integrity_enabled::smc_transition)
{
  if (integrity_enabled != security::integrity_enabled::off) {
    ocudu_assert(sec_cfg.integ_algo.has_value(), "Cannot enable integrity protection: No algorithm selected");
    ocudu_assert(sec_cfg.k_128_int.has_value(), "Cannot enable integrity protection: No key");
    switch (sec_cfg.integ_algo.value()) {
      case integrity_algorithm::nia2:
#ifdef MBEDTLS_CMAC_C
        integ_eng = std::make_unique<integrity_engine_nia2_cmac>(sec_cfg.k_128_int.value(), bearer_id, direction);
#else
        integ_eng = std::make_unique<integrity_engine_nia2_non_cmac>(sec_cfg.k_128_int.value(), bearer_id, direction);
#endif
        break;
      default:
        integ_eng = std::make_unique<integrity_engine_generic>(
            sec_cfg.k_128_int.value(), bearer_id, direction, sec_cfg.integ_algo.value());
        break;
    }
  }
  if (ciphering_enabled == security::ciphering_enabled::on) {
    switch (sec_cfg.cipher_algo) {
      case ciphering_algorithm::nea1:
        cipher_eng = std::make_unique<ciphering_engine_nea1>(sec_cfg.k_128_enc, bearer_id, direction);
        break;
      case ciphering_algorithm::nea2:
        cipher_eng = std::make_unique<ciphering_engine_nea2>(sec_cfg.k_128_enc, bearer_id, direction);
        break;
      case ciphering_algorithm::nea3:
        cipher_eng = std::make_unique<ciphering_engine_nea3>(sec_cfg.k_128_enc, bearer_id, direction);
        break;
      default:
        // no cipher_eng for NEA0
        // no cipher_eng for NEA0
        break;
    }
  }
}


security_status security_engine_impl::encrypt_and_protect_integrity(byte_buffer& buf, size_t offset, uint32_t count)
{
  security_status integ_status = security_status::success_unprotected;

  // apply integrity protection if activated

  // apply integrity protection if activated
  if (integ_eng != nullptr) {
    integ_status = integ_eng->protect_integrity(buf, count);
    if (not is_success(integ_status)) {
      return integ_status;
    }
  }

  // apply ciphering if activated

  // apply ciphering if activated
  if (cipher_eng != nullptr) {
    security_status cipher_status = cipher_eng->apply_ciphering(buf, offset, count);
    if (not is_success(cipher_status)) {
      return cipher_status;
    }
  }

  // return the integrity success type (protected/unprotected)

  // return the integrity success type (protected/unprotected)
  return integ_status;
}


security_status security_engine_impl::decrypt_and_verify_integrity(byte_buffer& buf, size_t offset, uint32_t count)
{
  // apply deciphering if activated
  // apply deciphering if activated
  if (cipher_eng != nullptr) {
    security_status cipher_status = cipher_eng->apply_ciphering(buf, offset, count);
    if (not is_success(cipher_status)) {
      return cipher_status;
    }
  }


  security_status integ_status = security_status::success_unprotected;

  // verify integrity if activated

  // verify integrity if activated
  if (integ_eng != nullptr) {
    integ_status = integ_eng->verify_integrity(buf, count);
    // Unprotected PDUs are expected to fail the integrity check.
    // Unprotected PDUs are expected to fail the integrity check.
    if (allow_unprotected && integ_status == security_status::integrity_failure) {
      // Unprotected PDUs must have zero MAC-I.
      // Unprotected PDUs must have zero MAC-I.
      byte_buffer_view                   mac{buf, buf.length() - sec_mac_len, sec_mac_len};
      static constexpr security::sec_mac zero_mac = {};
      if (std::equal(zero_mac.begin(), zero_mac.end(), mac.begin(), mac.end())) {
        integ_status = security_status::success_unprotected;
        buf.trim_tail(sec_mac_len);
      }
    }
  }


  return integ_status;
}
