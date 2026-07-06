// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_preamble_information.h  (97 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/phy_time_unit.h"
#include "ocudu/ran/prach/prach_format_type.h"
#include "ocudu/ran/prach/prach_subcarrier_spacing.h"


namespace ocudu {


struct prach_configuration;

/// \brief Collects PRACH preamble information parameters.
///
/// The parameters are used and described in TS38.211 Section 6.3.3.1.

/// \brief Collects PRACH preamble information parameters.
///
/// The parameters are used and described in TS38.211 Section 6.3.3.1.
struct prach_preamble_information {
  /// Sequence length in frequency domain, parameter \f$L_{RA}\f$.
  /// Sequence length in frequency domain, parameter \f$L_{RA}\f$.
  unsigned sequence_length;
  /// Parameter \f$\Delta f^{RA}\f$.
  /// Parameter \f$\Delta f^{RA}\f$.
  prach_subcarrier_spacing scs;
  /// \brief Number of OFDM symbols.
  ///
  /// It is given by the first multiplier that appears in the \f$N_u\f$ column, in TS38.211 Tables 6.3.3.1-1 and
  /// 6.3.3.1-2.
  /// \brief Number of OFDM symbols.
  ///
  /// It is given by the first multiplier that appears in the \f$N_u\f$ column, in TS38.211 Tables 6.3.3.1-1 and
  /// 6.3.3.1-2.
  unsigned nof_symbols;
  /// Parameter \f$N_{CP}^{RA}\f$. Expressed in units of the reference symbol time \f$\kappa\f$.
  /// Parameter \f$N_{CP}^{RA}\f$. Expressed in units of the reference symbol time \f$\kappa\f$.
  phy_time_unit cp_length;
  /// Flag: true if the preamble supports the restricted sets A and B.
  /// Flag: true if the preamble supports the restricted sets A and B.
  bool support_restricted_sets;

  /// Parameter \f$N_u\f$, expressed in units of the reference symbol time \f$\kappa\f$.

