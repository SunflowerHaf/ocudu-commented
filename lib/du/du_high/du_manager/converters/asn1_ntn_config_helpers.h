// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/converters/asn1_ntn_config_helpers.h  (30 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/rrc_nr/sys_info.h"
#include "ocudu/du/du_cell_config.h"


namespace ocudu {
namespace odu {

/// Creates and fills an ASN.1 SIB19 message structure for NTN cell configuration.
/// \param[in] sib19_params The SIB19 configuration parameters to encode.
/// \return The filled ASN.1 SIB19 structure.

/// Creates and fills an ASN.1 SIB19 message structure for NTN cell configuration.
/// \param[in] sib19_params The SIB19 configuration parameters to encode.
/// \return The filled ASN.1 SIB19 structure.
asn1::rrc_nr::sib19_r17_s make_asn1_rrc_cell_sib19(const sib19_info& sib19_params);

/// Creates and fills an ASN.1 NTN-Config-R17 structure for NTN cell configuration.
/// \param[in] sib19_params The NTN cell configuration parameters to encode.
/// \return The filled ASN.1 NTN-Config-R17 structure.

/// Creates and fills an ASN.1 NTN-Config-R17 structure for NTN cell configuration.
/// \param[in] sib19_params The NTN cell configuration parameters to encode.
/// \return The filled ASN.1 NTN-Config-R17 structure.
asn1::rrc_nr::ntn_cfg_r17_s make_asn1_rrc_cell_ntn_cfg(const ntn_config& ntn_cfg);

/// Fills advanced cell NTN-config parameters in ASN.1 SIB19 message.
/// \param[in]  sib19_params content of SIB19 msg.
/// \param[out] out The ASN.1 SIB19 struct to fill.
/// \return A buffer with packed SIB19 as BCCH-DL-SCH message.

/// Fills advanced cell NTN-config parameters in ASN.1 SIB19 message.
/// \param[in]  sib19_params content of SIB19 msg.
/// \param[out] out The ASN.1 SIB19 struct to fill.
/// \return A buffer with packed SIB19 as BCCH-DL-SCH message.
void make_asn1_rrc_advanced_cell_sib19(const sib19_info& sib19_params, asn1::rrc_nr::sib19_r17_s& out);


} // namespace odu
} // namespace ocudu
