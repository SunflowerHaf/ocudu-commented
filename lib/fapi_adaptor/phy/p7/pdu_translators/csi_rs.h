// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/fapi_adaptor/phy/p7/pdu_translators/csi_rs.h  (36 lines)
//
// LIBRARY: lib/fapi_adaptor
// FAPI (Functional API) adaptors between the MAC layer and the upper PHY. Translates MAC scheduling decisions (PDCCH, PDSCH, PUCCH, PUSCH allocations) into FAPI P7 messages and vice versa for UL indications. Also includes the P5 (cell config) adaptor and UCI part-2 size tables.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/fapi/p7/messages/dl_csi_rs_pdu.h"
#include "ocudu/phy/upper/signal_processors/nzp_csi_rs/nzp_csi_rs_generator.h"
#include "ocudu/ran/csi_rs/csi_rs_pattern.h"


namespace ocudu {
namespace fapi_adaptor {

/// \brief Helper function that converts from a CSI-RS FAPI PDU to a NZP-CSI-RS processor PDU.
///
/// \param[out] proc_pdu NZP-CSI-RS processor PDU.
/// \param[in] fapi_pdu FAPI PDU received that contains all the CSI-RS parameters.
/// \param[in] sfn SFN when the FAPI PDU was received.
/// \param[in] slot Slot when the FAPI PDU was received.
/// \param[in] cell_bandwidth_prb Cell bandwidth in PRB.

/// \brief Helper function that converts from a CSI-RS FAPI PDU to a NZP-CSI-RS processor PDU.
///
/// \param[out] proc_pdu NZP-CSI-RS processor PDU.
/// \param[in] fapi_pdu FAPI PDU received that contains all the CSI-RS parameters.
/// \param[in] sfn SFN when the FAPI PDU was received.
/// \param[in] slot Slot when the FAPI PDU was received.
/// \param[in] cell_bandwidth_prb Cell bandwidth in PRB.
void convert_csi_rs_fapi_to_phy(nzp_csi_rs_generator::config_t& proc_pdu,
                                const fapi::dl_csi_rs_pdu&      fapi_pdu,
                                slot_point                      slot,
                                uint16_t                        cell_bandwidth_prb);

/// \brief Gets the CSI-RS pattern from the given FAPI PDU.
///
/// \param[out] pattern CSI-RS pattern.
/// \param[in] fapi_pdu FAPI PDU received that contains all the CSI-RS parameters.
/// \param[in] cell_bandwidth_prb Cell bandwidth in PRB.

/// \brief Gets the CSI-RS pattern from the given FAPI PDU.
///
/// \param[out] pattern CSI-RS pattern.
/// \param[in] fapi_pdu FAPI PDU received that contains all the CSI-RS parameters.
/// \param[in] cell_bandwidth_prb Cell bandwidth in PRB.
void get_csi_rs_pattern_from_fapi_pdu(csi_rs_pattern&            pattern,
                                      const fapi::dl_csi_rs_pdu& fapi_pdu,
                                      uint16_t                   cell_bandwidth_prb);


} // namespace fapi_adaptor
} // namespace ocudu
