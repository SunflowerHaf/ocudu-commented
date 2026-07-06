// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/mac/p7/pdu_translators/ssb.h  (21 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi/p7/builders/dl_ssb_pdu_builder.h"
#include "ocudu/mac/mac_cell_result.h"


namespace ocudu {
namespace fapi_adaptor {

/// \brief Helper function that converts from a SSB MAC PDU to a SSB FAPI PDU.
///
/// \param[out] builder   SSB FAPI builder that helps to fill the PDU.
/// \param[in] mac_pdu    SSB MAC PDU to convert to SSB FAPI PDU.
/// \param[in] slot       Slot point associated to this PDU.

/// \brief Helper function that converts from a SSB MAC PDU to a SSB FAPI PDU.
///
/// \param[out] builder   SSB FAPI builder that helps to fill the PDU.
/// \param[in] mac_pdu    SSB MAC PDU to convert to SSB FAPI PDU.
/// \param[in] slot       Slot point associated to this PDU.
void convert_ssb_mac_to_fapi(fapi::dl_ssb_pdu_builder& builder, const ocudu::dl_ssb_pdu& mac_pdu, slot_point slot);


} // namespace fapi_adaptor
} // namespace ocudu
