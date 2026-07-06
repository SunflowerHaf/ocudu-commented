// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/precoding/precoding_constants.h  (28 lines)
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
#include "ocudu/support/math/math_utils.h"


namespace ocudu {


namespace precoding_constants {

/// Minimum precoding PRG size.

/// Minimum precoding PRG size.
constexpr unsigned MIN_PRG_SIZE = 4;

/// Maximum number of PRG.

/// Maximum number of PRG.
constexpr unsigned MAX_NOF_PRG = divide_ceil(MAX_NOF_PRBS, MIN_PRG_SIZE);

/// Maximum number of layers supported by the precoder.

/// Maximum number of layers supported by the precoder.
constexpr unsigned MAX_NOF_LAYERS = 8;

/// Maximum number of ports supported by the precoder.

/// Maximum number of ports supported by the precoder.
constexpr unsigned MAX_NOF_PORTS = 8;


} // namespace precoding_constants


} // namespace ocudu
