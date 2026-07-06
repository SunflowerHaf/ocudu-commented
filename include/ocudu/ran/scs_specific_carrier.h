// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/scs_specific_carrier.h  (34 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/subcarrier_spacing.h"
#include <optional>


namespace ocudu {

/// \brief It provides parameters determining the location and width of the actual carrier.
/// \remark See TS 38.331, "SCS-SpecificCarrier".

/// \brief It provides parameters determining the location and width of the actual carrier.
/// \remark See TS 38.331, "SCS-SpecificCarrier".
struct scs_specific_carrier {
  /// Offset between Point A (lowest subcarrier of common RB 0) and the lowest usable subcarrier in this carrier in
  /// number of PRBs. Values: (0..2199).
  /// Offset between Point A (lowest subcarrier of common RB 0) and the lowest usable subcarrier in this carrier in
  /// number of PRBs. Values: (0..2199).
  unsigned           offset_to_carrier;
  subcarrier_spacing scs;
  /// Width of this carrier in number of PRBs. Values: (0..MAX_NOF_PRBS).
  /// Width of this carrier in number of PRBs. Values: (0..MAX_NOF_PRBS).
  unsigned carrier_bandwidth;
  /// Indicates the downlink Tx Direct Current location for the carrier. A value in the range 0..3299 indicates the
  /// subcarrier index within the carrier. The values in the value range 3301..4095 are reserved and ignored by the UE.
  /// If this field is absent, the UE assumes the default value of 3300 (i.e. "Outside the carrier").
  /// Indicates the downlink Tx Direct Current location for the carrier. A value in the range 0..3299 indicates the
  /// subcarrier index within the carrier. The values in the value range 3301..4095 are reserved and ignored by the UE.
  /// If this field is absent, the UE assumes the default value of 3300 (i.e. "Outside the carrier").
  std::optional<unsigned> tx_direct_current_location;


  bool operator==(const scs_specific_carrier& rhs) const
  {
    return offset_to_carrier == rhs.offset_to_carrier && scs == rhs.scs && carrier_bandwidth == rhs.carrier_bandwidth &&
           tx_direct_current_location == rhs.tx_direct_current_location;
  }
  bool operator!=(const scs_specific_carrier& rhs) const { return !(rhs == *this); }
};


} // namespace ocudu
