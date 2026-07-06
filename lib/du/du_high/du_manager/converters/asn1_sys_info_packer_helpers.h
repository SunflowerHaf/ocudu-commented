// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/du/du_high/du_manager/converters/asn1_sys_info_packer_helpers.h  (26 lines)
//
// LIBRARY: lib/du
// O-RAN Distributed Unit core: the du_high (scheduler, MAC, RLC, F1AP, UE management — the 'brain' of the DU) and du_low (upper PHY / FAPI boundary). Contains the full DU High implementation: DU manager, DU scheduler wrapper, F1AP procedures, UE context FSMs, and the O-DU factory.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/rrc_nr/sys_info.h"
#include "ocudu/ran/pci.h"
#include "ocudu/ran/sib/cell_reselection.h"


namespace ocudu::asn1_utils {

/// Convert Qhyst value to ASN.1 RRC representation.

/// Convert Qhyst value to ASN.1 RRC representation.
asn1::rrc_nr::sib2_s::cell_resel_info_common_s_::q_hyst_opts::options make_asn1_rrc_q_hyst(const q_hyst_t& q_hyst);

/// Convert QoffsetRange value to ASN.1 RRC representation.

/// Convert QoffsetRange value to ASN.1 RRC representation.
asn1::rrc_nr::q_offset_range_opts::options make_asn1_rrc_q_offset_range(const q_offset_range_t& q_offset_range);

/// Convert PCI range to ASN.1 RRC representation.

/// Convert PCI range to ASN.1 RRC representation.
asn1::rrc_nr::pci_range_s make_asn1_rrc_pci_range(const pci_range_t& pci_range);

/// Convert allowed measurement bandwidth to ASN.1 RRC representation.

/// Convert allowed measurement bandwidth to ASN.1 RRC representation.
asn1::rrc_nr::eutra_allowed_meas_bw_opts::options
make_asn1_rrc_allowed_meas_bw(const eutra_allowed_meas_bandwidth_t& allowed_beas_bw);


} // namespace ocudu::asn1_utils
