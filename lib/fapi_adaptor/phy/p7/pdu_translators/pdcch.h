// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/phy/p7/pdu_translators/pdcch.h  (27 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi/p7/messages/dl_pdcch_pdu.h"
#include "ocudu/phy/upper/channel_processors/pdcch/pdcch_processor.h"


namespace ocudu {
namespace fapi_adaptor {


class precoding_matrix_repository;

/// Helper function that converts from a PDCCH FAPI PDU to a PDCCH processor PDU.
///
/// \param[out] proc_pdu PDCCH processor PDU.
/// \param[in] fapi_pdu FAPI PDU received that contains all the CSI-RS parameters.
/// \param[in] slot Slot when the FAPI PDU was received.
/// \param[in] pm_repo Precoding matrix repository.

/// Helper function that converts from a PDCCH FAPI PDU to a PDCCH processor PDU.
///
/// \param[out] proc_pdu PDCCH processor PDU.
/// \param[in] fapi_pdu FAPI PDU received that contains all the CSI-RS parameters.
/// \param[in] slot Slot when the FAPI PDU was received.
/// \param[in] pm_repo Precoding matrix repository.
void convert_pdcch_fapi_to_phy(pdcch_processor::pdu_t&            proc_pdu,
                               const fapi::dl_pdcch_pdu&          fapi_pdu,
                               slot_point                         slot,
                               const precoding_matrix_repository& pm_repo);


} // namespace fapi_adaptor
} // namespace ocudu
