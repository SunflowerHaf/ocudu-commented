// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/harq_id.h  (33 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"


namespace ocudu {

/// Identification of an HARQ process.

/// Identification of an HARQ process.
enum harq_id_t : uint8_t {
  MAX_HARQ_ID           = 31,
  MAX_NOF_HARQS         = 32, ///< Maximum number of HARQ processes (NTN).
  MAX_NOF_HARQS_NON_NTN = 16, ///< Maximum number of HARQ processes for non-NTN cells.
  INVALID_HARQ_ID       = 32
};


constexpr harq_id_t to_harq_id(unsigned h_id)
{
  return static_cast<harq_id_t>(h_id);
}

/// Bitset mask for DL HARQ Feedback Disabled configuration.

/// Bitset mask for DL HARQ Feedback Disabled configuration.
using harq_dl_feedback_disabled_mask = bounded_bitset<MAX_NOF_HARQS, true>;

/// Bitset mask for UL HARQ mode configuration.

/// Bitset mask for UL HARQ mode configuration.
using harq_ul_mode_mask = bounded_bitset<MAX_NOF_HARQS, true>;

/// Outcomes of a HARQ-ACK report.

/// Outcomes of a HARQ-ACK report.
enum class mac_harq_ack_report_status : int8_t { nack = 0, ack, dtx };


} // namespace ocudu
