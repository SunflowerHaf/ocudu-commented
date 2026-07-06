// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/precoding/precoding_matrix_indicator.h  (45 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/precoding/precoding_codebook_properties.h"
#include <optional>
#include <variant>

/// \file
/// \brief Precoding Matrix Indicator (PMI) definitions.
///
/// This file contains the different PMI types. The different types of PMI are described in TS38.214 Section 5.2.2.2.
/// The purpose of these structures are unifying the PMI in CSI reports and the generation of precoding matrices from
/// the CSI reports.


/// \file
/// \brief Precoding Matrix Indicator (PMI) definitions.
///
/// This file contains the different PMI types. The different types of PMI are described in TS38.214 Section 5.2.2.2.
/// The purpose of these structures are unifying the PMI in CSI reports and the generation of precoding matrices from
/// the CSI reports.

namespace ocudu {

/// Precoding Matrix Indicator (PMI) for two antenna ports.

/// Precoding Matrix Indicator (PMI) for two antenna ports.
struct pmi_two_antenna_port {
  /// PMI codebook index from TS38.214 Table 5.2.2.2.1-1
  /// PMI codebook index from TS38.214 Table 5.2.2.2.1-1
  unsigned pmi;
};

/// \brief Precoding Matrix Indicator (PMI) field for Type I Single-Panel codebook.
///
/// This PMI codebook mode is described in TS38.214 Section 5.2.2.2.1.

/// \brief Precoding Matrix Indicator (PMI) field for Type I Single-Panel codebook.
///
/// This PMI codebook mode is described in TS38.214 Section 5.2.2.2.1.
struct pmi_typeI_single_panel {
  /// Single-panel topology configuration.
  /// Single-panel topology configuration.
  pmi_codebook_single_panel_config panel_config;
  /// PMI parameter \f$i_{1,1}\f$.
  /// PMI parameter \f$i_{1,1}\f$.
  unsigned i_1_1;
  /// PMI parameter \f$i_{1,2}\f$. Only available for \f$N_2 > 1\f$ or \f$\upsilon > 2\f$.
  /// PMI parameter \f$i_{1,2}\f$. Only available for \f$N_2 > 1\f$ or \f$\upsilon > 2\f$.
  std::optional<unsigned> i_1_2;
  /// PMI parameter \f$i_{1,3}\f$. Only available for \f$\upsilon \in \{2,3,4\}\f$.
  /// PMI parameter \f$i_{1,3}\f$. Only available for \f$\upsilon \in \{2,3,4\}\f$.
  std::optional<unsigned> i_1_3;
  /// PMI parameter \f$i_2\f$.
  /// PMI parameter \f$i_2\f$.
  unsigned i_2;
};

/// Unified Precoding Matrix Indicator (PMI) type.

/// Unified Precoding Matrix Indicator (PMI) type.
using precoding_matrix_indicator = std::variant<std::monostate, pmi_two_antenna_port, pmi_typeI_single_panel>;


} // namespace ocudu
