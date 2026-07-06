// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/precoding/precoding_codebook_helpers.h  (49 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/precoding/precoding_codebook_configuration.h"

/// \file
/// \brief Precoding Matrix Indicator (PMI) extended information structures and helper functions.
///
/// This file contains structures that extend the information from the PMI codebooks.


/// \file
/// \brief Precoding Matrix Indicator (PMI) extended information structures and helper functions.
///
/// This file contains structures that extend the information from the PMI codebooks.

namespace ocudu {

/// Single-panel codebook configuration of \f$(N_1, N_2)\f$ and \f$(O_1, O_2)\f$

/// Single-panel codebook configuration of \f$(N_1, N_2)\f$ and \f$(O_1, O_2)\f$
struct pmi_codebook_single_panel_info {
  /// Parameter \f$N_1\f$.
  /// Parameter \f$N_1\f$.
  unsigned n1;
  /// Parameter \f$N_2\f$.
  /// Parameter \f$N_2\f$.
  unsigned n2;
  /// Parameter \f$O_1\f$.
  /// Parameter \f$O_1\f$.
  unsigned o1;
  /// Parameter \f$O_2\f$.
  /// Parameter \f$O_2\f$.
  unsigned o2;
};

/// Returns the single-panel codebook configuration of \f$(N_1, N_2)\f$ and \f$(O_1, O_2)\f$.

/// Returns the single-panel codebook configuration of \f$(N_1, N_2)\f$ and \f$(O_1, O_2)\f$.
const pmi_codebook_single_panel_info& get_single_panel_info(pmi_codebook_single_panel_config n1_n2);

/// \brief Precoding Matrix Indicator (PMI) parameter bit-widths for Type I single-panel codebooks.
///
/// Unused or fix values for the given configuration are set to zero.

/// \brief Precoding Matrix Indicator (PMI) parameter bit-widths for Type I single-panel codebooks.
///
/// Unused or fix values for the given configuration are set to zero.
struct pmi_typeI_single_panel_param_sizes {
  /// Parameter \f$i_{1,1}\f$ bit-width.
  /// Parameter \f$i_{1,1}\f$ bit-width.
  unsigned i_1_1;
  /// Parameter \f$i_{1,2}\f$ bit-width.
  /// Parameter \f$i_{1,2}\f$ bit-width.
  unsigned i_1_2;
  /// Parameter \f$i_{1,3}\f$ bit-width.
  /// Parameter \f$i_{1,3}\f$ bit-width.
  unsigned i_1_3;
  /// Parameter \f$i_2\f$ bit-width.
  /// Parameter \f$i_2\f$ bit-width.
  unsigned i_2;
};

/// Gets PMI parameter sizes for \e TypeI-SinglePanel Mode 1 codebook configuration as per TS38.212 Table 6.3.1.1.2-1.

/// Gets PMI parameter sizes for \e TypeI-SinglePanel Mode 1 codebook configuration as per TS38.212 Table 6.3.1.1.2-1.
pmi_typeI_single_panel_param_sizes get_pmi_sizes_typeI_single_panel(const pmi_codebook_single_panel_info& panel_info,
                                                                    uint8_t                               ri);


} // namespace ocudu
