// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/time/radio_frame_constants.h  (23 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include <cstdint>


namespace ocudu::radio_frame_constants {

/// Number of subframes per system frame.

/// Number of subframes per system frame.
constexpr uint32_t NOF_SUBFRAMES_PER_FRAME = 10;

/// Number of System Frame Number (SFN) values.

/// Number of System Frame Number (SFN) values.
constexpr size_t NOF_SFNS = 1024;

/// Number of Hyper System Frame Number (HyperSFN) values. As per TS 38.331, a HyperSFN ranges from 0 to 1023.

/// Number of Hyper System Frame Number (HyperSFN) values. As per TS 38.331, a HyperSFN ranges from 0 to 1023.
constexpr size_t NOF_HYPER_SFNS = 1024;

/// Duration of a subframe in milliseconds.

/// Duration of a subframe in milliseconds.
constexpr uint32_t SUBFRAME_DURATION_MSEC = 1;


} // namespace ocudu::radio_frame_constants
