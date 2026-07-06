// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/sch/sch_mcs.h  (37 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_integer.h"
#include "ocudu/ran/sch/modulation_scheme.h"


namespace ocudu {

/// Physical Downlink and Uplink Shared Channel Modulation and Code Scheme Index, parameter \$fI_{MCS}\$f in TS38.214
/// Section 5.1.3.1.

/// Physical Downlink and Uplink Shared Channel Modulation and Code Scheme Index, parameter \$fI_{MCS}\$f in TS38.214
/// Section 5.1.3.1.
using sch_mcs_index = bounded_integer<uint8_t, 0, 31>;

/// \brief Physical Downlink and Uplink Shared Channel Modulation and Coding Scheme breakdown.
///
/// Represents one row of an MCS table.

/// \brief Physical Downlink and Uplink Shared Channel Modulation and Coding Scheme breakdown.
///
/// Represents one row of an MCS table.
struct sch_mcs_description {
  /// Subcarrier modulation scheme.
  /// Subcarrier modulation scheme.
  modulation_scheme modulation;

  /// Target code rate, expressed as \f$R\times 1024\f$, range (0, ..., 1024).

  /// Target code rate, expressed as \f$R\times 1024\f$, range (0, ..., 1024).
  float target_code_rate;

  /// \brief Returns the target spectral efficiency, in bits per subcarrier access.
  /// \note The spectral efficiency is given by the target code rate times the number of bits per modulation symbol.

  /// \brief Returns the target spectral efficiency, in bits per subcarrier access.
  /// \note The spectral efficiency is given by the target code rate times the number of bits per modulation symbol.
  constexpr float get_spectral_efficiency() const
  {
    return get_bits_per_symbol(modulation) * get_normalised_target_code_rate();
  }

  /// \brief Returns the target code rate normalised between 0 and 1.

  /// \brief Returns the target code rate normalised between 0 and 1.
  constexpr float get_normalised_target_code_rate() const { return target_code_rate * (1.F / 1024); }
};


} // namespace ocudu
