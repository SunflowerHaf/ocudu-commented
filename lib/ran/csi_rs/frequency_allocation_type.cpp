// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/ran/csi_rs/frequency_allocation_type.cpp  (35 lines)
//
// LIBRARY: lib/ran
// Core RAN type definitions and utility functions shared by all layers. Contains: ARFCN/frequency helpers, band lookup tables, PRACH configuration tables, PDCCH/PUCCH/PUSCH resource element calculations, slot_point arithmetic, MCS tables, LDPC/polar code constants, PCI validation, PLMN/cell-identity types, QoS/S-NSSAI types, and more. The single most widely-included library.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#include "ocudu/ran/csi_rs/frequency_allocation_type.h"


using namespace ocudu;
using namespace csi_rs;

// Returns the scaling value applied to the bit position in the frequency allocation bitmap as per TS38.211
// Section 7.4.1.5.3.

// Returns the scaling value applied to the bit position in the frequency allocation bitmap as per TS38.211
// Section 7.4.1.5.3.
static unsigned get_bitpos_scale(unsigned row)
{
  if (row == 1) {
    return 1;
  }
  if (row == 2) {
    return 1;
  }
  if (row == 4) {
    return 4;
  }
  return 2;
}

// Converts a frequency domain bitmap to the corresponding k_n values.

// Converts a frequency domain bitmap to the corresponding k_n values.
void ocudu::csi_rs::convert_freq_domain(freq_allocation_index_type&      dst,
                                        const freq_allocation_mask_type& src,
                                        unsigned                         row)
{
  const unsigned scale = get_bitpos_scale(row);
  for (const auto pos : src.get_bit_positions()) {
    dst.push_back(scale * pos);
  }
}
