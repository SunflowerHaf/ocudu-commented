// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// SPDX-FileCopyrightText: Copyright (C) 2021-2026 Software Radio Systems Limited
// SPDX-License-Identifier: BSD-3-Clause-Open-MPI
// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

// =============================================================================
// FILE: lib/e1ap/common/e1ap_common_messages.h  (19 lines)
//
// LIBRARY: lib/e1ap
// E1 Application Protocol (E1AP, TS 37.483): the control-plane between the CU-CP and the CU-UP. Carries bearer setup/modification/release requests so the CU-CP can configure the user-plane. Separate sub-libraries for cu_cp-side, cu_up-side, and the gateway.
//
// This file is part of the above library. See library comment for context.
// =============================================================================

// Portions of this file may implement 3GPP specifications, which may be subject to additional licensing requirements.

#pragma once


#include "ocudu/asn1/e1ap/e1ap_ies.h"
#include "ocudu/e1ap/common/e1ap_message.h"
#include "ocudu/e1ap/common/e1ap_types.h"


namespace ocudu {

/// Generate an E1AP Error Indication message.

/// Generate an E1AP Error Indication message.
e1ap_message generate_error_indication(uint8_t                                      transaction_id,
                                       const std::optional<gnb_cu_up_ue_e1ap_id_t>& cu_up_ue_id,
                                       const std::optional<gnb_cu_cp_ue_e1ap_id_t>& cu_cp_ue_id,
                                       const std::optional<asn1::e1ap::cause_c>&    cause);


} // namespace ocudu
