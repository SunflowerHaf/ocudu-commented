// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/ssb/pbch_mib_message.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/ssb/ssb_properties.h"
#include "ocudu/ran/subcarrier_spacing.h"
#include <cstdint>


namespace ocudu {

/// \brief Collects the PBCH message contents for the Master Information Block (MIB) parameters.
///
/// The MIB is defined by Information Element \e MIB in TS38.331 Section 6.2.2.

/// \brief Collects the PBCH message contents for the Master Information Block (MIB) parameters.
///
/// The MIB is defined by Information Element \e MIB in TS38.331 Section 6.2.2.
struct pbch_mib_message {
  /// System Frame Number (0..1023). Parameter \e systemFrameNumber.
  /// System Frame Number (0..1023). Parameter \e systemFrameNumber.
  uint32_t sfn;
  /// \c true if the SS/PBCH block transmission is in an odd half frame, \c false otherwise.
  /// \c true if the SS/PBCH block transmission is in an odd half frame, \c false otherwise.
  bool hrf;
  /// Parameter \e subCarrierSpacingCommon.
  /// Parameter \e subCarrierSpacingCommon.
  subcarrier_spacing scs_common;
  /// Parameter \e ssb-SubcarrierOffset.
  /// Parameter \e ssb-SubcarrierOffset.
  ssb_subcarrier_offset subcarrier_offset;
  /// Field \e dmrs-TypeA-Position.
  /// Field \e dmrs-TypeA-Position.
  dmrs_typeA_position dmrs_typeA_pos;
  /// Field \e pdcch-ConfigSIB1.
  /// Field \e pdcch-ConfigSIB1.
  uint8_t pdcch_config_sib1;
  /// Field \e pdcch-ConfigSIB1.
  /// Field \e pdcch-ConfigSIB1.
  bool cell_barred;
  /// Field \e intraFreqReselection.
  /// Field \e intraFreqReselection.
  bool intrafreq_reselection;
  /// SSB opportunity index in a 5ms burst.
  /// SSB opportunity index in a 5ms burst.
  uint8_t ssb_block_index;
};


} // namespace ocudu
