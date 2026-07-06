// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/security/zuc.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/security
// Security interface headers: security_engine (applies/verifies NIA and NEA algorithms to PDUs), key_set (128-bit AS/NAS keys), security_context types, and the ciphering/integrity algorithm selection enum.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {
namespace security {


typedef unsigned char u8;
typedef unsigned      u32;

/* the state registers of LFSR */

/* the state registers of LFSR */
typedef struct {
  u32 LFSR_S0;
  u32 LFSR_S1;
  u32 LFSR_S2;
  u32 LFSR_S3;
  u32 LFSR_S4;
  u32 LFSR_S5;
  u32 LFSR_S6;
  u32 LFSR_S7;
  u32 LFSR_S8;
  u32 LFSR_S9;
  u32 LFSR_S10;
  u32 LFSR_S11;
  u32 LFSR_S12;
  u32 LFSR_S13;
  u32 LFSR_S14;
  u32 LFSR_S15;
  /* the registers of F */
  /* the registers of F */
  u32 F_R1;
  u32 F_R2;
  /* the outputs of BitReorganization */
  /* the outputs of BitReorganization */
  u32 BRC_X0;
  u32 BRC_X1;
  u32 BRC_X2;
  u32 BRC_X3;
} zuc_state_t;


void zuc_initialize(zuc_state_t* state, const u8* k, u8* iv);
void zuc_generate_keystream(zuc_state_t* state, int key_stream_len, u32* p_keystream);


} // namespace security
} // namespace ocudu