  /// Parameter \f$N_u\f$, expressed in units of the reference symbol time \f$\kappa\f$.
  phy_time_unit symbol_length() const
  {
    return phy_time_unit::from_seconds(static_cast<double>(nof_symbols) / static_cast<double>(ra_scs_to_Hz(scs)));
  }
};

/// \brief Get long PRACH preamble information as per TS38.211 Table 6.3.3.1-1.
///
/// An assertion is triggered if the PRACH preamble format is short.
///
/// \param[in] format PRACH preamble format.
/// \return PRACH preamble information.

/// \brief Get long PRACH preamble information as per TS38.211 Table 6.3.3.1-1.
///
/// An assertion is triggered if the PRACH preamble format is short.
///
/// \param[in] format PRACH preamble format.
/// \return PRACH preamble information.
prach_preamble_information get_prach_preamble_long_info(prach_format_type format);

/// \brief Get short PRACH preamble information as per TS38.211 Table 6.3.3.1-2.
///
/// An assertion is triggered if:
/// - the PRACH preamble format is long, or
/// - the random access subcarrier spacing does not satisfy \f$\Delta f ^\textup{RA} = 15 \cdot 2^\mu\f$ where \f$\mu
/// \in \{0, 1, 2, 3\}\f$.
///
/// \param[in] format        PRACH preamble format.
/// \param[in] ra_scs        Random access subcarrier spacing \f$\Delta f ^\textup{RA}\f$.
/// \param[in] last_occasion Set to true if \f$n_\textup{t}^\textup{RA}=N_\textup{t}^\textup{RA,slot}-1\f$
/// \return PRACH preamble information.

/// \brief Get short PRACH preamble information as per TS38.211 Table 6.3.3.1-2.
///
/// An assertion is triggered if:
/// - the PRACH preamble format is long, or
/// - the random access subcarrier spacing does not satisfy \f$\Delta f ^\textup{RA} = 15 \cdot 2^\mu\f$ where \f$\mu
/// \in \{0, 1, 2, 3\}\f$.
///
/// \param[in] format        PRACH preamble format.
/// \param[in] ra_scs        Random access subcarrier spacing \f$\Delta f ^\textup{RA}\f$.
/// \param[in] last_occasion Set to true if \f$n_\textup{t}^\textup{RA}=N_\textup{t}^\textup{RA,slot}-1\f$
/// \return PRACH preamble information.
prach_preamble_information
get_prach_preamble_short_info(prach_format_type format, prach_subcarrier_spacing ra_scs, bool last_occasion);

/// \brief Gets the PRACH window duration.
/// \param[in] format             PRACH preamble format.
/// \param[in] pusch_scs          Uplink resource grid subcarrier spacing. Determines the numerology \f$\mu\f$.
/// \param[in] start_symbol_index OFDM symbol index within the slot that marks the start of the acquisition window for
///                               the first time-domain PRACH occasion.
/// \param[in] nof_td_occasions   Number of time-domain occasions within a PRACH window.
/// \return The PRACH window duration from the beginning of the slot to the end of the last time-domain occasion.
/// \note The RA subcarrier spacing for short preambles is assumed to be equal to the uplink resource grid subcarrier
///       spacing.

/// \brief Gets the PRACH window duration.
/// \param[in] format             PRACH preamble format.
/// \param[in] pusch_scs          Uplink resource grid subcarrier spacing. Determines the numerology \f$\mu\f$.
/// \param[in] start_symbol_index OFDM symbol index within the slot that marks the start of the acquisition window for
///                               the first time-domain PRACH occasion.
/// \param[in] nof_td_occasions   Number of time-domain occasions within a PRACH window.
/// \return The PRACH window duration from the beginning of the slot to the end of the last time-domain occasion.
/// \note The RA subcarrier spacing for short preambles is assumed to be equal to the uplink resource grid subcarrier
///       spacing.
phy_time_unit get_prach_window_duration(prach_format_type  format,
                                        subcarrier_spacing pusch_scs,
                                        unsigned           start_symbol_index,
                                        unsigned           nof_td_occasions);

/// \brief Collects PRACH preamble duration information.

/// \brief Collects PRACH preamble duration information.
struct prach_symbols_slots_duration {
  /// Duration of the PRACH Preamble in slots, with reference to the PUSCH SCS.
  /// Duration of the PRACH Preamble in slots, with reference to the PUSCH SCS.
  unsigned prach_length_slots;
  /// PRACH starting slot within the subframe, with reference to the PUSCH SCS. For 15kHz PUSCH SCS, values: {0}; for
  /// 30kHz PUSCH SCS, values: {0, 1}
  /// PRACH starting slot within the subframe, with reference to the PUSCH SCS. For 15kHz PUSCH SCS, values: {0}; for
  /// 30kHz PUSCH SCS, values: {0, 1}
  unsigned start_slot_pusch_scs;
  /// PRACH duration in symbols, with reference to the PUSCH SCS.
  /// PRACH duration in symbols, with reference to the PUSCH SCS.
  unsigned nof_symbols;
  /// PRACH starting symbol within the slot, with reference to the PUSCH SCS.
  /// PRACH starting symbol within the slot, with reference to the PUSCH SCS.
  unsigned start_symbol_pusch_scs;
};

/// \brief Compute PRACH preamble duration information.
///
/// \param[in] prach_cfg PRACH preamble configuration.
/// \param[in] pusch_scs PUSCH SCS that is used as a reference for symbol and slot unit.
/// \return PRACH preamble duration information.

/// \brief Compute PRACH preamble duration information.
///
/// \param[in] prach_cfg PRACH preamble configuration.
/// \param[in] pusch_scs PUSCH SCS that is used as a reference for symbol and slot unit.
/// \return PRACH preamble duration information.
prach_symbols_slots_duration get_prach_duration_info(const prach_configuration& prach_cfg,
                                                     subcarrier_spacing         pusch_scs);


} // namespace ocudu
