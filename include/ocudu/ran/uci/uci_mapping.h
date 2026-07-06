// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/uci/uci_mapping.h  (60 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/support/ocudu_assert.h"


namespace ocudu {

/// HARQ values for UCI PUCCH Format 0 or Format 1.

/// HARQ values for UCI PUCCH Format 0 or Format 1.
enum class uci_pucch_f0_or_f1_harq_values { nack, ack, dtx };


constexpr const char* to_string(uci_pucch_f0_or_f1_harq_values value)
{
  switch (value) {
    case uci_pucch_f0_or_f1_harq_values::nack:
      return "nack";
    case uci_pucch_f0_or_f1_harq_values::ack:
      return "ack";
    case uci_pucch_f0_or_f1_harq_values::dtx:
      return "dtx";
    default:
      ocudu_assert(0, "invalid UCI PUCCH Format 0/1 HARQ value={}", static_cast<unsigned>(value));
      break;
  }
  return "";
}

/// \brief Maps the integer \c beta_offset value for HARQ-ACK reporting into the corresponding float value.
///
/// The integer \c beta_offset value is passed by the \c PUSCH-Config, TS 38.331, and the mapping into the corresponding
/// float value is determined as per Table 9.3-1, TS 38.213.
/// \param beta_uint_val is the integer value as per \c BetaOffsets, TS 38.331.
/// \return The corresponding float value as per Table 9.3-1, TS 38.213.

/// \brief Maps the integer \c beta_offset value for HARQ-ACK reporting into the corresponding float value.
///
/// The integer \c beta_offset value is passed by the \c PUSCH-Config, TS 38.331, and the mapping into the corresponding
/// float value is determined as per Table 9.3-1, TS 38.213.
/// \param beta_uint_val is the integer value as per \c BetaOffsets, TS 38.331.
/// \return The corresponding float value as per Table 9.3-1, TS 38.213.
float beta_harq_ack_to_float(unsigned beta_uint_val);

/// \brief Maps the integer \c beta_offset value for CSI reporting into the corresponding float value.
///
/// The integer \c beta_offset value is passed by the \c PUSCH-Config, TS 38.331, and the mapping into the corresponding
/// float value is determined as per Table 9.3-2, TS 38.213.
/// \param beta_uint_val is the integer value as per \c BetaOffsets, TS 38.331.
/// \return The corresponding float value as per Table 9.3-2, TS 38.213.

/// \brief Maps the integer \c beta_offset value for CSI reporting into the corresponding float value.
///
/// The integer \c beta_offset value is passed by the \c PUSCH-Config, TS 38.331, and the mapping into the corresponding
/// float value is determined as per Table 9.3-2, TS 38.213.
/// \param beta_uint_val is the integer value as per \c BetaOffsets, TS 38.331.
/// \return The corresponding float value as per Table 9.3-2, TS 38.213.
float beta_csi_to_float(unsigned beta_uint_val);

/// Indicates CRC result on UCI containing HARQ/CSI Part 1/CSI Part 2 data.

/// Indicates CRC result on UCI containing HARQ/CSI Part 1/CSI Part 2 data.
enum class uci_pusch_or_pucch_f2_3_4_detection_status {
  /// Used when CRC was attached.
  /// Used when CRC was attached.
  crc_pass = 1,
  /// Used when UE is expected to attach CRC.
  /// Used when UE is expected to attach CRC.
  crc_failure,
  /// Undetected UCI.
  /// Undetected UCI.
  dtx,
  /// Indicates UCI detection.
  /// Indicates UCI detection.
  no_dtx,
  /// Indicates that PHY did not check for UCI DTX.
  /// Indicates that PHY did not check for UCI DTX.
  dtx_not_checked
};


} // namespace ocudu
