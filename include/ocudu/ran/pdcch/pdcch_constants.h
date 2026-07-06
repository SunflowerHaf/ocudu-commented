// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/pdcch_constants.h  (59 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/resource_block.h"


namespace ocudu {
namespace pdcch_constants {

/// Defines the number if resource blocks per frequency resource in a CORESET as per TS38.331 in ControlResourceSet
/// information element.

/// Defines the number if resource blocks per frequency resource in a CORESET as per TS38.331 in ControlResourceSet
/// information element.
constexpr unsigned NOF_RB_PER_FREQ_RESOURCE = 6;

/// Defines the maximum number of frequency resources in a CORESET as per TS38.331 in ControlResourceSet
/// information element.

/// Defines the maximum number of frequency resources in a CORESET as per TS38.331 in ControlResourceSet
/// information element.
constexpr unsigned MAX_NOF_FREQ_RESOURCES = MAX_NOF_PRBS / NOF_RB_PER_FREQ_RESOURCE;

/// Maximum number of DCIs in a single transmission (it is not specified by the TS).

/// Maximum number of DCIs in a single transmission (it is not specified by the TS).
constexpr unsigned MAX_NOF_DCI = 1;

/// Maximum payload size in bits (it is not specified by the TS).

/// Maximum payload size in bits (it is not specified by the TS).
constexpr unsigned MAX_DCI_PAYLOAD_SIZE = 128;

/// Number of REs used for data in per RB and symbol as per TS38.211 section 7.3.2.5.

/// Number of REs used for data in per RB and symbol as per TS38.211 section 7.3.2.5.
constexpr unsigned NOF_RE_PDCCH_PER_RB = NOF_SUBCARRIERS_PER_RB - 3;

/// Number of REGs per CCE as per TS38.211 Section 7.3.2.2.

/// Number of REGs per CCE as per TS38.211 Section 7.3.2.2.
constexpr unsigned NOF_REG_PER_CCE = 6;

/// Number of CRC bits that are attached to a PDCCH, as per TS38.211 Section 7.1.3.

/// Number of CRC bits that are attached to a PDCCH, as per TS38.211 Section 7.1.3.
constexpr unsigned NOF_CRC_BITS = 24U;

/// Maximum CORESET duration in symbols as per TS38.211 Section 7.3.2.2. and TS 38.331 "maxCoReSetDuration".

/// Maximum CORESET duration in symbols as per TS38.211 Section 7.3.2.2. and TS 38.331 "maxCoReSetDuration".
constexpr unsigned MAX_CORESET_DURATION = 3;

/// Maximum aggregation level as per TS38.211 Table 7.3.2.1-1.

/// Maximum aggregation level as per TS38.211 Table 7.3.2.1-1.
constexpr unsigned MAX_AGGREGATION_LEVEL = 16;

/// \brief Maximum number of RBs that can be used for a single PDCCH transmission.
///
/// It coincides with the maximum number of REG that can be used for a single transmission.

/// \brief Maximum number of RBs that can be used for a single PDCCH transmission.
///
/// It coincides with the maximum number of REG that can be used for a single transmission.
constexpr unsigned MAX_NOF_RB_PDCCH = MAX_AGGREGATION_LEVEL * NOF_REG_PER_CCE;

/// Maximum number of REs for data in a single transmission.

/// Maximum number of REs for data in a single transmission.
constexpr unsigned MAX_NOF_RE_PDCCH = MAX_NOF_RB_PDCCH * NOF_RE_PDCCH_PER_RB;

/// Bits per symbol for QPSK, the modulation used for PDCCH, as per TS38.211 Section 7.3.2.4.

/// Bits per symbol for QPSK, the modulation used for PDCCH, as per TS38.211 Section 7.3.2.4.
constexpr unsigned QPSK_BITS_PER_SYMBOL = 2;

/// Define the maximum number of encoded data bits in a transmission.

/// Define the maximum number of encoded data bits in a transmission.
constexpr unsigned MAX_NOF_BITS = MAX_NOF_RE_PDCCH * QPSK_BITS_PER_SYMBOL;

/// Define the number of encoded data bits per CCE in a transmission.

/// Define the number of encoded data bits per CCE in a transmission.
constexpr unsigned NOF_BITS_PER_CCE = NOF_REG_PER_CCE * NOF_RE_PDCCH_PER_RB * QPSK_BITS_PER_SYMBOL;


} // namespace pdcch_constants
} // namespace ocudu
