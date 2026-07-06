// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/positioning/positioning_ids.h  (56 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>


namespace ocudu {

// LMF measurement ID.

// LMF measurement ID.
enum class lmf_meas_id_t : uint32_t { min = 1, max = 65536 };

/// Convert lmf_meas_id type to integer.

/// Convert lmf_meas_id type to integer.
inline uint32_t lmf_meas_id_to_uint(lmf_meas_id_t id)
{
  return static_cast<uint32_t>(id);
}

/// Convert integer to lmf_meas_id type.

/// Convert integer to lmf_meas_id type.
inline lmf_meas_id_t uint_to_lmf_meas_id(uint32_t id)
{
  return static_cast<lmf_meas_id_t>(id);
}

// RAN measurement ID.

// RAN measurement ID.
enum class ran_meas_id_t : uint32_t { min = 1, max = 65536 };

/// Convert ran_meas_id type to integer.

/// Convert ran_meas_id type to integer.
inline uint32_t ran_meas_id_to_uint(ran_meas_id_t id)
{
  return static_cast<uint32_t>(id);
}

/// Convert integer to ran_meas_id type.

/// Convert integer to ran_meas_id type.
inline ran_meas_id_t uint_to_ran_meas_id(uint32_t id)
{
  return static_cast<ran_meas_id_t>(id);
}

// Transmission-Reception Point (TRP) ID.

// Transmission-Reception Point (TRP) ID.
enum class trp_id_t : uint32_t { min = 1, max = 65535 };

/// Convert trp_id type to integer.

/// Convert trp_id type to integer.
inline uint32_t trp_id_to_uint(trp_id_t id)
{
  return static_cast<uint32_t>(id);
}

/// Convert integer to trp_id type.

/// Convert integer to trp_id type.
inline trp_id_t uint_to_trp_id(uint32_t id)
{
  return static_cast<trp_id_t>(id);
}


} // namespace ocudu
