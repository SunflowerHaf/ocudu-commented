// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/sch/sch_dmrs_power.h  (26 lines)
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
#include <array>


namespace ocudu {

/// \brief Calculates the ratio between the Physical Shared Channel EPRE and the DM-RS EPRE.
///
/// The calculation is common for PDSCH and PUSCH, as defined in TS38.214 Table 4.1-1 and Table 6.2.2-1.
///
/// \param[in] nof_cdm_groups_without_data Number of CDM groups without data.
/// \return Parameter \f$\beta_{\textup{DMRS}}\f$ in decibels.

/// \brief Calculates the ratio between the Physical Shared Channel EPRE and the DM-RS EPRE.
///
/// The calculation is common for PDSCH and PUSCH, as defined in TS38.214 Table 4.1-1 and Table 6.2.2-1.
///
/// \param[in] nof_cdm_groups_without_data Number of CDM groups without data.
/// \return Parameter \f$\beta_{\textup{DMRS}}\f$ in decibels.
inline float get_sch_to_dmrs_ratio_dB(unsigned nof_cdm_groups_without_data)
{
  ocudu_assert(nof_cdm_groups_without_data > 0 && nof_cdm_groups_without_data < 4,
               "Invalid number of DMRS CDM groups without data.");
  static constexpr std::array<float, 4> beta_dmrs_values = {NAN, 0, -3, -4.77};
  return beta_dmrs_values[nof_cdm_groups_without_data];
}


} // namespace ocudu
