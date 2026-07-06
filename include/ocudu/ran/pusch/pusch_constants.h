// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

///\file
///\brief pusch_constants - namespace containing constants related to PUSCH transmissions.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pusch/pusch_constants.h  (66 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

///\file
///\brief pusch_constants - namespace containing constants related to PUSCH transmissions.

#pragma once


#include "ocudu/ran/resource_block.h"
#include "ocudu/support/units.h"


namespace ocudu {


namespace pusch_constants {

/// \brief Maximum number of RE per resource block in a PUSCH transmission.
///
/// As per TS38.214 Section 6.1.4.2.

/// \brief Maximum number of RE per resource block in a PUSCH transmission.
///
/// As per TS38.214 Section 6.1.4.2.
constexpr unsigned MAX_NRE_PER_RB = 156;

/// \brief Maximum modulation order supported on PUSCH transmissions.
///
/// As per TS38.214 Section 6.1.4.1 with \c mcs-Table set to \c qam256.

/// \brief Maximum modulation order supported on PUSCH transmissions.
///
/// As per TS38.214 Section 6.1.4.1 with \c mcs-Table set to \c qam256.
constexpr unsigned MAX_MODULATION_ORDER = 8;

/// \brief Maximum number of PUSCH transmission layers.
///
/// As per TS38.211 Section 6.3.1.3.

/// \brief Maximum number of PUSCH transmission layers.
///
/// As per TS38.211 Section 6.3.1.3.
constexpr unsigned MAX_NOF_LAYERS = 4;

/// \brief Maximum number of receive ports for receiving PUSCH.
///
/// Equal to the maximum number of transmission layers for PUSCH.

/// \brief Maximum number of receive ports for receiving PUSCH.
///
/// Equal to the maximum number of transmission layers for PUSCH.
constexpr unsigned MAX_NOF_RX_PORTS = MAX_NOF_LAYERS;

/// Returns number of REs per codeword in a single transmission.

/// Returns number of REs per codeword in a single transmission.
constexpr unsigned get_codeword_max_symbols(unsigned nof_prb, unsigned nof_layers)
{
  return nof_prb * pusch_constants::MAX_NRE_PER_RB * nof_layers;
}

/// Returns number of encoded bits per codeword in a single transmission.

/// Returns number of encoded bits per codeword in a single transmission.
constexpr units::bits get_max_codeword_size(unsigned nof_prb, unsigned nof_layers)
{
  return units::bits{get_codeword_max_symbols(nof_prb, nof_layers) * pusch_constants::MAX_MODULATION_ORDER};
}

/// Maximum number of bits per OFDM symbol.

/// Maximum number of bits per OFDM symbol.
constexpr unsigned MAX_NOF_BITS_PER_OFDM_SYMBOL =
    MAX_NOF_LAYERS * MAX_NOF_SUBCARRIERS * pusch_constants::MAX_MODULATION_ORDER;

/// Maximum number of OFDM symbols carrying DM-RS in a slot is at most \f$4 \times 2\f$, being 4 the maximum
/// number of positions \f$\bar{l}\f$ and 2 the maximum number of indices \f$l'\f$, as per TS38.211 Section 6.4.1.1.

/// Maximum number of OFDM symbols carrying DM-RS in a slot is at most \f$4 \times 2\f$, being 4 the maximum
/// number of positions \f$\bar{l}\f$ and 2 the maximum number of indices \f$l'\f$, as per TS38.211 Section 6.4.1.1.
constexpr unsigned MAX_NOF_DMRS_SYMBOLS = 4 * 2;

/// Maximum number of subcarriers carrying DM-RS in a symbol. It is at most half of the total number of subcarriers
/// (i.e., <tt>MAX_NOF_SUBCARRIERS / 2</tt>) is assigned a DM-RS symbol.

/// Maximum number of subcarriers carrying DM-RS in a symbol. It is at most half of the total number of subcarriers
/// (i.e., <tt>MAX_NOF_SUBCARRIERS / 2</tt>) is assigned a DM-RS symbol.
constexpr unsigned MAX_NOF_DMRS_SUBC = MAX_NOF_SUBCARRIERS / 2;

/// Maximum number of PUSCH time domain resource allocations. See TS 38.331, \c maxNrofUL-Allocations.

/// Maximum number of PUSCH time domain resource allocations. See TS 38.331, \c maxNrofUL-Allocations.
constexpr unsigned MAX_NOF_PUSCH_TD_RES_ALLOCS = 16;


} // namespace pusch_constants


} // namespace ocudu
