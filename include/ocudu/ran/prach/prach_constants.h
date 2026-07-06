// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/prach/prach_constants.h  (52 lines)
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
#include "ocudu/ran/time/radio_frame_constants.h"


namespace ocudu {


namespace prach_constants {

/// Long sequence length as per TS38.211 Section 6.3.3.1, case \f$L_{RA}=839\f$.

/// Long sequence length as per TS38.211 Section 6.3.3.1, case \f$L_{RA}=839\f$.
constexpr unsigned LONG_SEQUENCE_LENGTH = 839U;

/// Maximum number of OFDM symbols per slot containing long-sequence PRACH preambles. Inferred from TS38.211
/// Table 6.3.3.1-1.

/// Maximum number of OFDM symbols per slot containing long-sequence PRACH preambles. Inferred from TS38.211
/// Table 6.3.3.1-1.
constexpr unsigned LONG_SEQUENCE_MAX_NOF_SYMBOLS = 4U;

/// Short sequence length as per TS38.211 Section 6.3.3.1, case \f$L_{RA}=139\f$.

/// Short sequence length as per TS38.211 Section 6.3.3.1, case \f$L_{RA}=139\f$.
constexpr unsigned SHORT_SEQUENCE_LENGTH = 139U;

/// Maximum number of OFDM symbols per slot containing short-sequence PRACH preambles. Inferred from TS38.211
/// Table 6.3.3.1-2.

/// Maximum number of OFDM symbols per slot containing short-sequence PRACH preambles. Inferred from TS38.211
/// Table 6.3.3.1-2.
constexpr unsigned SHORT_SEQUENCE_MAX_NOF_SYMBOLS = 12U;

/// Maximum PRACH reception window length in the time domain equal to half frame. Inferred from TS38.211 Table
/// 6.3.3.1-1, taking the maximum of \f$N_u+N_{CP}^{RA}\f$ rounded to the next subframe.

/// Maximum PRACH reception window length in the time domain equal to half frame. Inferred from TS38.211 Table
/// 6.3.3.1-1, taking the maximum of \f$N_u+N_{CP}^{RA}\f$ rounded to the next subframe.
constexpr phy_time_unit MAX_WINDOW_LENGTH = phy_time_unit::from_seconds(5e-3);

/// Maximum number of preambles per time-frequency PRACH occasion as per TS38.211 Section 6.3.3.1.

/// Maximum number of preambles per time-frequency PRACH occasion as per TS38.211 Section 6.3.3.1.
constexpr unsigned MAX_NUM_PREAMBLES = 64;

/// Maximum number of PRACH time-domain occasions within a slot as per TS38.211, Tables 6.3.3.2-[2-4].

/// Maximum number of PRACH time-domain occasions within a slot as per TS38.211, Tables 6.3.3.2-[2-4].
constexpr unsigned MAX_NOF_PRACH_TD_OCCASIONS = 7;

/// Maximum number of PRACH frequency-domain occasions within a slot. It is given by the maximum value of \e msg1-FDM in
/// TS38.331 Section 6.3.2 Information Element \e RACH-ConfigGeneric.

/// Maximum number of PRACH frequency-domain occasions within a slot. It is given by the maximum value of \e msg1-FDM in
/// TS38.331 Section 6.3.2 Information Element \e RACH-ConfigGeneric.
constexpr unsigned MAX_NOF_PRACH_FD_OCCASIONS = 8;

/// Maximum number of PRACH occasions within a slot as per TS38.211, Tables 6.3.3.2-[2-4] and maximum msg1-FDM of 8
/// according to TS 38.331.

/// Maximum number of PRACH occasions within a slot as per TS38.211, Tables 6.3.3.2-[2-4] and maximum msg1-FDM of 8
/// according to TS 38.331.
constexpr size_t MAX_NOF_PRACH_OCCASIONS_PER_SLOT = MAX_NOF_PRACH_TD_OCCASIONS * MAX_NOF_PRACH_FD_OCCASIONS;

/// Maximum PRACH SFN opportunity period. Maximum value for the parameter \f$x\f$. This value is deduced from TS
/// 38.211 Tables 6.3.3.2-2, 6.3.3.2-3, and 6.3.3.2-4.

/// Maximum PRACH SFN opportunity period. Maximum value for the parameter \f$x\f$. This value is deduced from TS
/// 38.211 Tables 6.3.3.2-2, 6.3.3.2-3, and 6.3.3.2-4.
static constexpr unsigned MAX_PRACH_SFN_PERIOD = 16;


} // namespace prach_constants


} // namespace ocudu
