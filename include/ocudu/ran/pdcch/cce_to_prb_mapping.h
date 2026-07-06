// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/pdcch/cce_to_prb_mapping.h  (68 lines)
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
#include "ocudu/adt/static_vector.h"
#include "ocudu/ran/pci.h"
#include "ocudu/ran/pdcch/coreset.h"
#include "ocudu/ran/pdcch/pdcch_constants.h"


namespace ocudu {

/// Describes a PRB index list of unsigned 16 bit indicating the PRB index.

/// Describes a PRB index list of unsigned 16 bit indicating the PRB index.
using prb_index_list = static_vector<uint16_t, pdcch_constants::MAX_NOF_RB_PDCCH>;

/// \brief Calculates the PDCCH CCE to PRB mapping for a PDCCH transmission in CORESET0.
///
/// \param[in] N_coreset0_start  The lowest RB index of the CORESET0 relative to CRB0 (PointA).
/// \param[in] N_coreset0_size   The CORESET0 bandwidth in RBs.
/// \param[in] N_symb_coreset    The number of symbols for the PDCCH transmission.
/// \param[in] N_id_cell         Physical cell identifier.
/// \param[in] aggregation_level Number of CCE used for the PDCCH transmission.
/// \param[in] cce_index         Initial CCE index for the PDCCH transmision.
/// \return A list of the resource blocks used by the PDCCH transmission.

/// \brief Calculates the PDCCH CCE to PRB mapping for a PDCCH transmission in CORESET0.
///
/// \param[in] N_coreset0_start  The lowest RB index of the CORESET0 relative to CRB0 (PointA).
/// \param[in] N_coreset0_size   The CORESET0 bandwidth in RBs.
/// \param[in] N_symb_coreset    The number of symbols for the PDCCH transmission.
/// \param[in] N_id_cell         Physical cell identifier.
/// \param[in] aggregation_level Number of CCE used for the PDCCH transmission.
/// \param[in] cce_index         Initial CCE index for the PDCCH transmision.
/// \return A list of the resource blocks used by the PDCCH transmission.
prb_index_list cce_to_prb_mapping_coreset0(unsigned N_coreset0_start,
                                           unsigned N_coreset0_size,
                                           unsigned N_symb_coreset,
                                           pci_t    N_id_cell,
                                           unsigned aggregation_level,
                                           unsigned cce_index);

/// \brief Calculates the PDCCH CCE to PRB mapping for a non-interleaved PDCCH transmission.
///
/// \param[in] N_bwp_start       Start of the BWP relative to CRB0 (PointA).
/// \param[in] freq_resources    Indicates the frequency resources active for the CORESET.
/// \param[in] N_symb_coreset    The number of symbols for the PDCCH transmission.
/// \param[in] aggregation_level Number of CCE used for the PDCCH transmission.
/// \param[in] cce_index         Initial CCE index for the PDCCH transmision.
/// \return A list of the resource blocks used by the PDCCH transmission.

/// \brief Calculates the PDCCH CCE to PRB mapping for a non-interleaved PDCCH transmission.
///
/// \param[in] N_bwp_start       Start of the BWP relative to CRB0 (PointA).
/// \param[in] freq_resources    Indicates the frequency resources active for the CORESET.
/// \param[in] N_symb_coreset    The number of symbols for the PDCCH transmission.
/// \param[in] aggregation_level Number of CCE used for the PDCCH transmission.
/// \param[in] cce_index         Initial CCE index for the PDCCH transmision.
/// \return A list of the resource blocks used by the PDCCH transmission.
prb_index_list cce_to_prb_mapping_non_interleaved(unsigned                    N_bwp_start,
                                                  const freq_resource_bitmap& freq_resources,
                                                  unsigned                    N_symb_coreset,
                                                  unsigned                    aggregation_level,
                                                  unsigned                    cce_index);

/// \brief Calculates the PDCCH CCE to PRB mapping for an interleaved PDCCH transmission.
///
/// \param[in] N_bwp_start       Start of the BWP relative to CRB0 (PointA).
/// \param[in] freq_resources    Indicates the frequency resources active for the CORESET.
/// \param[in] N_symb_coreset    The number of symbols for the PDCCH transmission.
/// \param[in] reg_bundle_size   Parameter \c reg-BundleSize.
/// \param[in] interleaver_size  Parameter \c interleaverSize.
/// \param[in] shift_index       Parameter \c shiftIndex if available, otherwise \f$N_{ID}^{cell}\f$.
/// \param[in] aggregation_level Number of CCE used for the PDCCH transmission.
/// \param[in] cce_index         Initial CCE index for the PDCCH transmision.
/// \return A list of the resource blocks used by the PDCCH transmission.

/// \brief Calculates the PDCCH CCE to PRB mapping for an interleaved PDCCH transmission.
///
/// \param[in] N_bwp_start       Start of the BWP relative to CRB0 (PointA).
/// \param[in] freq_resources    Indicates the frequency resources active for the CORESET.
/// \param[in] N_symb_coreset    The number of symbols for the PDCCH transmission.
/// \param[in] reg_bundle_size   Parameter \c reg-BundleSize.
/// \param[in] interleaver_size  Parameter \c interleaverSize.
/// \param[in] shift_index       Parameter \c shiftIndex if available, otherwise \f$N_{ID}^{cell}\f$.
/// \param[in] aggregation_level Number of CCE used for the PDCCH transmission.
/// \param[in] cce_index         Initial CCE index for the PDCCH transmision.
/// \return A list of the resource blocks used by the PDCCH transmission.
prb_index_list cce_to_prb_mapping_interleaved(unsigned                    N_bwp_start,
                                              const freq_resource_bitmap& freq_resources,
                                              unsigned                    N_symb_coreset,
                                              unsigned                    reg_bundle_size,
                                              unsigned                    interleaver_size,
                                              unsigned                    shift_index,
                                              unsigned                    aggregation_level,
                                              unsigned                    cce_index);


} // namespace ocudu
