// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/csi_rs/csi_rs_config_helpers.h  (38 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/csi_rs/csi_rs_types.h"
#include "ocudu/ran/csi_rs/frequency_allocation_type.h"


namespace ocudu {


namespace csi_rs {

/// \brief Returns the row index corresponding to Table 7.4.1.5.3-1, TS 38.211 given the CSI-RS configuration.
/// \param[in] nof_ports Number of ports, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] density Density, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] cdm_type CDM-type, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] fd_alloc Freq. Domain Allocation, as per \c frequencyDomainAllocation in \c CSI-RS-ResourceMapping,
///            TS 38.331.
/// \return The row index of Table 7.4.1.5.3-1, TS 38.211 corresponding to the inputs. If the given input configuration
///         does not match any of the rows in the table, the function triggers an assert and returns an invalid value
///         (i.e., 0).

/// \brief Returns the row index corresponding to Table 7.4.1.5.3-1, TS 38.211 given the CSI-RS configuration.
/// \param[in] nof_ports Number of ports, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] density Density, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] cdm_type CDM-type, as per Table 7.4.1.5.3-1, TS 38.211.
/// \param[in] fd_alloc Freq. Domain Allocation, as per \c frequencyDomainAllocation in \c CSI-RS-ResourceMapping,
///            TS 38.331.
/// \return The row index of Table 7.4.1.5.3-1, TS 38.211 corresponding to the inputs. If the given input configuration
///         does not match any of the rows in the table, the function triggers an assert and returns an invalid value
///         (i.e., 0).
unsigned get_csi_rs_resource_mapping_row_number(uint8_t                          nof_ports,
                                                csi_rs_freq_density_type         density,
                                                csi_rs_cdm_type                  cdm_type,
                                                const freq_allocation_mask_type& fd_alloc);

/// \brief returns the number of CSI-RS ports corresponding to a CSI-RS mapping table entry.
///
/// The number of ports for each CSI-RS mapping format is defined in TS38.211 Table 7.4.1.5.3-1.
///
/// \param csi_rs_row_id CSI-RS mapping table row identifier, set as per the first column in TS38.211 Table 7.4.1.5.3-1.
/// \return The number of ports for the specified CSI-RS mapping table entry.

/// \brief returns the number of CSI-RS ports corresponding to a CSI-RS mapping table entry.
///
/// The number of ports for each CSI-RS mapping format is defined in TS38.211 Table 7.4.1.5.3-1.
///
/// \param csi_rs_row_id CSI-RS mapping table row identifier, set as per the first column in TS38.211 Table 7.4.1.5.3-1.
/// \return The number of ports for the specified CSI-RS mapping table entry.
unsigned get_nof_csi_rs_ports(unsigned csi_rs_row_id);


} // namespace csi_rs


} // namespace ocudu
