// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: include/ocudu/ran/csi_report/csi_report_config_helpers.h  (27 lines)
//
// INTERFACE HEADER — include/ocudu/ran
// RAN types and utilities (~250 files): the single most widely included tree. Contains everything RAN-specific that is not layer-specific: slot_point and slot_point_extended, ARFCN and frequency helpers, NR band definitions and lookup functions, cell identity types (PCI, NCI, CGI, PLMN, TAC), QoS types (5QI, S-NSSAI), resource block types (PRB, CRB, VRB, BWP), PDSCH/PUSCH/PUCCH resource configuration types, TDD pattern types, HARQ types, MCS tables and helpers, PRACH configuration tables, SSB configuration types, MIMO layer types, subcarrier spacing types, and hundreds of supporting enums and constants drawn directly from 3GPP TS 38.211/212/213/214/321/322/331.
//
// This file defines abstract interfaces / data types used across multiple
// layers. Implementations live in the corresponding lib/ directory.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/ran/csi_report/csi_report_configuration.h"
#include "ocudu/ran/csi_rs/csi_meas_config.h"


namespace ocudu {

/// \brief Returns the Channel State Information (CSI) report configuration parameters based on CSI-MeasConfig.
/// \param csi_meas CSI-RS measurement configuration.
/// \return Returns CSI report configuration parameters.

/// \brief Returns the Channel State Information (CSI) report configuration parameters based on CSI-MeasConfig.
/// \param csi_meas CSI-RS measurement configuration.
/// \return Returns CSI report configuration parameters.
csi_report_configuration create_csi_report_configuration(const csi_meas_config& csi_meas);

/// CSI report configuration validator.

/// CSI report configuration validator.
bool is_valid(const csi_report_configuration& config);

/// \brief Tells whether the CSI report is configured for PUSCH.
///
/// \remark There is no explicit statement defining this in the TS; however, we can infer from \c reportConfigType in \c
/// CSI-ReportConfig, TS 38.331, that the CSI report is configured for PUSCH if it is either \c semiPersistentOnPUSCH or
/// \c aperiodic, while it's configured for PUCCH if it is \c periodic or \c semiPersistentOnPUCCH.

/// \brief Tells whether the CSI report is configured for PUSCH.
///
/// \remark There is no explicit statement defining this in the TS; however, we can infer from \c reportConfigType in \c
/// CSI-ReportConfig, TS 38.331, that the CSI report is configured for PUSCH if it is either \c semiPersistentOnPUSCH or
/// \c aperiodic, while it's configured for PUCCH if it is \c periodic or \c semiPersistentOnPUCCH.
bool is_pusch_configured(const csi_meas_config& csi_meas);


} // namespace ocudu
