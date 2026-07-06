// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

///\file
///\brief pdsch_constants - namespace containing constants related to PDSCH transmissions.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdsch/pdsch_constants.h  (63 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

///\file
///\brief pdsch_constants - namespace containing constants related to PDSCH transmissions.

#pragma once


#include "ocudu/ran/resource_block.h"
#include "ocudu/support/units.h"
#include <cstddef>


namespace ocudu {


namespace pdsch_constants {

/// \brief Maximum number of RE per resource block in a PDSCH transmission.
///
/// As per TS38.214 Section 5.1.3.2.

/// \brief Maximum number of RE per resource block in a PDSCH transmission.
///
/// As per TS38.214 Section 5.1.3.2.
constexpr unsigned MAX_NRE_PER_RB = 156;

/// \brief Maximum modulation order supported on PDSCH transmissions.
///
/// As per TS38.214 Section 5.1.3.1 with \c mcs-Table set to \c qam256.

/// \brief Maximum modulation order supported on PDSCH transmissions.
///
/// As per TS38.214 Section 5.1.3.1 with \c mcs-Table set to \c qam256.
constexpr unsigned MAX_MODULATION_ORDER = 8;

/// \brief Maximum number of PDSCH transmission layers per codeword.
///
/// As per TS38.211 Table 7.3.1.3-1.

/// \brief Maximum number of PDSCH transmission layers per codeword.
///
/// As per TS38.211 Table 7.3.1.3-1.
constexpr unsigned CODEWORD_MAX_NOF_LAYERS = 4;

/// \brief Maximuym number of codewords that can be contained in a PDSCH transmission.
///
/// As per TS38.211 Table 7.3.1.3-1.

/// \brief Maximuym number of codewords that can be contained in a PDSCH transmission.
///
/// As per TS38.211 Table 7.3.1.3-1.
constexpr unsigned MAX_NOF_CODEWORDS = 2;

/// \brief Maximum number of PDSCH transmission layers.
///
/// As per TS38.211 Table 7.3.1.3-1.

/// \brief Maximum number of PDSCH transmission layers.
///
/// As per TS38.211 Table 7.3.1.3-1.
constexpr unsigned MAX_NOF_LAYERS = CODEWORD_MAX_NOF_LAYERS * MAX_NOF_CODEWORDS;

/// \brief Maximum number of resource elements that can be mapped into a single codeword.
///
/// Calculated as the product of maximum number or RE per PRB and the maximum number of PRB in the a resource grid.

/// \brief Maximum number of resource elements that can be mapped into a single codeword.
///
/// Calculated as the product of maximum number or RE per PRB and the maximum number of PRB in the a resource grid.
constexpr unsigned CODEWORD_MAX_NOF_RE = MAX_NRE_PER_RB * MAX_NOF_PRBS;

/// \brief Maximum number of symbols that can be mapped into a single codeword.
///
/// Calculated as the product of the maximum number of resource elements and the maximum layers

/// \brief Maximum number of symbols that can be mapped into a single codeword.
///
/// Calculated as the product of the maximum number of resource elements and the maximum layers
constexpr unsigned CODEWORD_MAX_SYMBOLS = CODEWORD_MAX_NOF_RE * CODEWORD_MAX_NOF_LAYERS;

/// \brief Maximum number of bits that can be modulated into a single codeword.
///
/// Calculated as the product of the maximum number of resource elements and the maximum modulation order.

/// \brief Maximum number of bits that can be modulated into a single codeword.
///
/// Calculated as the product of the maximum number of resource elements and the maximum modulation order.
constexpr units::bits CODEWORD_MAX_SIZE{CODEWORD_MAX_SYMBOLS * MAX_MODULATION_ORDER};


} // namespace pdsch_constants

/// \brief Maximum size in bytes of a PDSCH PDU for a given UE.

/// \brief Maximum size in bytes of a PDSCH PDU for a given UE.
constexpr size_t MAX_DL_PDU_LENGTH = pdsch_constants::CODEWORD_MAX_SIZE.round_up_to_bytes().value();


} // namespace ocudu
