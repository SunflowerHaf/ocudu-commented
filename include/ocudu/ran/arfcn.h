// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/arfcn.h  (26 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "../adt/bounded_integer.h"


namespace ocudu {

/// Absolute Radio Frequency Channel Number (ARFCN), as per TS 38.104, Section 5.4.2.1.

/// Absolute Radio Frequency Channel Number (ARFCN), as per TS 38.104, Section 5.4.2.1.
using arfcn_t = bounded_integer<uint32_t, 0, 3279165>;

/// Max ARFCN valid value, as of TS 38.104 V17.8.0.

/// Max ARFCN valid value, as of TS 38.104 V17.8.0.
constexpr arfcn_t MAX_ARFCN = arfcn_t::max();

/// Min ARFCN value for range of frequencies 3GHz-24.25GHz, as per Table 5.4.2.1-1, TS 38.104.

/// Min ARFCN value for range of frequencies 3GHz-24.25GHz, as per Table 5.4.2.1-1, TS 38.104.
constexpr arfcn_t MIN_ARFCN_3_GHZ_24_5_GHZ = 600000;
/// Min ARFCN value for range of frequencies above 24.25GHz, as per Table 5.4.2.1-1, TS 38.104.
/// Min ARFCN value for range of frequencies above 24.25GHz, as per Table 5.4.2.1-1, TS 38.104.
constexpr arfcn_t MIN_ARFCN_24_5_GHZ_100_GHZ = 2016667;
/// The cutoff frequency for case A, B and C paired is 3GHz, corresponding to 600000 ARFCN (TS 38.213, Section 4.1).
/// The cutoff frequency for case A, B and C paired is 3GHz, corresponding to 600000 ARFCN (TS 38.213, Section 4.1).
constexpr arfcn_t CUTOFF_FREQ_ARFCN_CASE_A_B_C = MIN_ARFCN_3_GHZ_24_5_GHZ;
/// The cutoff frequency for case C unpaired is 1.88GHz, corresponding to 376000 ARFCN (TS 38.213, Section 4.1).
/// The cutoff frequency for case C unpaired is 1.88GHz, corresponding to 376000 ARFCN (TS 38.213, Section 4.1).
constexpr arfcn_t CUTOFF_FREQ_ARFCN_CASE_C_UNPAIRED = 376000;


} // namespace ocudu
