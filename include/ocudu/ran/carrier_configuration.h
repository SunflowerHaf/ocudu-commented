// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/carrier_configuration.h  (28 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "arfcn.h"
#include "ocudu/ran/bs_channel_bandwidth.h"
#include "ocudu/ran/nr_band.h"
#include <cstdint>


namespace ocudu {

/// \brief Configuration of each transmission point associated to the corresponding cell(s). This includes
/// different physical antennas, different frequencies, bandwidths.

/// \brief Configuration of each transmission point associated to the corresponding cell(s). This includes
/// different physical antennas, different frequencies, bandwidths.
struct carrier_configuration {
  /// Width of this carrier in MHz.
  /// Width of this carrier in MHz.
  bs_channel_bandwidth carrier_bw = bs_channel_bandwidth::MHz10;
  /// NR Absolute Radio Frequency Channel Number (NR-ARFCN) of "F_REF", which is the RF reference frequency, as per
  /// TS 38.104, Section 5.4.2.1 ("F_REF" maps to the central frequency of the band).
  /// NR Absolute Radio Frequency Channel Number (NR-ARFCN) of "F_REF", which is the RF reference frequency, as per
  /// TS 38.104, Section 5.4.2.1 ("F_REF" maps to the central frequency of the band).
  arfcn_t arfcn_f_ref = 365000;
  /// <em>NR operating band<\em>, as per Table 5.2-1 and 5.2-2. TS 38.104.
  /// <em>NR operating band<\em>, as per Table 5.2-1 and 5.2-2. TS 38.104.
  nr_band band = nr_band::invalid;
  /// Number of antennas. Values: (0..65355).
  /// Number of antennas. Values: (0..65355).
  uint16_t nof_ant = 1;
};


} // namespace ocudu
