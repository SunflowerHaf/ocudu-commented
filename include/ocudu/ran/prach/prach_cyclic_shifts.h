// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_cyclic_shifts.h  (35 lines)
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
#include "ocudu/ran/prach/restricted_set_config.h"
#include <cstdint>


namespace ocudu {

/// Reserved number of cyclic shifts. It indicates the number of cyclic shifts is invalid.

/// Reserved number of cyclic shifts. It indicates the number of cyclic shifts is invalid.
constexpr uint16_t PRACH_CYCLIC_SHIFTS_RESERVED = 430;

/// \brief Calculates the number of cyclic shifts \f$N_{CS}\f$ used in the sequence generation as per TS38.211
/// Section 6.3.3.1.
///
/// The number of cyclic shifts \f$N_{CS}\f$ is extracted from:
/// - TS38.211 Table 6.3.3.1-5 for preambles 0, 1 and 2
/// - TS38.211 Table 6.3.3.1-6 for preamble 3, and
/// - TS38.211 Table 6.3.3.1-7 for the remaining preambles.
///
/// \param[in] prach_scs             \brief PRACH subcarrier spacing (parameter \f$\Delta f^{RA}\f$ as defined in
///                                  TS38.211 Section 6.3.3.1).
/// \param[in] restricted_set        \brief Restricted set (see \e restrictedSetConfig in TS38.331 Section 6.3.2,
///                                  Information Element \e RACH-ConfigCommon).
/// \param[in] zero_correlation_zone \brief Zero correlation zone (see \e zeroCorrelationZoneConfig in TS38.331
///                                  Section 6.3.2, Information Element \e RACH-ConfigGeneric).
/// \return The number of cyclic shifts if the input parameters are valid. Otherwise, PRACH_CYCLIC_SHIFTS_RESERVED.

/// \brief Calculates the number of cyclic shifts \f$N_{CS}\f$ used in the sequence generation as per TS38.211
/// Section 6.3.3.1.
///
/// The number of cyclic shifts \f$N_{CS}\f$ is extracted from:
/// - TS38.211 Table 6.3.3.1-5 for preambles 0, 1 and 2
/// - TS38.211 Table 6.3.3.1-6 for preamble 3, and
/// - TS38.211 Table 6.3.3.1-7 for the remaining preambles.
///
/// \param[in] prach_scs             \brief PRACH subcarrier spacing (parameter \f$\Delta f^{RA}\f$ as defined in
///                                  TS38.211 Section 6.3.3.1).
/// \param[in] restricted_set        \brief Restricted set (see \e restrictedSetConfig in TS38.331 Section 6.3.2,
///                                  Information Element \e RACH-ConfigCommon).
/// \param[in] zero_correlation_zone \brief Zero correlation zone (see \e zeroCorrelationZoneConfig in TS38.331
///                                  Section 6.3.2, Information Element \e RACH-ConfigGeneric).
/// \return The number of cyclic shifts if the input parameters are valid. Otherwise, PRACH_CYCLIC_SHIFTS_RESERVED.
uint16_t prach_cyclic_shifts_get(prach_subcarrier_spacing prach_scs,
                                 restricted_set_config    restricted_set,
                                 unsigned                 zero_correlation_zone);


} // namespace ocudu
