// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/pdcch_candidates.h  (104 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/pdcch/aggregation_level.h"
#include "ocudu/ran/pdcch/coreset.h"
#include "ocudu/ran/rnti.h"
#include "ocudu/ran/subcarrier_spacing.h"


namespace ocudu {

/// Maximum number of candidates per aggregation level in a SS as per TS38.331 SearchSpace.

/// Maximum number of candidates per aggregation level in a SS as per TS38.331 SearchSpace.
constexpr unsigned PDCCH_MAX_NOF_CANDIDATES_SS = 8;

/// PDCCH candidate and PDCCH candidate list data types.

/// PDCCH candidate and PDCCH candidate list data types.
using pdcch_candidate_type = uint8_t;
using pdcch_candidate_list = static_vector<pdcch_candidate_type, PDCCH_MAX_NOF_CANDIDATES_SS>;

/// \brief Gets the maximum number of monitored PDCCH candidates per slot for a given subcarrier spacing, for a single
/// serving cell, as per TS 38.213, Table 10.1-2.

/// \brief Gets the maximum number of monitored PDCCH candidates per slot for a given subcarrier spacing, for a single
/// serving cell, as per TS 38.213, Table 10.1-2.
inline unsigned max_nof_monitored_pdcch_candidates(subcarrier_spacing scs)
{
  static constexpr std::array<uint8_t, 4> max_monitored_pdcch_candidates_per_slot = {44, 36, 22, 20};
  return max_monitored_pdcch_candidates_per_slot[to_numerology_value(scs)];
}

/// \brief Parameters for calculating the PDCCH lowest Control Channel Element (CCE).
///
/// The parameters in this struct allow computing the PDCCH lowest CCE, for all candidates and for a Common SS,
/// following the specifics in TS38.213 Section 10.1.
///
/// Consider an active DL BWP of a serving cell with carrier indicator field \f$n_{CI}\f$. In the search space set
/// \f$s\f$, associated with CORESET \f$p\f$ in slot \f$n_{s,f}^\mu\f$, the lowest CCE index \f$n_{CCE}\f$ corresponding
/// to the PDCCH candidate \f$m_{s,n_{CI}}\f$ is given by
/// \[
/// n_{CCE} = L\cdot \left \{ \left ( Y_{p,n_{s,f}^\mu} + \left \lfloor \frac{m_{s,n_{CI}}\cdot N_{CCE,p}}{L\cdot
/// M_{s,max}} \right \rfloor +n_{CI} \right ) mod \left \lfloor N_{CCE,p}/L \right \rfloor \right \}
/// \]
/// where:
/// - \f$Y_{p,n_{s,f}^\mu}=0\f$,
/// - \f$n_{CI}=0\f$,
/// - \f$m_{s,n_{CI}}\in \{0,...,M_{s,n_{CI}}^{(L)}\}\f$,

/// \brief Parameters for calculating the PDCCH lowest Control Channel Element (CCE).
///
/// The parameters in this struct allow computing the PDCCH lowest CCE, for all candidates and for a Common SS,
/// following the specifics in TS38.213 Section 10.1.
///
/// Consider an active DL BWP of a serving cell with carrier indicator field \f$n_{CI}\f$. In the search space set
/// \f$s\f$, associated with CORESET \f$p\f$ in slot \f$n_{s,f}^\mu\f$, the lowest CCE index \f$n_{CCE}\f$ corresponding
/// to the PDCCH candidate \f$m_{s,n_{CI}}\f$ is given by
/// \[
/// n_{CCE} = L\cdot \left \{ \left ( Y_{p,n_{s,f}^\mu} + \left \lfloor \frac{m_{s,n_{CI}}\cdot N_{CCE,p}}{L\cdot
/// M_{s,max}} \right \rfloor +n_{CI} \right ) mod \left \lfloor N_{CCE,p}/L \right \rfloor \right \}
/// \]
/// where:
/// - \f$Y_{p,n_{s,f}^\mu}=0\f$,
/// - \f$n_{CI}=0\f$,
/// - \f$m_{s,n_{CI}}\in \{0,...,M_{s,n_{CI}}^{(L)}\}\f$,
struct pdcch_candidates_common_ss_configuration {
  /// Aggregation level \f$L\epsilon\{1,2,4,8,16\}\f$.
  /// Aggregation level \f$L\epsilon\{1,2,4,8,16\}\f$.
  aggregation_level al;
  /// \brief Number of PDCCH candidates \f$M_{s,max}^{(L)}\f$ the UE is configured to monitor for aggregation level
  /// \f$L\f$ of a search space set \f$s\f$ for a serving cell corresponding to \f$n_{CI}\f$.
  /// \brief Number of PDCCH candidates \f$M_{s,max}^{(L)}\f$ the UE is configured to monitor for aggregation level
  /// \f$L\f$ of a search space set \f$s\f$ for a serving cell corresponding to \f$n_{CI}\f$.
  unsigned nof_candidates;
  /// Number of CCEs contained in CORESET \f$p\f$, \f$N_{CCE,p}\f$.
  /// Number of CCEs contained in CORESET \f$p\f$, \f$N_{CCE,p}\f$.
  unsigned nof_cce_coreset;
};

/// \brief Parameters for calculating the PDCCH lowest Control Channel Element (CCE).
///
/// The parameters in this struct allow computing the PDCCH lowest CCE, for all candidates and for a UE-Specific SS,
/// following the specifics in TS38.213 Section 10.1.
///
/// Consider an active DL BWP of a serving cell with carrier indicator field \f$n_{CI}\f$. In the search space set
/// \f$s\f$, associated with CORESET \f$p\f$ in slot \f$n_{s,f}^\mu\f$, the lowest CCE index \f$n_{CCE}\f$ corresponding
/// to the PDCCH candidate \f$m_{s,n_{CI}}\f$ is given by
/// \[
/// n_{CCE} = L\cdot \left \{ \left ( Y_{p,n_{s,f}^\mu} + \left \lfloor \frac{m_{s,n_{CI}}\cdot N_{CCE,p}}{L\cdot
/// M_{s,max}} \right \rfloor +n_{CI} \right ) mod \left \lfloor N_{CCE,p}/L \right \rfloor \right \}
/// \]
/// where:
/// - \f$Y_{p,n_{s,f}^\mu}\f$ is calculated as a function of parameters \f$p\f$, \f$n_\textup{RNTI}\f$ and
///   \f$n_{s,f}^\mu\f$;
/// - \f$n_{CI}=0\f$,
/// - \f$m_{s,n_{CI}}\in \{0,...,M_{s,n_{CI}}^{(L)}\}\f$.

/// \brief Parameters for calculating the PDCCH lowest Control Channel Element (CCE).
///
/// The parameters in this struct allow computing the PDCCH lowest CCE, for all candidates and for a UE-Specific SS,
/// following the specifics in TS38.213 Section 10.1.
///
/// Consider an active DL BWP of a serving cell with carrier indicator field \f$n_{CI}\f$. In the search space set
/// \f$s\f$, associated with CORESET \f$p\f$ in slot \f$n_{s,f}^\mu\f$, the lowest CCE index \f$n_{CCE}\f$ corresponding
/// to the PDCCH candidate \f$m_{s,n_{CI}}\f$ is given by
/// \[
/// n_{CCE} = L\cdot \left \{ \left ( Y_{p,n_{s,f}^\mu} + \left \lfloor \frac{m_{s,n_{CI}}\cdot N_{CCE,p}}{L\cdot
/// M_{s,max}} \right \rfloor +n_{CI} \right ) mod \left \lfloor N_{CCE,p}/L \right \rfloor \right \}
/// \]
/// where:
/// - \f$Y_{p,n_{s,f}^\mu}\f$ is calculated as a function of parameters \f$p\f$, \f$n_\textup{RNTI}\f$ and
///   \f$n_{s,f}^\mu\f$;
/// - \f$n_{CI}=0\f$,
/// - \f$m_{s,n_{CI}}\in \{0,...,M_{s,n_{CI}}^{(L)}\}\f$.
struct pdcch_candidates_ue_ss_configuration {
  /// Aggregation level \f$L\epsilon\{1,2,4,8,16\}\f$.
  /// Aggregation level \f$L\epsilon\{1,2,4,8,16\}\f$.
  aggregation_level al;
  /// \brief Number of PDCCH candidates \f$M_{s,max}^{(L)}\f$ the UE is configured to monitor for aggregation level
  /// \f$L\f$ of a search space set \f$s\f$ for a serving cell corresponding to \f$n_{CI}\f$.
  /// \brief Number of PDCCH candidates \f$M_{s,max}^{(L)}\f$ the UE is configured to monitor for aggregation level
  /// \f$L\f$ of a search space set \f$s\f$ for a serving cell corresponding to \f$n_{CI}\f$.
  unsigned nof_candidates;
  /// Number of CCEs contained in CORESET \f$p\f$, \f$N_{CCE,p}\f$.
  /// Number of CCEs contained in CORESET \f$p\f$, \f$N_{CCE,p}\f$.
  unsigned nof_cce_coreset;
  /// CORESET identifier. Parameter \f$p\f$.
  /// CORESET identifier. Parameter \f$p\f$.
  coreset_id cs_id;
  /// Parameter \f$n_\textup{RNTI}\f$.
  /// Parameter \f$n_\textup{RNTI}\f$.
  rnti_t rnti;
  /// Slot index within the radio frame. Parameter \f$n_{s,f}^\mu\f$.
  /// Slot index within the radio frame. Parameter \f$n_{s,f}^\mu\f$.
  unsigned slot_index;
};

/// \brief Generates a PDCCH candidate list for Common SS as per TS38.213 Section 10.1.
///
/// An assertion is triggered if the number of CCEs for the aggregation level exceeds the number of CCE in the CORESET.
///
/// The resultant list contains the lowest CCE index of the \c config.nof_candidates.

/// \brief Generates a PDCCH candidate list for Common SS as per TS38.213 Section 10.1.
///
/// An assertion is triggered if the number of CCEs for the aggregation level exceeds the number of CCE in the CORESET.
///
/// The resultant list contains the lowest CCE index of the \c config.nof_candidates.
pdcch_candidate_list pdcch_candidates_common_ss_get_lowest_cce(const pdcch_candidates_common_ss_configuration& config);

/// \brief Generates a PDCCH candidate list for UE-Specific SS as per TS38.213 Section 10.1.
///
/// An assertion is triggered if the number of candidates times the aggregation level exceeds the number of CCE in the
/// CORESET.
///
/// The resultant list contains the lowest CCE index of the \c config.nof_candidates.

/// \brief Generates a PDCCH candidate list for UE-Specific SS as per TS38.213 Section 10.1.
///
/// An assertion is triggered if the number of candidates times the aggregation level exceeds the number of CCE in the
/// CORESET.
///
/// The resultant list contains the lowest CCE index of the \c config.nof_candidates.
pdcch_candidate_list pdcch_candidates_ue_ss_get_lowest_cce(const pdcch_candidates_ue_ss_configuration& config);


} // namespace ocudu
