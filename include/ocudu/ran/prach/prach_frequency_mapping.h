// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_frequency_mapping.h  (32 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/prach/prach_subcarrier_spacing.h"
#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {

/// Collects PRACH frequency mapping information as per TS38.211 Section 5.3.2 and Section 6.3.3.2.

/// Collects PRACH frequency mapping information as per TS38.211 Section 5.3.2 and Section 6.3.3.2.
struct prach_frequency_mapping_information {
  /// Number of resource blocks per PRACH occasion in the frequency domain, relative to the PUSCH subcarrier spacing
  /// (\f$\Delta f\f$).
  /// Number of resource blocks per PRACH occasion in the frequency domain, relative to the PUSCH subcarrier spacing
  /// (\f$\Delta f\f$).
  unsigned nof_rb_ra;
  /// Parameter \f$\bar{k}\f$.
  /// Parameter \f$\bar{k}\f$.
  unsigned k_bar;
};

/// Reserved PRACH frequency-domain mapping information.

/// Reserved PRACH frequency-domain mapping information.
constexpr prach_frequency_mapping_information PRACH_FREQUENCY_MAPPING_INFORMATION_RESERVED = {0, 0};

/// \brief Gets the PRACH frequency mapping information contained in TS38.211 Table 6.3.3.2-1.
/// \param[in] prach_scs_Hz PRACH subcarrier spacing (parameter \f$\Delta f_{RA}\f$).
/// \param[in] pusch_scs_Hz PUSCH subcarrier spacing (parameter \f$\Delta f\f$).
/// \return The requested PRACH frequency mapping information if the combination of input parameters is valid, \c
/// PRACH_FREQUENCY_MAPPING_INFORMATION_RESERVED otherwise.

/// \brief Gets the PRACH frequency mapping information contained in TS38.211 Table 6.3.3.2-1.
/// \param[in] prach_scs_Hz PRACH subcarrier spacing (parameter \f$\Delta f_{RA}\f$).
/// \param[in] pusch_scs_Hz PUSCH subcarrier spacing (parameter \f$\Delta f\f$).
/// \return The requested PRACH frequency mapping information if the combination of input parameters is valid, \c
/// PRACH_FREQUENCY_MAPPING_INFORMATION_RESERVED otherwise.
prach_frequency_mapping_information prach_frequency_mapping_get(prach_subcarrier_spacing prach_scs,
                                                                subcarrier_spacing       pusch_scs);


} // namespace ocudu
