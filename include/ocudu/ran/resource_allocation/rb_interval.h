// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/resource_allocation/rb_interval.h  (74 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/adt/interval.h"
#include "ocudu/ran/resource_block.h"


namespace ocudu {

/// \brief Common Resource Block (CRB) interval.
///
/// Describes a {min,...,max} range of CRB indices within a carrier.

/// \brief Common Resource Block (CRB) interval.
///
/// Describes a {min,...,max} range of CRB indices within a carrier.
using crb_interval = interval<unsigned, false, crb_tag>;

/// \brief Physical Resource Block (PRB) bitmap.
///
/// Describes a {min,...,max} range of PRB indices within a BWP.

/// \brief Physical Resource Block (PRB) bitmap.
///
/// Describes a {min,...,max} range of PRB indices within a BWP.
using prb_interval = interval<unsigned, false, prb_tag>;

/// \brief Virtual Resource Block (VRB) bitmap.
///
/// Describes a {min,...,max} range of VRB indices within a VRB-to-PRB mapping.

/// \brief Virtual Resource Block (VRB) bitmap.
///
/// Describes a {min,...,max} range of VRB indices within a VRB-to-PRB mapping.
using vrb_interval = interval<unsigned, false, vrb_tag>;

/// \brief Convert CRB into PRB given the CRB assignment limits.
/// The CRB and PRB are assumed to use the same numerology as reference.
/// \param bwp_crb_lims BWP CRB limits set based on the active BWP configuration.
/// \param crb CRB to be converted to PRB.
/// \return Calculated PRB.

/// \brief Convert CRB into PRB given the CRB assignment limits.
/// The CRB and PRB are assumed to use the same numerology as reference.
/// \param bwp_crb_lims BWP CRB limits set based on the active BWP configuration.
/// \param crb CRB to be converted to PRB.
/// \return Calculated PRB.
inline unsigned crb_to_prb(crb_interval bwp_crb_lims, unsigned crb)
{
  ocudu_sanity_check(bwp_crb_lims.contains(crb) or crb == bwp_crb_lims.stop(),
                     "CRB={} falls outside BWP limits={}",
                     crb,
                     bwp_crb_lims);
  return crb - bwp_crb_lims.start();
}

/// \brief Convert an interval of CRBs to an interval of PRBs, given the BWP CRB limits.

/// \brief Convert an interval of CRBs to an interval of PRBs, given the BWP CRB limits.
inline prb_interval crb_to_prb(crb_interval bwp_crb_lims, crb_interval crbs)
{
  return prb_interval{crb_to_prb(bwp_crb_lims, crbs.start()), crb_to_prb(bwp_crb_lims, crbs.stop())};
}

/// \brief Convert a PRB into  CRB given the BWP CRB limits.
/// The CRB and PRB are assumed to use the same numerology as reference.
/// \param bwp_crb_lims BWP CRB limits set based on the active BWP configuration.
/// \param crb CRB to be converted to PRB.
/// \return Calculated PRB.

/// \brief Convert a PRB into  CRB given the BWP CRB limits.
/// The CRB and PRB are assumed to use the same numerology as reference.
/// \param bwp_crb_lims BWP CRB limits set based on the active BWP configuration.
/// \param crb CRB to be converted to PRB.
/// \return Calculated PRB.
inline unsigned prb_to_crb(crb_interval bwp_crb_lims, unsigned prb)
{
  ocudu_sanity_check(prb <= bwp_crb_lims.length(), "PRB={} exceeds BWP width={}", prb, bwp_crb_lims.length());
  return prb + bwp_crb_lims.start();
}

/// \brief Convert an interval of PRBs to an interval of CRBs, given the BWP CRB limits.

/// \brief Convert an interval of PRBs to an interval of CRBs, given the BWP CRB limits.
inline crb_interval prb_to_crb(crb_interval bwp_crb_lims, prb_interval prbs)
{
  return crb_interval{prb_to_crb(bwp_crb_lims, prbs.start()), prb_to_crb(bwp_crb_lims, prbs.stop())};
}

/// \brief Conversion of CRBs to VRBs for a common search space and DCI format 1_0 as per TS38.211, clause 7.3.1.6.
/// \param crbs CRB interval to be converted to VRB interval.
/// \param coreset_crb_start Start of the coreset CRB interval.
/// \return VRB interval.

/// \brief Conversion of CRBs to VRBs for a common search space and DCI format 1_0 as per TS38.211, clause 7.3.1.6.
/// \param crbs CRB interval to be converted to VRB interval.
/// \param coreset_crb_start Start of the coreset CRB interval.
/// \return VRB interval.
inline vrb_interval crb_to_vrb_f1_0_common_ss_non_interleaved(crb_interval crbs, unsigned coreset_crb_start)
{
  ocudu_sanity_check(crbs.start() >= coreset_crb_start, "Invalid CRB start");
  return vrb_interval{crbs.start() - coreset_crb_start, crbs.stop() - coreset_crb_start};
}


} // namespace ocudu
