// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/srs/srs_bandwidth_configuration.h  (31 lines)
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
#include <optional>


namespace ocudu {

/// \brief Contains the Sounding Reference Signals (SRS) bandwidth configuration parameters.
///
/// The parameters are used in TS38.211 Section 6.4.1.4.3 and they are derived from TS38.211 Table 6.4.1.4.3-1.

/// \brief Contains the Sounding Reference Signals (SRS) bandwidth configuration parameters.
///
/// The parameters are used in TS38.211 Section 6.4.1.4.3 and they are derived from TS38.211 Table 6.4.1.4.3-1.
struct srs_configuration {
  /// Sounding Reference Signal bandwidth in physical resource blocks, corresponds to the parameter \f$m_{SRS,b}\f$.
  /// Sounding Reference Signal bandwidth in physical resource blocks, corresponds to the parameter \f$m_{SRS,b}\f$.
  unsigned m_srs;
  /// Number of frequency hopping locations, corresponds to parameter \f$N_{b}\f$.
  /// Number of frequency hopping locations, corresponds to parameter \f$N_{b}\f$.
  unsigned N;
};

/// \brief Gets an SRS configuration.
///
/// \param[in] c_srs Parameter \f$C_{SRS}\f$ contained in the higher-layer parameter \e freqHopping (see TS38.331
/// Section 6.3.2, Information Element \e SRS-Config).
/// \param[in] b_srs Parameter \f$B_{SRS}\f$ contained in the higher-layer parameter \e freqHopping (see TS38.331
/// Section 6.3.2, Information Element \e SRS-Config).
/// \return A valid SRS configuration if the provided arguments are valid, otherwise \c std::nullopt.

/// \brief Gets an SRS configuration.
///
/// \param[in] c_srs Parameter \f$C_{SRS}\f$ contained in the higher-layer parameter \e freqHopping (see TS38.331
/// Section 6.3.2, Information Element \e SRS-Config).
/// \param[in] b_srs Parameter \f$B_{SRS}\f$ contained in the higher-layer parameter \e freqHopping (see TS38.331
/// Section 6.3.2, Information Element \e SRS-Config).
/// \return A valid SRS configuration if the provided arguments are valid, otherwise \c std::nullopt.
std::optional<srs_configuration> srs_configuration_get(uint8_t c_srs, uint8_t b_srs);


} // namespace ocudu
