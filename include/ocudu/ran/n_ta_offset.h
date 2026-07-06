// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/n_ta_offset.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

/// \brief Time advance offset - parameter \f$N_{TA,offset}\f$ in TS38.211 Section 4.3.3.
///
/// This value must be selected from the parameter \e n-TimingAdvanceOffset (TS38.331 Section 6.3.2, Information Element
/// \e ServingCellConfigCommon) if it is present. Otherwise, it is given by TS38.133 Section 7.1.2 depending on the
/// duplex mode of the cell and the frequency range.
///
/// The values are given in units of \f$T_c\f$ (see TS38.211 Section 4.1).

/// \brief Time advance offset - parameter \f$N_{TA,offset}\f$ in TS38.211 Section 4.3.3.
///
/// This value must be selected from the parameter \e n-TimingAdvanceOffset (TS38.331 Section 6.3.2, Information Element
/// \e ServingCellConfigCommon) if it is present. Otherwise, it is given by TS38.133 Section 7.1.2 depending on the
/// duplex mode of the cell and the frequency range.
///
/// The values are given in units of \f$T_c\f$ (see TS38.211 Section 4.1).
enum class n_ta_offset {
  /// For FR1 FDD band with LTE-NR coexistence case.
  /// For FR1 FDD band with LTE-NR coexistence case.
  n0 = 0,
  /// For FR1 FDD band without LTE-NR coexistence case or for FR1 TDD band without LTE-NR coexistence case.
  /// For FR1 FDD band without LTE-NR coexistence case or for FR1 TDD band without LTE-NR coexistence case.
  n25600 = 25600,
  /// For FR2.
  /// For FR2.
  n13792 = 13792,
  /// For FR1 TDD band with LTE-NR coexistence case.
  /// For FR1 TDD band with LTE-NR coexistence case.
  n39936 = 39936
};


} // namespace ocudu
