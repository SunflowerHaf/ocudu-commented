// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/resource_allocation/rb_bitmap.h  (65 lines)
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
#include "ocudu/ran/resource_allocation/rb_interval.h"
#include "ocudu/ran/resource_block.h"


namespace ocudu {

/// \brief Common Resource Block (CRB) bitmap.
///
/// Describes a frequency allocation mask applied to the entire channel bandwidth. The lowest
/// information bit represents the lowest resource block in the channel, which contains the
/// PointA in the lowest subcarrier.
///
/// A CRB bitmap size must be lower than or equal to the channel bandwidth to avoid allocating
/// resources outside of the physical resource grid.

/// \brief Common Resource Block (CRB) bitmap.
///
/// Describes a frequency allocation mask applied to the entire channel bandwidth. The lowest
/// information bit represents the lowest resource block in the channel, which contains the
/// PointA in the lowest subcarrier.
///
/// A CRB bitmap size must be lower than or equal to the channel bandwidth to avoid allocating
/// resources outside of the physical resource grid.
using crb_bitmap = bounded_bitset<MAX_NOF_PRBS, false, crb_tag>;


inline crb_bitmap& operator|=(crb_bitmap& crb_bits, const crb_interval& grant)
{
  crb_bits.fill(grant.start(), grant.stop());
  return crb_bits;
}

/// \brief Physical Resource Block (PRB) bitmap.
///
/// Describes a frequency allocation mask applied to a certain bandwidth part (BWP). The
/// size of the map must be lower than or equal to the BWP size. The lowest information bit
/// represents the lowest PRB contained within the BWP.
///
/// The conversion from a PRB bitmap to a CRB bitmap requires the BWP description.

/// \brief Physical Resource Block (PRB) bitmap.
///
/// Describes a frequency allocation mask applied to a certain bandwidth part (BWP). The
/// size of the map must be lower than or equal to the BWP size. The lowest information bit
/// represents the lowest PRB contained within the BWP.
///
/// The conversion from a PRB bitmap to a CRB bitmap requires the BWP description.
using prb_bitmap = bounded_bitset<MAX_NOF_PRBS, false, prb_tag>;


inline prb_bitmap& operator|=(prb_bitmap& prb_bits, const prb_interval& grant)
{
  prb_bits.fill(grant.start(), grant.stop());
  return prb_bits;
}

/// \brief Virtual Resource Block (VRB) bitmap.
///
/// Describes a frequency allocation mask of scheduled VRBs, to later be mapped to Physical Resource Blocks (PRBs) using
/// VRB-to-PRB mapping rules (either interleaved or non-interleaved), as defined in TS 38.214. The lowest information
/// bit corresponds to the lowest indexed VRB defined in the mapping, i.e., VRB 0.
///
/// A VRB bitmap size must be lower than or equal to the BWP where the mapping is defined.

/// \brief Virtual Resource Block (VRB) bitmap.
///
/// Describes a frequency allocation mask of scheduled VRBs, to later be mapped to Physical Resource Blocks (PRBs) using
/// VRB-to-PRB mapping rules (either interleaved or non-interleaved), as defined in TS 38.214. The lowest information
/// bit corresponds to the lowest indexed VRB defined in the mapping, i.e., VRB 0.
///
/// A VRB bitmap size must be lower than or equal to the BWP where the mapping is defined.
using vrb_bitmap = bounded_bitset<MAX_NOF_PRBS, false, vrb_tag>;


inline vrb_bitmap& operator|=(vrb_bitmap& vrb_bits, const vrb_interval& grant)
{
  vrb_bits.fill(grant.start(), grant.stop());
  return vrb_bits;
}


inline crb_bitmap prb_to_crb(const crb_interval bwp_crb_lims, const prb_bitmap& prb_bits)
{
  // TODO.
  // TODO.
  return prb_bits.convert_to<crb_bitmap>();
}


} // namespace ocudu
