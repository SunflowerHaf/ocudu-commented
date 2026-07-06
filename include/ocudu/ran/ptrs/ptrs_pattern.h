// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/ptrs/ptrs_pattern.h  (57 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/bounded_bitset.h"
#include "ocudu/adt/interval.h"
#include "ocudu/ran/cyclic_prefix.h"
#include "ocudu/ran/dmrs/dmrs.h"
#include "ocudu/ran/ptrs/ptrs.h"
#include "ocudu/ran/ptrs/ptrs_constants.h"
#include "ocudu/ran/resource_allocation/rb_bitmap.h"
#include "ocudu/ran/rnti.h"


namespace ocudu {

/// Required parameters to compute a PT-RS allocation pattern in a resource grid.

/// Required parameters to compute a PT-RS allocation pattern in a resource grid.
struct ptrs_pattern_configuration {
  /// RNTI associated with the DCI scheduling the transmission, parameter \f$n_{RNTI}\f$.
  /// RNTI associated with the DCI scheduling the transmission, parameter \f$n_{RNTI}\f$.
  rnti_t rnti;
  /// DM-RS config type (\e dmrsConfigType).
  /// DM-RS config type (\e dmrsConfigType).
  dmrs_config_type dmrs_type;
  /// DM-RS position mask. Indicates the OFDM symbols carrying DM-RS within the slot.
  /// DM-RS position mask. Indicates the OFDM symbols carrying DM-RS within the slot.
  bounded_bitset<MAX_NSYMB_PER_SLOT> dmrs_symbol_mask;
  /// Frequency domain allocation as CRB mask. The entries set to true are used for transmission.
  /// Frequency domain allocation as CRB mask. The entries set to true are used for transmission.
  crb_bitmap rb_mask;
  /// Time domain allocation of the transmission containing PT-RS.
  /// Time domain allocation of the transmission containing PT-RS.
  interval<uint8_t> time_allocation;
  /// Frequency domain density.
  /// Frequency domain density.
  ptrs_frequency_density freq_density;
  /// Time domain density.
  /// Time domain density.
  ptrs_time_density time_density;
  /// Resource element offset.
  /// Resource element offset.
  ptrs_re_offset re_offset;
  /// Number of transmit ports.
  /// Number of transmit ports.
  unsigned nof_ports;
};

/// PT-RS allocation pattern in a resource grid.

/// PT-RS allocation pattern in a resource grid.
struct ptrs_pattern {
  /// Resource block where the pattern begins in frequency domain, the range is {0, ..., 274}.
  /// Resource block where the pattern begins in frequency domain, the range is {0, ..., 274}.
  unsigned rb_begin;
  /// Resource block where the pattern ends in frequency domain (excluded), the range is {1, ..., 275}.
  /// Resource block where the pattern ends in frequency domain (excluded), the range is {1, ..., 275}.
  unsigned rb_end;
  /// Resource block index jump.
  /// Resource block index jump.
  unsigned rb_stride;
  /// RE used within the RB that contains PT-RS for a certain port.
  /// RE used within the RB that contains PT-RS for a certain port.
  static_vector<uint8_t, ptrs_constants::max_nof_ports> re_offset;
  /// Symbol mask. True entries indicate the symbols affected by the pattern within the slot.
  /// Symbol mask. True entries indicate the symbols affected by the pattern within the slot.
  bounded_bitset<MAX_NSYMB_PER_SLOT> symbol_mask;
};

/// Generates the PT-RS pattern from the given PT-RS parameters.

/// Generates the PT-RS pattern from the given PT-RS parameters.
ptrs_pattern get_ptrs_pattern(const ptrs_pattern_configuration& pattern_config);


} // namespace ocudu
