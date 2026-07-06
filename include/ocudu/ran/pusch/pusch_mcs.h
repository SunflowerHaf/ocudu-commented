// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/pusch_mcs.h  (53 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/sch/sch_mcs.h"


namespace ocudu {

/// \brief Modulation and Code Scheme table identifiers for PUSCH.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e mcs-Table in various Information Elements).
/// For the actual tables and the selection procedure, see TS38.214 Section 6.1.4.1.

/// \brief Modulation and Code Scheme table identifiers for PUSCH.
///
/// The identifiers are inspired by TS38.331 Section as 6.3.2 (see field \e mcs-Table in various Information Elements).
/// For the actual tables and the selection procedure, see TS38.214 Section 6.1.4.1.
enum class pusch_mcs_table {
  /// Identifies MCS index table 1, TS38.214 Table 5.1.3.1-1.
  /// Identifies MCS index table 1, TS38.214 Table 5.1.3.1-1.
  qam64 = 0,
  /// Identifies MCS index table 2, TS38.214 Table 5.1.3.1-2.
  /// Identifies MCS index table 2, TS38.214 Table 5.1.3.1-2.
  qam256 = 1,
  /// Identifies MCS index table 3, TS38.214 Table 5.1.3.1-3.
  /// Identifies MCS index table 3, TS38.214 Table 5.1.3.1-3.
  qam64LowSe = 2,
};

/// Convert PUSCH MCS table to string.

/// Convert PUSCH MCS table to string.
constexpr const char* pusch_mcs_table_to_string(pusch_mcs_table table)
{
  switch (table) {
    case pusch_mcs_table::qam64:
      return "qam64";
    case pusch_mcs_table::qam256:
      return "qam256";
    case pusch_mcs_table::qam64LowSe:
      return "qam64LowSe";
    default:
      break;
  }
  return "invalid";
}

/// \brief Gets the Modulation and Coding Scheme configuration for PUSCH.
///
/// Reserved target code rates and spectral efficiencies are indicated with zero.
///
/// \param[in] table                  MCS table.
/// \param[in] index                  MCS index.
/// \param[in] use_transform_precoder Set to true if transform precoding is enabled.
/// \param[in] tp_pi2bpsk_present     Set to true if higher layer parameter \e tp-pi2BPSK is enabled. See TS38.331
///                                   Section 6.3.2 Information Element \e PUSCH-Config for more information.
/// \return Modulation and Coding Scheme parameters.

/// \brief Gets the Modulation and Coding Scheme configuration for PUSCH.
///
/// Reserved target code rates and spectral efficiencies are indicated with zero.
///
/// \param[in] table                  MCS table.
/// \param[in] index                  MCS index.
/// \param[in] use_transform_precoder Set to true if transform precoding is enabled.
/// \param[in] tp_pi2bpsk_present     Set to true if higher layer parameter \e tp-pi2BPSK is enabled. See TS38.331
///                                   Section 6.3.2 Information Element \e PUSCH-Config for more information.
/// \return Modulation and Coding Scheme parameters.
sch_mcs_description
pusch_mcs_get_config(pusch_mcs_table table, sch_mcs_index index, bool use_transform_precoder, bool tp_pi2bpsk_present);


} // namespace ocudu
