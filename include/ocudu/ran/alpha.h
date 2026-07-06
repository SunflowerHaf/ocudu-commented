// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/alpha.h  (67 lines)
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

/// The IE Alpha defines possible values of a the pathloss compensation coefficient for uplink power control. Value
/// alpha0 corresponds to the value 0, Value alpha04 corresponds to the value 0.4, and so on. Value alpha1 corresponds
/// to value 1.
/// \remark See TS 38.331, Alpha. Also, see clause 7.1 of TS 38.213.

/// The IE Alpha defines possible values of a the pathloss compensation coefficient for uplink power control. Value
/// alpha0 corresponds to the value 0, Value alpha04 corresponds to the value 0.4, and so on. Value alpha1 corresponds
/// to value 1.
/// \remark See TS 38.331, Alpha. Also, see clause 7.1 of TS 38.213.
enum class alpha : unsigned { alpha0, alpha04, alpha05, alpha06, alpha07, alpha08, alpha09, alpha1, not_set };

/// \brief Converts an alpha value to a float.

/// \brief Converts an alpha value to a float.
inline float alpha_to_float(alpha a)
{
  switch (a) {
    case alpha::alpha0:
      return 0.0f;
    case alpha::alpha04:
      return 0.4f;
    case alpha::alpha05:
      return 0.5f;
    case alpha::alpha06:
      return 0.6f;
    case alpha::alpha07:
      return 0.7f;
    case alpha::alpha08:
      return 0.8f;
    case alpha::alpha09:
      return 0.9f;
    case alpha::alpha1:
      return 1.0f;
    case alpha::not_set:
    default:
      return 0.0f;
  }
  return 0.0f;
}

/// \brief Converts an alpha value to a float.

/// \brief Converts an alpha value to a float.
inline alpha float_to_alpha(float alpha_float)
{
  switch (static_cast<int>(alpha_float * 10)) {
    case 0:
      return alpha::alpha0;
    case 4:
      return alpha::alpha04;
    case 5:
      return alpha::alpha05;
    case 6:
      return alpha::alpha06;
    case 7:
      return alpha::alpha07;
    case 8:
      return alpha::alpha08;
    case 9:
      return alpha::alpha09;
    case 10:
      return alpha::alpha1;
    default:
      return alpha::not_set;
  }
}


} // namespace ocudu
