// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/common/log_helpers.h  (48 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "e1ap_logger.h"
#include "ocudu/e1ap/common/e1ap_message.h"
#include "ocudu/ran/cu_cp_types.h"
#include "ocudu/ran/cu_up_types.h"
#include "ocudu/support/format/prefixed_logger.h"


namespace ocudu {

/// \brief Helper for logging Rx/Tx E1AP PDUs for the CU-CP and CU-UP.

/// \brief Helper for logging Rx/Tx E1AP PDUs for the CU-CP and CU-UP.
template <typename UeIndex>
void log_e1ap_pdu(ocudulog::basic_logger&       logger,
                  bool                          is_rx,
                  const std::optional<UeIndex>& ue_id,
                  const e1ap_message&           e1ap_msg,
                  bool                          json_enabled);

/// \brief Helper for logging Rx/Tx E1AP PDUs for the CU-CP and CU-UP with prefixed logger.

/// \brief Helper for logging Rx/Tx E1AP PDUs for the CU-CP and CU-UP with prefixed logger.
template <typename UeIndex>
void log_e1ap_pdu(e1ap_logger&                  logger,
                  bool                          is_rx,
                  const std::optional<UeIndex>& ue_id,
                  const e1ap_message&           e1ap_msg,
                  bool                          json_enabled);


extern template void log_e1ap_pdu<cu_cp_ue_index_t>(ocudulog::basic_logger&                logger,
                                                    bool                                   is_rx,
                                                    const std::optional<cu_cp_ue_index_t>& ue_id,
                                                    const e1ap_message&                    e1ap_msg,
                                                    bool                                   json_enabled);
extern template void log_e1ap_pdu<cu_up_ue_index_t>(ocudulog::basic_logger&                logger,
                                                    bool                                   is_rx,
                                                    const std::optional<cu_up_ue_index_t>& ue_id,
                                                    const e1ap_message&                    e1ap_msg,
                                                    bool                                   json_enabled);


extern template void log_e1ap_pdu<cu_up_ue_index_t>(e1ap_logger&                           logger,
                                                    bool                                   is_rx,
                                                    const std::optional<cu_up_ue_index_t>& ue_id,
                                                    const e1ap_message&                    e1ap_msg,
                                                    bool                                   json_enabled);


} // namespace ocudu
