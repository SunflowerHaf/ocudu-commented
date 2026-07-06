// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/pdcch_type0_css_coreset_config.h  (53 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {


enum class nr_band;

/// Refer to "SS/PBCH block and CORESET multiplexing pattern", TS 38.213, Section 13.

/// Refer to "SS/PBCH block and CORESET multiplexing pattern", TS 38.213, Section 13.
enum class ssb_coreset0_mplex_pattern { mplx_pattern1 = 0, mplx_pattern2, mplx_pattern3, mplex_invalid };

/// Describes the CORESET for Type0-PDCCH CSS.

/// Describes the CORESET for Type0-PDCCH CSS.
struct pdcch_type0_css_coreset_description {
  /// SS/PBCH block and CORESET multiplexing pattern.
  /// SS/PBCH block and CORESET multiplexing pattern.
  ssb_coreset0_mplex_pattern pattern;
  /// CORESET bandwidth in RBs. Parameter \f$N_{RB}^{CORESET}\f$ as per TS38.213 Section 13.
  /// CORESET bandwidth in RBs. Parameter \f$N_{RB}^{CORESET}\f$ as per TS38.213 Section 13.
  uint8_t nof_rb_coreset;
  /// CORESET duration in symbols. Parameter \f$N_{symb}^{CORESET}\f$ as per TS38.213 Section 13.
  /// CORESET duration in symbols. Parameter \f$N_{symb}^{CORESET}\f$ as per TS38.213 Section 13.
  uint8_t nof_symb_coreset;
  /// \brief Offset defined respect SCS of the CORESET for Type0-PDCCH CSS set, provided by \c subCarrierSpacingCommon,
  /// from the smallest RB index of the CORESET for Type0-PDCCH CSS set to the smallest RB index of the common RB
  /// overlapping with the first RB of the corresponding SS/PBCH block.
  /// \brief Offset defined respect SCS of the CORESET for Type0-PDCCH CSS set, provided by \c subCarrierSpacingCommon,
  /// from the smallest RB index of the CORESET for Type0-PDCCH CSS set to the smallest RB index of the common RB
  /// overlapping with the first RB of the corresponding SS/PBCH block.
  int8_t offset;
};

/// Reserved CORESET for Type0-PDCCH CSS.

/// Reserved CORESET for Type0-PDCCH CSS.
constexpr pdcch_type0_css_coreset_description PDCCH_TYPE0_CSS_CORESET_RESERVED =
    {ssb_coreset0_mplex_pattern::mplex_invalid, 0, 0, 0};

/// \brief Get the CORESET configuration for Type0-PDCCH CSS.
///
/// The CORESET configuration is retrieved as per TS38.213 Tables 13-1, 13-2, 13-3, 13-4, 13-5, 13-6, 13-7, 13-8, 13-9
/// and 13-10 depending on the subcarrier combination of the SS/PBCH block and PDCCH, and the minimum channel bandwidth.
///
/// \param[in] band                    Band minimum bandwidth in MHz as per TS38.104 Table 5.3.5-1 for FR 1
///                                    and Table 5.3.5-2 for FR2. This is ignored in case the band is restricted to
///                                    operation with shared spectrum channel access.
/// \param[in] ssb_scs                 SS/PBCH block subcarrier spacing.
/// \param[in] pdcch_scs               PDCCH subcarrier spacing.
/// \param[in] coreset_zero_index      Parameter \c controlResourceSetZero as per TS38.331 PDCCH-ConfigSIB1.
/// \param[in] subcarrier_offset       Offset between the CRB and the beginning of the SS/PBCH block.
/// \return A valid CORESET description if \c config is valid. Otherwise, \c PDCCH_TYPE0_CSS_CORESET_RESERVED.

/// \brief Get the CORESET configuration for Type0-PDCCH CSS.
///
/// The CORESET configuration is retrieved as per TS38.213 Tables 13-1, 13-2, 13-3, 13-4, 13-5, 13-6, 13-7, 13-8, 13-9
/// and 13-10 depending on the subcarrier combination of the SS/PBCH block and PDCCH, and the minimum channel bandwidth.
///
/// \param[in] band                    Band minimum bandwidth in MHz as per TS38.104 Table 5.3.5-1 for FR 1
///                                    and Table 5.3.5-2 for FR2. This is ignored in case the band is restricted to
///                                    operation with shared spectrum channel access.
/// \param[in] ssb_scs                 SS/PBCH block subcarrier spacing.
/// \param[in] pdcch_scs               PDCCH subcarrier spacing.
/// \param[in] coreset_zero_index      Parameter \c controlResourceSetZero as per TS38.331 PDCCH-ConfigSIB1.
/// \param[in] subcarrier_offset       Offset between the CRB and the beginning of the SS/PBCH block.
/// \return A valid CORESET description if \c config is valid. Otherwise, \c PDCCH_TYPE0_CSS_CORESET_RESERVED.
pdcch_type0_css_coreset_description pdcch_type0_css_coreset_get(nr_band            band,
                                                                subcarrier_spacing ssb_scs,
                                                                subcarrier_spacing pdcch_scs,
                                                                uint8_t            coreset_zero_index,
                                                                uint8_t            subcarrier_offset);


} // namespace ocudu
