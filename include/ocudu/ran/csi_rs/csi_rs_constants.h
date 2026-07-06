// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/csi_rs/csi_rs_constants.h  (47 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


namespace ocudu {

/// Maximum number of \f$k_i\f$ frequency allocation reference values, according to TS 38.211 Table 7.4.1.5.3-1.

/// Maximum number of \f$k_i\f$ frequency allocation reference values, according to TS 38.211 Table 7.4.1.5.3-1.
constexpr unsigned CSI_RS_MAX_NOF_K_INDEXES = 6;

/// Maximum number of ports that can be simultaneously used for CSI-RS, detailed in the TS38.211 Table 7.4.1.5.3-1
/// Row 18.

/// Maximum number of ports that can be simultaneously used for CSI-RS, detailed in the TS38.211 Table 7.4.1.5.3-1
/// Row 18.
constexpr unsigned CSI_RS_MAX_NOF_PORTS = 32;

/// Maximum number of resource sets per resource configuration. See TS 38.331, \c
/// maxNrofNZP-CSI-RS-ResourceSetsPerConfig.

/// Maximum number of resource sets per resource configuration. See TS 38.331, \c
/// maxNrofNZP-CSI-RS-ResourceSetsPerConfig.
constexpr unsigned MAX_NOF_NZP_CSI_RS_RESOURCE_SETS_PER_CSI_RESOURCE_CONFIG = 16;

/// Maximum number of CSI SSB resource sets per resource configuration. See TS 38.331, \c
/// maxNrofCSI-SSB-ResourceSetsPerConfig.

/// Maximum number of CSI SSB resource sets per resource configuration. See TS 38.331, \c
/// maxNrofCSI-SSB-ResourceSetsPerConfig.
constexpr unsigned MAX_NOF_CSI_SSB_RESOURCE_SETS_PER_CSI_RESOURCE_CONFIG = 1;

/// Maximum number of CSI IM resource sets per resource configuration. See TS 38.331, \c
/// maxNrofCSI-IM-ResourceSetsPerConfig.

/// Maximum number of CSI IM resource sets per resource configuration. See TS 38.331, \c
/// maxNrofCSI-IM-ResourceSetsPerConfig.
constexpr unsigned MAX_NOF_CSI_IM_RESOURCE_SETS_PER_CSI_RESOURCE_CONFIG = 16;

/// Maximum number of resources per resource configuration. See TS 38.331, \c
/// maxNrofNZP-CSI-RS-ResourcesPerConfig.

/// Maximum number of resources per resource configuration. See TS 38.331, \c
/// maxNrofNZP-CSI-RS-ResourcesPerConfig.
constexpr unsigned MAX_NOF_NZP_CSI_RS_RESOURCES_PER_CONFIG = 128;

/// Maximum number of triggers for aperiodic CSI reporting. See TS 38.331, \c
/// maxNrOfCSI-AperiodicTriggers.

/// Maximum number of triggers for aperiodic CSI reporting. See TS 38.331, \c
/// maxNrOfCSI-AperiodicTriggers.
constexpr unsigned MAX_NOF_CSI_APERIODIC_TRIGGERS = 128;

/// Maximum number of report configurations per trigger state for aperiodic reporting. See TS 38.331, \c
/// maxNrofReportConfigPerAperiodicTrigger.

/// Maximum number of report configurations per trigger state for aperiodic reporting. See TS 38.331, \c
/// maxNrofReportConfigPerAperiodicTrigger.
constexpr unsigned MAX_NOF_REPORT_CONFIG_PER_APERIODIC_TRIGGER = 16;

/// See TS 38.331, \c maxNrofAP-CSI-RS-ResourcesPerSet.

/// See TS 38.331, \c maxNrofAP-CSI-RS-ResourcesPerSet.
constexpr unsigned MAX_NOF_AP_CSI_RS_RESOURCES_PER_SET = 16;

/// Maximum number of triggers for semi persistent reporting on PUSCH. See TS 38.331, \c
/// maxNrOfSemiPersistentPUSCH-Triggers.

/// Maximum number of triggers for semi persistent reporting on PUSCH. See TS 38.331, \c
/// maxNrOfSemiPersistentPUSCH-Triggers.
constexpr unsigned MAX_NOF_SEMI_PERSISTENT_PUSCH_TRIGGERS = 64;


} // namespace ocudu
